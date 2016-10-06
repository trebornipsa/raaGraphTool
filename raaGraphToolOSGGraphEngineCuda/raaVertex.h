#pragma once

#include <string>

#include <osg/Group>
#include <osg/Material>
#include <osgManipulator/Dragger>
#include <osg/NodeCallback>
#include <osg/MatrixTransform>

#include <raaGraphEngine/raaNode.h>
#include <raaGraphEngine/raaNodeFactory.h>

class raaVertex : public raaNode, osg::NodeCallback
{
	friend class raaVertexFactory;
public:
	static std::string csm_sFont;
	static float csm_AmbCoef;
	static float csm_DiffCoef;
	static float csm_SpecCoef;

	virtual osg::Vec3f getPos();
	virtual void setPos(osg::Vec3f v);

	osg::Group* getGroup();
	void setGroup(osg::Group *pGroup);

	void setIndex(unsigned int uiIndex);
	unsigned int index();

	void setVelocity(osg::Vec3f vVel);
	osg::Vec3f velocity();


	void updateVelocity(osg::Vec3f vForce);

	void setForces(osg::Vec3f vForce=osg::Vec3f(0.0f, 0.0f, 0.0f));
	void addForce(osg::Vec3f vForce);
	osg::Vec3f getForces();

	float update();

	float energy();

	void setActive(bool bActive);
	void setDraggerTransform(osg::MatrixTransform *pDMT);
	virtual void operator()(osg::Node *pNode, osg::NodeVisitor *pNV);

	void toggleFixed();

protected:
	osg::Group *m_pGroup;

	void addDragger(osgManipulator::Dragger *pDragger, osg::Switch *pSwitch, osg::MatrixTransform *pMT);
	osg::Material* makeMaterial(osg::Vec4f vCol);

	raaVertex(std::string sID, std::string sName, raaGraph *pGraph);
	virtual ~raaVertex();
	unsigned int m_uiIndex;

	osg::Vec3f m_vVelocity;
	osg::Vec3f m_vForces;
	float m_fEnergy;

	bool m_bActive;
	osg::MatrixTransform *m_pDraggerTransform;

	bool m_bLocked;

	osg::Switch *m_pMaterialSwitch;
};

class raaVertexFactory : public raaNodeFactory
{
public:
	virtual raaNode* create(std::string sID, std::string sName, raaGraph *pGraph);
};
