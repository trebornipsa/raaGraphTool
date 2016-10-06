#pragma once

#include <osg/NodeCallback>
#include <osg/MatrixTransform>
#include <osg/Geometry>

class raaVertexCallback : public osg::NodeCallback
{
public:
	raaVertexCallback(osg::MatrixTransform *pMT, unsigned int uiIndex);

	void setTransform(osg::MatrixTransform *pMT);
	void setActive(bool bActive);

	virtual void operator()(osg::Node *pNode, osg::NodeVisitor *pNV);

protected:
	virtual ~raaVertexCallback(void);

	osg::MatrixTransform	*m_pMT;
	osg::Geometry *m_pGeom;

	int m_iVertexIndex;
	bool m_bActive;
};

