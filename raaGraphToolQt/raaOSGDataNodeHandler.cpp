#include "stdafx.h"

#include <windows.h>

#include <osgViewer/Viewer>

#include "raaOSGDataNode.h"
#include "raaOSGDataNodeHandler.h"


raaOSGDataNodeHandler::raaOSGDataNodeHandler()
{
	m_pSelected = 0;


	setupDragger();
}


raaOSGDataNodeHandler::~raaOSGDataNodeHandler()
{
	if (m_pDragger) m_pDragger->unref();
}

bool raaOSGDataNodeHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*)
{
	osgViewer::Viewer *pViewer = dynamic_cast<osgViewer::Viewer*>(aa.asView());

	if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON && (ea.getButtonMask() && osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON))
	{
		osgViewer::View* pView = dynamic_cast<osgViewer::View*>(&aa);
		osg::ref_ptr<osgGA::GUIEventAdapter> event = new osgGA::GUIEventAdapter(ea);
		if (pView) pick(pView, ea.getX(), ea.getY());
		return true;
	}

	if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
	{
		switch (ea.getKey())
		{
		case 'p':
			if (m_pSelected)
			{
				m_pSelected->togglePin();
			}
			return true;
/*		case osgGA::GUIEventAdapter::KEY_Left:
			if (m_pSelectedSwitch)
			{
				updateManipulators();

				m_pSelectedSwitch->setAllChildrenOff();

				m_iManip++;
				if (m_iManip >= (int)m_pSelectedSwitch->getNumChildren()) m_iManip = 0;

				m_pSelectedSwitch->setSingleChildOn(m_iManip);
				((raaVertex*)m_pSelectedSwitch->getParent(0)->getUpdateCallback())->setDraggerTransform((osg::MatrixTransform*)m_pSelectedSwitch->getChild(m_iManip));
			}
			return true;
		case osgGA::GUIEventAdapter::KEY_Right:
			if (m_pSelectedSwitch)
			{
				updateManipulators();

				m_pSelectedSwitch->setAllChildrenOff();

				m_iManip--;
				if (m_iManip<0) m_iManip = m_pSelectedSwitch->getNumChildren() - 1;

				m_pSelectedSwitch->setSingleChildOn(m_iManip);
				((raaVertex*)m_pSelectedSwitch->getParent(0)->getUpdateCallback())->setDraggerTransform((osg::MatrixTransform*)m_pSelectedSwitch->getChild(m_iManip));
			}
			return true;
*/		}
	}
	return false;
}

void raaOSGDataNodeHandler::pick(osgViewer::View* pView, float x, float y)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;

	if (m_pSelected) m_pSelected->select(false);
	m_pSelected = 0;

	if (pView->computeIntersections(x, y, intersections))
	{
		if (intersections.size())
		{
			for (osgUtil::LineSegmentIntersector::Intersections::iterator it = intersections.begin(); it != intersections.end(); it++)
			{
				for (osg::NodePath::const_reverse_iterator rit = it->nodePath.rbegin(); rit != it->nodePath.rend(); rit++)
				{
					if(osg::Group *pGroup=dynamic_cast<osg::Group*>(*rit))
					{
						if (pGroup->getUpdateCallback())
						{
							osg::Callback *pCallback = pGroup->getUpdateCallback();
							if (pCallback->getName()=="raaOSGDataNode")
							{
									raaOSGDataNode *pDataNode = static_cast<raaOSGDataNode*>(pCallback);

									pDataNode->select(true);
									m_pSelected = pDataNode;
									return;
							}
						}
					}
				}
			}
		}
	}
}

void raaOSGDataNodeHandler::setupDragger()
{
/*	m_pDragger = new osgManipulator::Dragger();
	m_pDragger->setupDefaultGeometry();
	m_pDragger->setHandleEvents(true);
//	pDragger->addTransformUpdating(pMT);
	m_pDragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);
//	pDragger->setMatrix(sm_Scale*pMT->getMatrix());
*/
}
