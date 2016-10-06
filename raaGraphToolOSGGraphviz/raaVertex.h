#pragma once

#include <raaGraphEngine/raaNode.h>
#include <raaGraphEngine/raaNodeFactory.h>

class raaVertex : public raaNode
{
	friend class raaVertexFactory;
public:
	virtual osg::Vec3f getPos();
	virtual void setPos(osg::Vec3f v);

	osg::Group* getGroup();
	void setGroup(osg::Group *pGroup);

protected:
	osg::Group *m_pGroup;

	void addDragger(osgManipulator::Dragger *pDragger, osg::Switch *pSwitch, osg::MatrixTransform *pMT);
	osg::Material* makeMaterial(osg::Vec4f vCol);

	raaVertex(std::string sName, raaGraph *pGraph) : raaNode(sName, pGraph);
	virtual ~raaVertex();
};

class raaVertexFactory : public raaNodeFactory
{
public:
	virtual raaNode* create(std::string sName, raaGraph *pGraph);
};
