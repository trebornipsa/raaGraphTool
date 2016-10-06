#pragma once

#include <osg/NodeCallback>
#include <osg/MatrixTransform>
#include <osg/Geometry>

class raaVertexCallback : public osg::Callback
{
public:
	raaVertexCallback(osg::Geometry *pGeom, unsigned int uiIndex);

	void setTransform(osg::MatrixTransform *pMT);
	void setActive(bool bActive);
	virtual bool run(osg::Object* object, osg::Object* data);
//	virtual void operator()(osg::Node *pNode, osg::NodeVisitor *pNV);

protected:
	virtual ~raaVertexCallback(void);

	osg::MatrixTransform	*m_pMT;
	osg::Geometry *m_pGeom;

	unsigned int m_uiVertexIndex;
	bool m_bActive;
};

