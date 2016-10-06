#include "stdafx.h"

#include <iostream>

#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/Group>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Material>

#include <QtSql/QtSql>

osg::Group *g_pGroup=0;

int main(int argc, char* argv[])
{
	g_pGroup=new osg::Group();
	g_pGroup->ref();
	g_pGroup->setName("root");

	QSqlDatabase db;
	db=QSqlDatabase::addDatabase("QSQLITE");

	QDir d("E:");

	db.setDatabaseName(d.path()+QDir::separator()+"History.db");
//	db.setDatabaseName("C:/Users/Rob/AppData/Local/Google/Chrome/User Data/Default/History");
	
	if(db.open())
	{
		std::cout << "connected" << std::endl;

		QStringList sl=db.tables();

		for(QStringList::iterator it=sl.begin();it!=sl.end();it++)
		{
			std::cout<<"table: " << it->toStdString() << std::endl;

		}

		db.close();
	}
	else
	{
		std::cout << "fail" << std::endl;
	}

	std::cout << "Finished" << std::endl;

	osgViewer::Viewer viewer;

	// define graphics context
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

	// RAA::Exercise 3 
	// add custom handler -> press 'i' for info, 'p' for rendering modes
	viewer.addEventHandler(new raaOSGSimpleEventHandler());

	// add the thread model handler -> press 'm'
	viewer.addEventHandler(new osgViewer::ThreadingHandler);

	// add the window size toggle handler -> press 'f'
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);

	// add the stats handler -> press 's'
	viewer.addEventHandler(new osgViewer::StatsHandler);

	// add the record camera path handler
	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);

	// add the LOD Scale handler
	viewer.addEventHandler(new osgViewer::LODScaleHandler);

	// add the screen capture handler -> press 'c'. look for image file in working dir($(osg)\bin)
	viewer.addEventHandler(new osgViewer::ScreenCaptureHandler);

	// add the help handler -> press 'h'
	viewer.addEventHandler(new osgViewer::HelpHandler);

	// set the scene to render
	viewer.setSceneData(g_pRoot);

	viewer.realize();

	return viewer.run();
}

