// raaGraphToolOSG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

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

//#include <raaGraphEngine/raaGraphEngine.h>
//#include <raaGraphEngine/raaGraph.h>
//#include <raaGraphEngine/raaNode.h>
//#include <raaGraphEngine/raaEdge.h>
//#include <raaGraphEngine/raaNodeFactory.h>
//#include <raaGraphEngine/raaEdgeFactory.h>

//#include "raaArc.h"
//#include "raaVertex.h"
//#include "raaUndirectedGraph.h"
#include "raaVertexHandler.h"
//#include "raaVertexCallback.h"

#include "raaEdgeDrawable.h"
#include "raaCudaGraph.h"
#include "raaGraphIndexer.h"

osg::Group *g_pRoot=0;
//raaGraph *g_pGraph=0;
raaCudaGraph *g_pGraph=0;
static float sg_fScale=10.0f;
static bool sg_bHeight=false;

typedef std::map<std::string, unsigned int> nodeMap;
nodeMap g_Nodes;
std::string g_sFont="fonts/arial.ttf"; 

class raaSolveHandler: public osgGA::GUIEventHandler
{
public:
	raaSolveHandler()
	{ 

	}

	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *)
	{
		if(ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN)
		{
			if(ea.getKey()=='s')
			{
//				g_pGraph->solve(1);

//				std::cout << "Energy: " << g_pGraph->energy() << std::endl;

				g_pGraph->solve(0.3f);
				std::cout << "Finished " << std::endl;

				return true;
			}
			else if(ea.getKey()=='a')
			{
//				((raaUndirectedGraph*)g_pGraph)->contSolve(true);

				return true;
			}
			else if(ea.getKey()=='z')
			{
//				((raaUndirectedGraph*)g_pGraph)->contSolve(false);

				return true;
			}
		}

		return false;
	}
};

void addDragger(osgManipulator::Dragger *pDragger, osg::Switch *pSwitch, osg::MatrixTransform *pMT)
{
	pDragger->setupDefaultGeometry();
	pDragger->setHandleEvents(true);
	pDragger->addTransformUpdating(pMT);
	pDragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);
	pDragger->setMatrix(pMT->getMatrix());
	pSwitch->addChild(pDragger);
}

osg::Material* makeMaterial(osg::Vec4f vCol)
{
	osg::Material *pMat=new osg::Material();

	pMat->setAmbient(osg::Material::FRONT, osg::Vec4(vCol[0]*0.2f, vCol[1]*0.2f, vCol[2]*0.2f, 1.0f));
	pMat->setDiffuse(osg::Material::FRONT, osg::Vec4(vCol[0]*0.65f, vCol[1]*0.65f, vCol[2]*0.65f, 1.0f));
	pMat->setSpecular(osg::Material::FRONT, osg::Vec4(vCol[0]*0.9f, vCol[1]*0.9f, vCol[2]*0.9f, 1.0f));
	pMat->setShininess(osg::Material::FRONT, 2.0f);

	return pMat;
}



osg::Group* createNode(osg::Vec3f vPos, std::string sName)
{
	osg::Group *pGroup=new osg::Group();
	pGroup->setName("manip");
	pGroup->ref();

	osg::MatrixTransform *pMT=new osg::MatrixTransform();
	pMT->setName("Transform");
	pMT->setMatrix(osg::Matrix::translate(vPos));
	pGroup->addChild(pMT);

	osg::Switch *pDraggerSwitch=new osg::Switch();
	pDraggerSwitch->setName("DraggerSwitch");
	pGroup->addChild(pDraggerSwitch);

	osg::Switch *pMaterialSwitch=new osg::Switch(); 
	pMaterialSwitch->setName("MaterialSwitch");
	pMT->addChild(pMaterialSwitch);

	osg::ShapeDrawable *pSD=new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), 0.1f));

	osg::Geode *pGeode0=new osg::Geode();
	pGeode0->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(0.2f, 1.0f, 0.3f, 1.0f)), osg::StateAttribute::ON);
	pGeode0->addDrawable(pSD);
	pMaterialSwitch->addChild(pGeode0);

	osg::Geode *pGeode1=new osg::Geode();
	pGeode1->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(1.0f, 0.2f, 0.3f, 1.0f)), osg::StateAttribute::ON);
	pGeode1->addDrawable(pSD);
	pMaterialSwitch->addChild(pGeode1);

	pMaterialSwitch->setSingleChildOn(0);

	addDragger(new osgManipulator::TranslateAxisDragger(), pDraggerSwitch, pMT);
	addDragger(new osgManipulator::Translate1DDragger(), pDraggerSwitch, pMT);
	addDragger(new osgManipulator::Translate2DDragger(), pDraggerSwitch, pMT);
	pDraggerSwitch->setAllChildrenOff();

	osg::Switch *pSwitch=new osg::Switch();
	pSwitch->setAllChildrenOn();

	osg::Billboard *pBB=new osg::Billboard();

	osgText::Text *pText=new osgText::Text();
	pText->setCharacterSize(0.1f);
	pText->setFont(g_sFont);
	pText->setText(sName);

	pBB->addDrawable(pText);
	pSwitch->addChild(pBB);
	pMT->addChild(pSwitch);

	pBB->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(0.6f, 0.2f, 0.2f, 1.0f)), osg::StateAttribute::ON);

	pBB->setMode(osg::Billboard::POINT_ROT_EYE);
	pBB->setAxis(osg::Vec3f(0.0f, 1.0f, 0.0f));
	pBB->setNormal(osg::Vec3f(0.0f, 0.0f, 1.0f));
	pBB->setPosition(0, osg::Vec3f(0.15f, 0.0f, 0.0f));

	return pGroup;
}


