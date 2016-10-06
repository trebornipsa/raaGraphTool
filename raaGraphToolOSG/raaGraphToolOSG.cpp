// raaGraphToolOSG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/Billboard>
#include <osgText/Text>
#include <osg/Group>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/BlendFunc>
#include <osgManipulator/Translate1DDragger>
#include <osgManipulator/Translate2DDragger>
#include <osgManipulator/TranslateAxisDragger>
#include <map>
#include <list>
#include <vector>

#include <boost/config.hpp>
#include <boost/tokenizer.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/breadth_first_search.hpp>


#include "raaVertexHandler.h"
#include "raaVertexCallback.h"

const static float csg_AmbCoef=0.1f;
const static float csg_DiffCoef=0.8f;
const static float csg_SpecCoef=1.0f;

const static std::string csg_sFont("fonts/arial.ttf");

osg::Group *g_pRoot=0;

typedef std::map<int, osg::Group*>raaVertices;
typedef std::map<int, osg::Group*>raaArcObjects;

typedef struct
{
	unsigned int m_uiStart;
	unsigned int m_uiEnd;
	float m_fWeight;
} raaArc;

typedef std::vector<raaArc*>raaArcs;

raaArcs g_lArcs;

raaVertices g_mVertices;
raaArcObjects g_mArcs;

static float sg_fScale=10.0f;
static bool sg_bHeight=false;
static bool sg_bBoost=false; 


typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS, boost::property < boost::vertex_name_t, std::string >, boost::property < boost::edge_name_t, std::string > > Graph;

osg::Material* makeMaterial(osg::Vec4f vCol)
{
	osg::Material *pMat=new osg::Material();

	pMat->setAmbient(osg::Material::FRONT, osg::Vec4(vCol[0]*csg_AmbCoef, vCol[1]*csg_AmbCoef, vCol[2]*csg_AmbCoef, 1.0f));
	pMat->setDiffuse(osg::Material::FRONT, osg::Vec4(vCol[0]*csg_DiffCoef, vCol[1]*csg_DiffCoef, vCol[2]*csg_DiffCoef, 1.0f));
	pMat->setSpecular(osg::Material::FRONT, osg::Vec4(vCol[0]*csg_SpecCoef, vCol[1]*csg_SpecCoef, vCol[2]*csg_SpecCoef, 1.0f));
	pMat->setShininess(osg::Material::FRONT, 2.0f);

	return pMat;
}

void updateVertexHeight()
{
	int iNumVerts=g_mVertices.size();
	float *paF=(float*)_alloca(sizeof(float)*iNumVerts);

	for(int i=0;i<iNumVerts;i++) paF[i]=0.0f;

	for(int i=0;i<g_lArcs.size();i++)
	{
		paF[g_lArcs[i]->m_uiStart]+=g_lArcs[i]->m_fWeight;
		paF[g_lArcs[i]->m_uiEnd]+=g_lArcs[i]->m_fWeight;
	}

	float fMax=0.0f;
	float fMin=0.0f;

	for(int i=0;i<iNumVerts;i++)
	{
		fMax=(fMax<paF[i]) ? paF[i] : fMax;
		fMin=(fMin>paF[i]) ? paF[i] : fMin;
	}

	float fScale=fMax-fMin;

	for(int i=0;i<iNumVerts;i++)
	{
		osg::Group *pG=g_mVertices[i+1];
		if(pG)
		{
			osg::MatrixTransform *pMT=(osg::MatrixTransform*)pG->getChild(0);
			pMT->setDataVariance(osg::Object::DYNAMIC);
			osg::Matrixf m=pMT->getMatrix();
			osg::Vec3f v=m.getTrans(); 

			v[2]=((paF[i]/fScale)+fMin)*10.0f;
			m.setTrans(v);
			pMT->setMatrix(m);

			osg::Switch *pS=(osg::Switch*)pG->getChild(1);
		
			for(int i=0;i<pS->getNumChildren();i++) ((osgManipulator::Dragger*)pS->getChild(i))->setMatrix(raaVertexHandler::sm_Scale*pMT->getMatrix());
		}
	}
}

void addDragger(osgManipulator::Dragger *pDragger, osg::Switch *pSwitch, osg::MatrixTransform *pMT)
{
	pDragger->setupDefaultGeometry();
	pDragger->setHandleEvents(true);
	pDragger->addTransformUpdating(pMT);
	pDragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);
	pDragger->setMatrix(raaVertexHandler::sm_Scale*pMT->getMatrix());
	pSwitch->addChild(pDragger);
}

