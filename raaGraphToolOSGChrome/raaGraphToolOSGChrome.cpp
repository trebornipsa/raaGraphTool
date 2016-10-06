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

#include <raaGraphEngine/raaGraphEngine.h>
#include <raaGraphEngine/raaGraph.h>
#include <raaGraphEngine/raaNode.h>
#include <raaGraphEngine/raaEdge.h>
#include <raaGraphEngine/raaNodeFactory.h>
#include <raaGraphEngine/raaEdgeFactory.h>

#include "raaArc.h"
#include "raaVertex.h"
#include "raaUndirectedGraph.h"
#include "raaVertexHandler.h"
#include "raaVertexCallback.h"

#include <QtSql/QtSql>

osg::Group *g_pRoot=0;
raaGraph *g_pGraph=0;
static float sg_fScale=10.0f;
static bool sg_bHeight=false;

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
			if(ea.getKey()=='p')
			{
				g_pGraph->solve(1);

				std::cout << "Energy: " << g_pGraph->energy() << std::endl;

				return true;
			}
			else if(ea.getKey()=='a')
			{
				((raaUndirectedGraph*)g_pGraph)->contSolve(true);

				return true;
			}
			else if(ea.getKey()=='z')
			{
				((raaUndirectedGraph*)g_pGraph)->contSolve(false);

				return true;
			}
		}

		return false;
	}
};



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

		raaNode *pNode=g_pGraph->addNode(sID, "raaVertex", sName);
		pNode->setPos(vPos);
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

		if(g_pGraph->getNode(sStart) && g_pGraph->getNode(sEnd))
		{
			g_pGraph->addEdge("raaArc", g_pGraph->getNode(sStart), g_pGraph->getNode(sEnd), fWeight);
		}
	}
}

bool loadPajek(std::string sFile)
{
	std::string sLine;
	std::ifstream in(sFile);
	int iMode=0; // 1->vertices, 2->arcs; 	

	g_pGraph=raaGraphEngine::instance()->createGraph("raaUndirectedGraph", "pajek");

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

		g_pGraph->normaliseEdgeWeights();
		((raaUndirectedGraph*)g_pGraph)->applyMasses();
		g_pGraph->setSolver("undirected");
		return true;
	}	
	return false;
}

bool loadChrome(std::string sFile)
{
	g_pGraph=raaGraphEngine::instance()->createGraph("raaUndirectedGraph", "chrome");

	QSqlDatabase db;
	db=QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(sFile.c_str());


	raaNode *pHistory=g_pGraph->addNode("History", "raaVertex", "History");
	pHistory->setPos(osg::Vec3f(0.0f, 0.0f, 0.0f));
	pHistory->setFixed(true);


	if(db.open())
	{
		QStringList sl=db.tables();

		for(QStringList::iterator it=sl.begin();it!=sl.end();it++)
			std::cout << "Table: " << it->toStdString() << std::endl;

		//		QSqlQuery q("SELECT id, url, from visit FROM visits");
		QSqlQuery q0("SELECT * FROM visits");

		int iUrl0=q0.record().indexOf("url");
		int iId0=q0.record().indexOf("id");
		int iFrom0=q0.record().indexOf("from_visit");
		int iDuration0=q0.record().indexOf("visit_duration");

		unsigned int uiProcessed=0; unsigned int uiAdded=0;

		while(q0.next() && uiProcessed<10000)
		{
			if(!g_pGraph->getNode(q0.value(iId0).toString().toStdString()))
			{
				raaNode *pNode=g_pGraph->addNode(q0.value(iId0).toString().toStdString(), "raaVertex", q0.value(iUrl0).toString().toStdString());
//				pNode->setMass(1.0f);
			}

			if(q0.value(iFrom0).toInt())
				g_pGraph->addEdge("raaArc", g_pGraph->getNode(q0.value(iFrom0).toString().toStdString()), g_pGraph->getNode(q0.value(iId0).toString().toStdString()), 10.0f);
			else
				g_pGraph->addEdge("raaArc", pHistory, g_pGraph->getNode(q0.value(iId0).toString().toStdString()), 20.0f);
//				g_pGraph->getNode(q0.value(iId0).toString().toStdString())->setFixed(true);

			std::cout<<"Processed: " << uiProcessed++ << std::endl;
		}

		db.close();

		g_pGraph->normaliseEdgeWeights();
		((raaUndirectedGraph*)g_pGraph)->applyMasses();
		g_pGraph->setSolver("undirected");
		return true;
	}	
	return false;
}

int main(int argc, char* argv[])
{
	raaGraphEngine::start();

	g_pRoot=new osg::Group();
	g_pRoot->ref();

	raaUndirectedGraphFactory *pUDGFactory;
	raaGraphEngine::instance()->registerNodeFactory("raaVertex", new raaVertexFactory());
	raaGraphEngine::instance()->registerEdgeFactory("raaArc", new raaArcFactory());
	raaGraphEngine::instance()->registerGraphFactory("raaUndirectedGraph", pUDGFactory=new raaUndirectedGraphFactory());
	pUDGFactory->setRoot(g_pRoot);

	std::string sPajek;

	for(int i=0;i<argc;i++)
	{
		if(!strcmp(argv[i], "-chrome")) loadChrome(argv[i+1]);
		else if(!strcmp(argv[i], "-s")) sg_fScale=atof((argv[i+1]));
	}

	osg::ArgumentParser arguments(&argc,argv);

	osgViewer::Viewer viewer(arguments);

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

	viewer.addEventHandler(new raaSolveHandler());
	viewer.addEventHandler(new raaVertexHandler(g_pRoot));
	viewer.addEventHandler(new osgViewer::ThreadingHandler);
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	viewer.addEventHandler(new osgViewer::StatsHandler);
//	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);
//	viewer.addEventHandler(new osgViewer::LODScaleHandler);
//	viewer.addEventHandler(new osgViewer::ScreenCaptureHandler);
//	viewer.addEventHandler(new osgViewer::HelpHandler);

	viewer.setSceneData(g_pRoot);

	viewer.realize();


	return viewer.run();


	return 0;
}
