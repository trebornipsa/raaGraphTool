#pragma once

#include <osg/vec3f>

#include <raaGraphEngine/raaEdge.h>
#include <raaGraphEngine/raaEdgeFactory.h>

class raaNode;

class raaArc : public raaEdge
{
	friend class raaArcFactory;
public:
	void calcForce();

	float forceVal();
	osg::Vec3f forceVec();

	void setIndex(unsigned int uiIndex);
	unsigned int index();
protected:
	raaArc(raaNode *pStart, raaNode *pEnd, float fWeight, raaGraph *pGraph);
	virtual ~raaArc();

	unsigned int m_uiIndex;

	float m_fIdealLen;
	float m_fActualLen;
	float m_fForce;
	osg::Vec3f m_vForce;
	float m_fCoefRest;
};

class raaArcFactory : public raaEdgeFactory
{
public:
	virtual raaEdge* create(raaNode *pStart, raaNode *pEnd, float fWeight=1.0f, raaGraph *pGraph=0);
};