void addVertex(int iID, std::string &sName, osg::Vec3f &vPos, std::string &sCol, std::string &sBCol)
{
	osg::Group *pGroup=new osg::Group();
	pGroup->setName("manip");
	pGroup->ref();
	g_mVertices[iID]=pGroup;

	osg::MatrixTransform *pMT=new osg::MatrixTransform();
	pMT->setMatrix(osg::Matrix::translate(vPos));
	pGroup->addChild(pMT);

	osg::Switch *pDraggerSwitch=new osg::Switch();
	pGroup->addChild(pDraggerSwitch);

	osg::Geode *pGeode=new osg::Geode();
	pGeode->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(0.2f, 1.0f, 0.3f, 1.0f)), osg::StateAttribute::ON);
	pMT->addChild(pGeode);

	pGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), 0.1f)));

	addDragger(new osgManipulator::TranslateAxisDragger(), pDraggerSwitch, pMT);
	addDragger(new osgManipulator::Translate1DDragger(), pDraggerSwitch, pMT);
	addDragger(new osgManipulator::Translate2DDragger(), pDraggerSwitch, pMT);
	pDraggerSwitch->setAllChildrenOff();

	osg::Switch *pSwitch=new osg::Switch();
	pSwitch->setAllChildrenOn();

	osg::Billboard *pBB=new osg::Billboard();

	osgText::Text *pText=new osgText::Text();
	pText->setCharacterSize(0.1f);
	pText->setFont(csg_sFont);
	pText->setText(sName);

	pBB->addDrawable(pText);
	pSwitch->addChild(pBB);
	pMT->addChild(pSwitch);

	pBB->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(0.6f, 0.2f, 0.2f, 1.0f)), osg::StateAttribute::ON);

	pBB->setMode(osg::Billboard::POINT_ROT_EYE);
	pBB->setAxis(osg::Vec3f(0.0f, 1.0f, 0.0f));
	pBB->setNormal(osg::Vec3f(0.0f, 0.0f, 1.0f));
	pBB->setPosition(0, osg::Vec3f(0.15f, 0.0f, 0.0f));

	g_pRoot->addChild(pGroup);
}

void addArcs()
{
	osg::Group *pGroup=new osg::Group();
	pGroup->setName("arcs");
	pGroup->ref();

	osg::Geode *pGeode=new osg::Geode();
	pGroup->addChild(pGeode);

	osg::Geometry *pGeom=new osg::Geometry();
	pGeode->addDrawable(pGeom);

	pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::OVERRIDE);
	pGeode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	osg::BlendFunc *pBF=new osg::BlendFunc(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);

	pGeode->getOrCreateStateSet()->setAttributeAndModes(pBF, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	pGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	osg::Vec3Array *pVerts=new osg::Vec3Array();

	pVerts->push_back(osg::Vec3f(0.0f, 0.0f, 0.0f));

	for(raaVertices::iterator it=g_mVertices.begin();it!=g_mVertices.end();it++)
	{
		osg::MatrixTransform *pMT=dynamic_cast<osg::MatrixTransform*>(it->second->getChild(0));
		
		osg::Matrixf m=pMT->getMatrix();

		pVerts->push_back(m.getTrans());
	}

	pGeom->setVertexArray(pVerts);

	osg::DrawElementsUByte *pIndex=new osg::DrawElementsUByte(osg::PrimitiveSet::LINES, 0);
	osg::Vec4Array *pCols=new osg::Vec4Array();

	for(raaArcs::iterator it=g_lArcs.begin();it!=g_lArcs.end();it++)
	{
		pIndex->push_back((*it)->m_uiStart);
		pIndex->push_back((*it)->m_uiEnd);

		pCols->push_back(osg::Vec4f((*it)->m_fWeight, (*it)->m_fWeight, (*it)->m_fWeight, (*it)->m_fWeight));
	}

	pGeom->setColorArray(pCols);
	pGeom->addPrimitiveSet(pIndex);
	pGeom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
	pGeom->setUseDisplayList(false);

	g_pRoot->addChild(pGroup);

	int i=0;
	for(raaVertices::iterator it=g_mVertices.begin();it!=g_mVertices.end();it++, i++)
	{
		it->second->setUpdateCallback(new raaVertexCallback(pGeom, i+1));
	}
}

void vertices(std::string sString, int iIndex)
{
	std::string sColour;
	std::string sBColour;

	if(sString.length())
	{
		char *pStr=(char*)_alloca(sizeof(char)*sString.length()+1);
		sprintf(pStr, "%s", sString.c_str());

		char *pPos=strtok(pStr, " \"");

		int iID=pPos ? atoi(pPos) : 0;
		std::string sName=(pPos=strtok(0, "\"")) ? pPos : "";
		float x=(pPos=strtok(0, " ")) ? atof(pPos)*sg_fScale : 0.0f;
		float y=(pPos=strtok(0, " ")) ? atof(pPos)*sg_fScale : 0.0f;
		float z=(pPos=strtok(0, " ")) ? atof(pPos)*sg_fScale : 0.0f;
		osg::Vec3f vPos(x,y,z);
		pPos=strtok(0, " ");
		std::string sColour=(pPos=strtok(0, " ")) ? pPos : "default";
		pPos=strtok(0, " ");
		std::string sBColour=(pPos=strtok(0, " ")) ? pPos : "default";

		addVertex(iID, sName, vPos, sColour, sBColour);				
	}
}

