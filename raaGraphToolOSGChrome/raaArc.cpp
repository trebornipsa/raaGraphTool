#include "StdAfx.h"

#include "raaVertex.h"

#include "raaArc.h"

raaEdge* raaArcFactory::create(raaNode *pStart, raaNode *pEnd, float fWeight, raaGraph *pGraph)
{
	return new raaArc(pStart, pEnd, fWeight, pGraph);
}


raaArc::raaArc(raaNode *pStart, raaNode *pEnd, float fWeight, raaGraph *pGraph) : raaEdge(pStart, pEnd, fWeight, pGraph)
{
	m_uiIndex=0;
	m_fIdealLen=3.0f;
	m_fCoefRest=0.1f;
}


raaArc::~raaArc(void)
{
}

void raaArc::setIndex( unsigned int uiIndex )
{
	m_uiIndex=uiIndex;
}

unsigned int raaArc::index()
{
	return m_uiIndex;
}

void raaArc::calcForce()
{
	m_vForce=m_pEnd->getPos()-m_pStart->getPos();
	m_fActualLen=m_vForce.normalize();
	//	m_fForce=(m_fActualLen-m_fIdealLen)*m_fCoefRest;
	m_fForce=(m_fActualLen-m_fIdealLen)*5.0f*m_fWeight;
	m_vForce*=m_fForce;
}

float raaArc::forceVal()
{
	return m_fForce;	
}

osg::Vec3f raaArc::forceVec()
{
	return m_vForce;
}