void vertices(std::string sString, int iIndex)
{
	std::string sColour;
	std::string sBColour;
	std::string sID;

	if(sString.length())
	{
		char *pStr=(char*)_alloca(sizeof(char)*sString.length()+1);
		sprintf(pStr, "%s", sString.c_str());

		char *pPos=strtok(pStr, " \"");

		sID=pPos ? pPos : "";
		std::string sName=(pPos=strtok(0, "\"")) ? pPos : "";
		float x=(pPos=strtok(0, " ")) ? atof(pPos)*sg_fScale : 0.0f;
		float y=(pPos=strtok(0, " ")) ? atof(pPos)*sg_fScale : 0.0f;
		float z=(pPos=strtok(0, " ")) ? atof(pPos)*sg_fScale : 0.0f;
		osg::Vec3f vPos(x,y,z);
		pPos=strtok(0, " ");
		std::string sColour=(pPos=strtok(0, " ")) ? pPos : "default";
		pPos=strtok(0, " ");
		std::string sBColour=(pPos=strtok(0, " ")) ? pPos : "default";
			
		unsigned int iIndex=g_pGraph->addNode(x,y,z,0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
						
		g_Nodes[sID]=iIndex;

		osg::Group *pGroup=createNode(vPos, sName);
		osg::MatrixTransform *pMT=0;

		for(unsigned int i=0;i<pGroup->getNumChildren();i++)
			if(pGroup->getChild(i)->getName()==std::string("Transform"))
			{
				pMT=dynamic_cast<osg::MatrixTransform*>(pGroup->getChild(i));
				break;
			}

		pMT->addUpdateCallback(new raaGraphIndexer(iIndex, g_pGraph));
		g_pRoot->addChild(pGroup);
	}
}

void arc(std::string sString)
{
	if(sString.length())
	{
		char *pStr=(char*)_alloca(sizeof(char)*sString.length()+1);
		sprintf(pStr, "%s", sString.c_str());

		std::string sStart, sEnd; 
		float fWeight=1.0f;

		char *pPos=strtok(pStr, " ");
		sStart=pPos ? pPos : "";
		sEnd=(pPos=strtok(0, " ")) ? pPos : "";
		fWeight=(pPos=strtok(0, " ")) ? atof(pPos) : 0.0f;

		g_pGraph->addArc(g_Nodes[sStart], g_Nodes[sEnd], 1.0f, fWeight, 1.1f);
	}
}

bool loadPajek(std::string sFile)
{
	std::string sLine;
	std::ifstream in(sFile);
	int iMode=0; // 1->vertices, 2->arcs; 	

//	g_pGraph=raaGraphEngine::instance()->createGraph("raaUndirectedGraph", "pajek");

	if(in.is_open())
	{
		while(!in.eof())
		{
			std::getline(in, sLine);

			if(sLine.find("*Vertices")!=std::string::npos)
			{
				iMode=1;
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

					for(unsigned int i=0;i<uiNumVerticies;i++)
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

		g_pGraph->resolve();

		osg::Geode *pGeode=new osg::Geode();
		raaEdgeDrawable *pDrawable=new raaEdgeDrawable(g_pGraph);
		pGeode->addDrawable(pDrawable);
		g_pRoot->addChild(pGeode);

		return true;
	}	
	return false;
}

int main(int argc, char* argv[])
{
//	raaGraphEngine::start();

	srand(20);

	g_pGraph=new raaCudaGraph();

	g_pRoot=new osg::Group();
	g_pRoot->ref();

//	raaUndirectedGraphFactory *pUDGFactory;
//	raaGraphEngine::instance()->registerNodeFactory("raaVertex", new raaVertexFactory());
//	raaGraphEngine::instance()->registerEdgeFactory("raaArc", new raaArcFactory());
//	raaGraphEngine::instance()->registerGraphFactory("raaUndirectedGraph", pUDGFactory=new raaUndirectedGraphFactory());
//	pUDGFactory->setRoot(g_pRoot);

	std::string sPajek;

	for(int i=0;i<argc;i++)
	{
		if(!strcmp(argv[i], "-pajek")) loadPajek(argv[i+1]);
		else if(!strcmp(argv[i], "-s")) sg_fScale=atof((argv[i+1]));
	}

	osg::ArgumentParser arguments(&argc,argv);

	osgViewer::Viewer viewer(arguments);
/*
	osg::GraphicsContext::Traits *pTraits = new osg::GraphicsContext::Traits();
	pTraits->x = 20;
	pTraits->y = 20;
	pTraits->width = 600;
	pTraits->height = 480;
	pTraits->windowDecoration = true;
	pTraits->doubleBuffer = true;
	pTraits->sharedContext = 0;
	osg::GraphicsContext *pGC = osg::GraphicsContext::createGraphicsContext(pTraits);
*/
	osgGA::KeySwitchMatrixManipulator* pKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator();
	pKeyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
	pKeyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
	pKeyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
	viewer.setCameraManipulator(pKeyswitchManipulator);

	osg::Camera *pCamera = viewer.getCamera();

//	pCamera->setGraphicsContext(pGC);
//	pCamera->setViewport(new osg::Viewport(0,0, pTraits->width, pTraits->height));

	viewer.addEventHandler(new raaSolveHandler());
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
