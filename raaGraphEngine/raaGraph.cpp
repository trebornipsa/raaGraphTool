#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "raaGraphEngine.h"
#include "raaGraphSolver.h"
#include "raaGraph.h"


raaGraph::raaGraph(std::string sName)
{
	srand(time(0));

	m_sName=sName;
	m_pSolver=0;
	m_bUnsolved=true;
}

raaGraph::~raaGraph(void)
{

}

raaNode* raaGraph::addNode(std::string sID, std::string sType, std::string sName )
{
	raaNode *pNode=0;
	if(sType.length() && sName.length() && m_mNodes.find(sName)==m_mNodes.end())
	{
		if(raaGraphEngine::instance()->m_mNodeFactories.find(sType)!=raaGraphEngine::instance()->m_mNodeFactories.end()) pNode=raaGraphEngine::instance()->m_mNodeFactories[sType]->create(sID, sName, this);
		else  pNode=raaGraphEngine::instance()->m_mNodeFactories["node"]->create(sID, sName, this);

		m_mNodes[sID]=pNode;
	}

	return pNode;
}

raaNode* raaGraph::getNode( std::string sID)
{
	if(sID.length() && m_mNodes.find(sID)!=m_mNodes.end()) return m_mNodes[sID];

	return 0;
}

raaEdge* raaGraph::addEdge(std::string sType,  raaNode *pStart, raaNode *pEnd, float fWeight/*=1.0f*/ )
{
	raaEdge *pEdge=0;

	if(nodeIsMember(pStart) && nodeIsMember(pEnd) && sType.length())
	{
		if(raaGraphEngine::instance()->m_mEdgeFactories.find(sType)!=raaGraphEngine::instance()->m_mEdgeFactories.end()) pEdge=raaGraphEngine::instance()->m_mEdgeFactories[sType]->create(pStart, pEnd, fWeight, this);
		else  pEdge=raaGraphEngine::instance()->m_mEdgeFactories["edge"]->create(pStart, pEnd, fWeight, this);

		m_mEdges.push_back(pEdge);
	}

	return pEdge;
}

bool raaGraph::nodeIsMember(raaNode *pNode)
{
	if(pNode)
	{
		if(m_mNodes.find(pNode->getID())!=m_mNodes.end()) return true;
	}

	return false;
}

void raaGraph::setIdealEdgeLength( float flen/*=1.0f*/ )
{
	m_fIdealEdgeLen=flen;
}

float raaGraph::idealEdgeLength()
{
	return m_fIdealEdgeLen;
}

void raaGraph::setSolver( raaGraphSolver *pSolver )
{
	if(pSolver)
	{
		if(pSolver!=m_pSolver)
		{
			delete m_pSolver;
			m_pSolver=pSolver;
			m_bUnsolved=true;
		}
	}
	else
	{
		delete m_pSolver;
		m_pSolver=0;
		m_bUnsolved=true;
	}
}

void raaGraph::setSolver( std::string sType )
{
		if(m_pSolver) delete m_pSolver;

		m_pSolver=raaGraphEngine::instance()->getSolver(sType);;
		m_bUnsolved=true;
}

bool raaGraph::solve(unsigned int uiNumIterations)
{
	bool bSolved;

	if(m_pSolver)
	{
		bSolved=m_pSolver->solve(this);
		m_bUnsolved=!bSolved;
		return bSolved;
	}

	std::cout <<"raaGraph: No solver attached" << std::endl;

	return false;
}

bool raaGraph::hasSolution()
{
	return !m_bUnsolved;
}

const raaNodes& raaGraph::nodes()
{
	return m_mNodes;
}

const raaEdges& raaGraph::edges()
{
	return m_mEdges;
}

void raaGraph::updateNode( raaNode *pNode, std::string sUpdate)
{
}

void raaGraph::normaliseEdgeWeights()
{
	float fMax=FLT_MIN;
	float fMin=FLT_MAX;

	for(raaEdges::iterator it=m_mEdges.begin();it!=m_mEdges.end();it++)
	{
		raaEdge *pEdge=(*it);

		fMax=(pEdge->weight()>fMax) ? pEdge->weight() : fMax;
		fMin=(pEdge->weight()<fMin) ? pEdge->weight() : fMin;
	}

	float fRange=fMax-fMin;

	for(raaEdges::iterator it=m_mEdges.begin();it!=m_mEdges.end();it++)
	{
		raaEdge *pEdge=(*it);
		
		pEdge->setWeight((pEdge->weight()-fMin)/fRange);
	}
}

void raaGraph::updateEdge( raaEdge *pEdge, std::string sUpdate )
{

}

float raaGraph::energy()
{
	return 0.0f;
}

void raaGraph::graphToArrays()
{
	
}
