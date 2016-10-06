#include <stdlib.h>
#include "raaGraph.h"
#include "raaNode.h"


raaNode::raaNode(std::string sID, std::string sName, raaGraph *pGraph)
{
	m_sID=sID;
	m_sName=sName;
	m_fMass=1.0f;
	m_bFixed=false;
	m_pGraph=pGraph;
	setRandPos();
}

raaNode::~raaNode(void)
{ 
}

std::string raaNode::getName()
{
	return m_sName;
}

std::string raaNode::getID()
{
	return m_sID;
}

void raaNode::setMass( float fMass/*=1.0f*/ )
{
	m_fMass=fMass;
}

float raaNode::mass()
{
	return m_fMass;
}

void raaNode::setFixed( bool bFixed/*=false*/ )
{
	m_bFixed=bFixed;
}

bool raaNode::fixed()
{
	return m_bFixed;
}

osg::Vec3f raaNode::getPos()
{
	return m_vPos;
}

void raaNode::setPos( osg::Vec3f v )
{
	m_vPos=v;
	if(m_pGraph) m_pGraph->updateNode(this, "nodePos");
}

float raaNode::distance(osg::Vec3f v)
{
	osg::Vec3f _v = m_vPos - v;

	return _v.length();
}

raaGraph* raaNode::graph()
{
	return m_pGraph;
}

osg::Vec3f raaNode::randVec( float fMin, float fMax )
{
	return osg::Vec3f(randFloat(fMin, fMax), randFloat(fMin, fMax), randFloat(fMin, fMax));
}

float raaNode::randFloat( float fMin, float fMax )
{
	float f=rand();

	f/=(float)RAND_MAX;
	f*=fMax-fMin;
	f+=fMin;

	return f;
}

void raaNode::setRandPos( float fMin/*=-100.0f*/, float fMax/*=100.0f*/ )
{
	setPos(randVec(fMin, fMax));
}

void raaNode::initClustering()
{
	m_bClusterVisited = false;
	m_bClustered = false;
}
