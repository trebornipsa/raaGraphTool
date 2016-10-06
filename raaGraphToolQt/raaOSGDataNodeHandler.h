#pragma once

#include <osgGA/GUIEventHandler>
#include <osgViewer/View>
#include <osgManipulator/Dragger>

class raaOSGDataNode;

class raaOSGDataNodeHandler : public osgGA::GUIEventHandler
{
public:
	raaOSGDataNodeHandler();
	virtual ~raaOSGDataNodeHandler();

	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);
	virtual void pick(osgViewer::View* pView, float x, float y);

protected:
	osgManipulator::Dragger *m_pDragger;
	raaOSGDataNode *m_pSelected;

	void setupDragger();

	osg::Matrixf m_Scale;
	osg::Matrixf m_InvScale;

};

