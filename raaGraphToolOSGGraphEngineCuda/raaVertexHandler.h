#pragma once
#include <osgGA/GUIEventHandler>

#include <osg/Group>
#include <osg/Switch>
#include <osg/ShapeDrawable>
#include <osgManipulator/Dragger>
#include <osgText/Text>
#include <osgViewer/Viewer>


class raaVertexHandler: public osgGA::GUIEventHandler
{
public:
	raaVertexHandler(osg::Group *pRoot);
	virtual ~raaVertexHandler(void);

	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);
	virtual void pick(osgViewer::View* pView, float x, float y);

	static osg::Matrixf sm_Scale;
	static osg::Matrixf sm_InvScale;

protected:
	osg::Group *m_pRoot;

	osg::Switch *m_pSelectedSwitch;
	int m_iManip;


	void updateManipulators();
	void addDragger(osgManipulator::Dragger *pDragger, osg::Switch *pSwitch, osg::MatrixTransform *pMT);

};

