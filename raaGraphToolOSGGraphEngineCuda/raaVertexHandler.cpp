#include "StdAfx.h"

#include <osg/MatrixTransform>
#include <osg/Material>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osg/StateSet>
#include <osg/BlendFunc>

#include <osgManipulator/RotateCylinderDragger>
#include <osgManipulator/RotateSphereDragger>

#include <osgManipulator/TrackballDragger>
#include <osgManipulator/Translate1DDragger>
#include <osgManipulator/Translate2DDragger>
#include <osgManipulator/TranslateAxisDragger>

#include <osgManipulator/TabPlaneTrackballDragger>
#include <osgManipulator/TabBoxDragger>
#include <osgManipulator/TabPlaneDragger>

#include <osgManipulator/Scale1DDragger>
#include <osgManipulator/Scale2DDragger>
#include <osgManipulator/ScaleAxisDragger>

#include <osgManipulator/TranslatePlaneDragger>

#include "raaVertex.h"
#include "raaVertexHandler.h"

//osg::Matrixf raaVertexHandler::sm_Scale=osg::Matrixf::scale(2.0f, 2.0f, 2.0f);
osg::Matrixf raaVertexHandler::sm_Scale=osg::Matrixf::scale(1.0f, 1.0f, 1.0f);
osg::Matrixf raaVertexHandler::sm_InvScale=osg::Matrixf::inverse(sm_Scale);

raaVertexHandler::raaVertexHandler(osg::Group *pRoot)
{
	m_pSelectedSwitch=0;

	m_iManip=0;
}

raaVertexHandler::~raaVertexHandler(void)
{
}

void raaVertexHandler::pick( osgViewer::View* pView, float x, float y )
{
	osgUtil::LineSegmentIntersector::Intersections intersections;

	updateManipulators();

	if(m_pSelectedSwitch)
	{
		m_pSelectedSwitch->setAllChildrenOff();
		((raaVertex*)m_pSelectedSwitch->getParent(0)->getUpdateCallback())->setActive(false);
		m_pSelectedSwitch=0;
	}

	if (pView->computeIntersections(x,y,intersections))
	{
		if(intersections.size())
		{
			for(osgUtil::LineSegmentIntersector::Intersections::iterator it = intersections.begin();it!=intersections.end();it++)
			{			
				for(osg::NodePath::const_reverse_iterator rit=it->nodePath.rbegin();rit!=it->nodePath.rend();rit++)
				{
					osg::Node *pNode=*rit;
					if(osg::Group *pGroup=dynamic_cast<osg::Group*>(pNode))
					{
						if(pGroup->getName()=="manip")
						{
							m_iManip=0;

							for(unsigned int i=0;i<pGroup->getNumChildren();i++)
							{
								if(osg::Switch *pSwitch=dynamic_cast<osg::Switch*>(pGroup->getChild(i)))
								{
									m_pSelectedSwitch=pSwitch;
									break;
								}
							}

							if(m_pSelectedSwitch) m_pSelectedSwitch->setSingleChildOn(m_iManip);
							((raaVertex*)pGroup->getUpdateCallback())->setActive(true);
							((raaVertex*)pGroup->getUpdateCallback())->setDraggerTransform((osg::MatrixTransform*)m_pSelectedSwitch->getChild(m_iManip));
							return;
						}
					}
				}
			}
		}
	}
}

void raaVertexHandler::addDragger(osgManipulator::Dragger *pDragger, osg::Switch *pSwitch, osg::MatrixTransform *pMT)
{
	pDragger->setupDefaultGeometry();
	pDragger->setHandleEvents(true);
	pDragger->addTransformUpdating(pMT);
	pDragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);
	pDragger->setMatrix(sm_Scale*pMT->getMatrix());
	pSwitch->addChild(pDragger);
}

bool raaVertexHandler::handle( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor * )
{
	osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView());

	if(ea.getButton()==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON && (ea.getButtonMask()&&osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON))
	{
		osgViewer::View* pView = dynamic_cast<osgViewer::View*>(&aa);
		osg::ref_ptr<osgGA::GUIEventAdapter> event = new osgGA::GUIEventAdapter(ea);
		if(pView) pick(pView,ea.getX(), ea.getY());	
	}

	

	if(pViewer && ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN)
	{	
		switch(ea.getKey())
		{
		case 'p':
			if(m_pSelectedSwitch)
			{
				((raaVertex*)m_pSelectedSwitch->getParent(0)->getUpdateCallback())->toggleFixed();
			}
			return true;
		case osgGA::GUIEventAdapter::KEY_Left:
			if(m_pSelectedSwitch)
			{
				updateManipulators();

				m_pSelectedSwitch->setAllChildrenOff();

				m_iManip++; 
				if(m_iManip>=(int)m_pSelectedSwitch->getNumChildren()) m_iManip=0;

				m_pSelectedSwitch->setSingleChildOn(m_iManip);
				((raaVertex*)m_pSelectedSwitch->getParent(0)->getUpdateCallback())->setDraggerTransform((osg::MatrixTransform*)m_pSelectedSwitch->getChild(m_iManip));
			}
			return true;
		case osgGA::GUIEventAdapter::KEY_Right:
			if(m_pSelectedSwitch)
			{
				updateManipulators();

				m_pSelectedSwitch->setAllChildrenOff();

				m_iManip--; 
				if(m_iManip<0) m_iManip=m_pSelectedSwitch->getNumChildren()-1;

				m_pSelectedSwitch->setSingleChildOn(m_iManip);
				((raaVertex*)m_pSelectedSwitch->getParent(0)->getUpdateCallback())->setDraggerTransform((osg::MatrixTransform*)m_pSelectedSwitch->getChild(m_iManip));
			}
			return true;
		}
	}
	return false;
}

void raaVertexHandler::updateManipulators()
{
	if(m_pSelectedSwitch)
	{
		osgManipulator::Dragger *pDragger=(osgManipulator::Dragger*)m_pSelectedSwitch->getChild(m_iManip);
		osg::Matrixf m=pDragger->getMatrix();

		((raaVertex*)m_pSelectedSwitch->getParent(0)->getUpdateCallback())->setPos(m.getTrans());
	}
}