void normaliseArcWeights()
{
	float fMax, fMin;
	bool bFirst=true;

	for(raaArcs::iterator it=g_lArcs.begin();it!=g_lArcs.end();it++)
	{
		raaArc *pArc=*it;

		if(bFirst)
		{
			fMax=fMin=pArc->m_fWeight;
			bFirst=false;
		}

		fMax=(pArc->m_fWeight>fMax) ? pArc->m_fWeight : fMax;
		fMin=(pArc->m_fWeight<fMin) ? pArc->m_fWeight : fMin;
	}

	float fScale=fMax-fMin;

	for(raaArcs::iterator it=g_lArcs.begin();it!=g_lArcs.end();it++)
	{
		raaArc *pArc=*it;

		pArc->m_fWeight=(((pArc->m_fWeight-fMin)/fScale)*0.4f)+0.6f;

//		pArc->m_fWeight=1.0f-((((pArc->m_fWeight-fMin)/(fMax-fMin))*0.95f)+0.05f);
	}
}

void arc(std::string sString)
{
	if(sString.length())
	{
		raaArc *pArc=new raaArc();
		char *pStr=(char*)_alloca(sizeof(char)*sString.length()+1);
		sprintf(pStr, "%s", sString.c_str());

		char *pPos=strtok(pStr, " ");
		pArc->m_uiStart=pPos ? atoi(pPos) : 0;
		pArc->m_uiEnd=(pPos=strtok(0, " ")) ? atoi(pPos) : 0;
		pArc->m_fWeight=(pPos=strtok(0, " ")) ? atof(pPos) : 0.0f;

		if(pArc->m_uiStart>=0 && pArc->m_uiEnd>=0) g_lArcs.push_back(pArc);
	}
}


bool loadPajek(std::string sFile)
{
	std::string sLine;
	std::ifstream in(sFile);
	int iMode=0; // 1->vertices, 2->arcs; 	

	g_lArcs.clear();

	if(in.is_open())
	{
		while(!in.eof())
		{
			std::getline(in, sLine);

			if(sLine.find("*Vertices")!=std::string::npos)
			{
				iMode=1;
//				std::getline(in, sLine);
			}
			else if(sLine.find("*Arcs")!=std::string::npos)
			{
				iMode=2;
				std::getline(in, sLine);
			}

			switch(iMode)
			{
			case 1:
				{
					char *pLine=(char*)_alloca(sizeof(char)*sLine.length()+1);
					sprintf(pLine, "%s", sLine.c_str());

					char *pPos=strtok(pLine, " ");
					unsigned int uiNumVerticies=(pPos=strtok(0," ")) ? atoi(pPos) : 0;

					for(int i=0;i<uiNumVerticies;i++)
					{
						std::getline(in, sLine);
						vertices(sLine, i);
					}
				}
				break;
			case 2:
				arc(sLine);
				break;
			}
		}
		in.close();
		normaliseArcWeights();
		if(sg_bHeight) updateVertexHeight();
		addArcs();
		return true;
	}	
	return false;
}




int main(int argc, char* argv[])
{
	g_pRoot=new osg::Group();
	g_pRoot->ref();

	std::string sPajek;

	for(int i=0;i<argc;i++)
	{
		if(!strcmp(argv[i], "-pajek")) loadPajek(argv[i+1]);
		else if(!strcmp(argv[i], "-s")) sg_fScale=atof((argv[i+1]));
		else if(!strcmp(argv[i], "-3")) sg_bHeight=true;
	}


	osg::ArgumentParser arguments(&argc,argv);

	osgViewer::Viewer viewer;

	osg::GraphicsContext::Traits *pTraits = new osg::GraphicsContext::Traits();
	pTraits->x = 20;
	pTraits->y = 20;
	pTraits->width = 600;
	pTraits->height = 480;
	pTraits->windowDecoration = true;
	pTraits->doubleBuffer = true;
	pTraits->sharedContext = 0;
	osg::GraphicsContext *pGC = osg::GraphicsContext::createGraphicsContext(pTraits);

	osgGA::KeySwitchMatrixManipulator* pKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator();
	pKeyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
	pKeyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
	pKeyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
	viewer.setCameraManipulator(pKeyswitchManipulator);

	osg::Camera *pCamera = viewer.getCamera();

	pCamera->setGraphicsContext(pGC);
	pCamera->setViewport(new osg::Viewport(0,0, pTraits->width, pTraits->height));

	viewer.addEventHandler(new raaVertexHandler(g_pRoot));
	viewer.addEventHandler(new osgViewer::ThreadingHandler);
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);
	viewer.addEventHandler(new osgViewer::LODScaleHandler);
	viewer.addEventHandler(new osgViewer::ScreenCaptureHandler);
	viewer.addEventHandler(new osgViewer::HelpHandler);

	viewer.setSceneData(g_pRoot);

	viewer.realize();

	return viewer.run();

	return 0;
}

