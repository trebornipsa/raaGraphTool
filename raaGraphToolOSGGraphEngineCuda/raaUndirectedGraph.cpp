#include "StdAfx.h"

#include <iostream>

#include <osg/BlendFunc>

#include <raaGraphEngine/raaNode.h>
#include <raaGraphEngine/raaEdge.h>

#include "raaArc.h"
#include "raaVertex.h"
#include "raaUndirectedGraph.h"

raaGraph* raaUndirectedGraphFactory::create(std::string sName)
{
	return new raaUndirectedGraph(sName, m_pRoot);
}

void raaUndirectedGraphFactory::setRoot( osg::Group *pRoot )
{
	m_pRoot=pRoot;	
}

raaUndirectedGraph::raaUndirectedGraph(std::string sName, osg::Group *pRoot) : raaGraph(sName)
{
	m_bContSolve=false;
	m_fEnergy=0.0f;
	m_pVertexGroup=new osg::Group();
	m_pVertexGroup->setName("vertices");
	m_pVertexGroup->ref();
	pRoot->addChild(m_pVertexGroup);
	pRoot->setUpdateCallback(this);

	m_pArcGroup=new osg::Group();
	m_pArcGroup->setName("arcs");
	m_pArcGroup->ref();
	pRoot->addChild(m_pArcGroup);

	osg::Geode *pGeode=new osg::Geode();
	m_pArcGroup->addChild(pGeode);

	m_pGeom=new osg::Geometry();
	pGeode->addDrawable(m_pGeom);

	pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::OVERRIDE);
	pGeode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	osg::BlendFunc *pBF=new osg::BlendFunc(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);

	pGeode->getOrCreateStateSet()->setAttributeAndModes(pBF, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	pGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	m_pVerts=new osg::Vec3Array();
	m_pIndex=new osg::DrawElementsUByte(osg::PrimitiveSet::LINES, 0);
	m_pCols=new osg::Vec4Array();

	m_pGeom->setVertexArray(m_pVerts);
	m_pGeom->setColorArray(m_pCols);
	m_pGeom->addPrimitiveSet(m_pIndex);
//	m_pGeom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
	m_pGeom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
	m_pGeom->setUseDisplayList(false);
	m_uiVertex=0;
	m_uiArc=0;
}

raaUndirectedGraph::~raaUndirectedGraph(void)
{
}

raaNode* raaUndirectedGraph::addNode(std::string sID, std::string sType, std::string sName)
{
	raaNode *pNode=raaGraph::addNode(sID, sType, sName);

	if(class raaVertex *pVert=dynamic_cast<class raaVertex*>(pNode))
	{
		m_pVertexGroup->addChild(pVert->getGroup());
		m_pVerts->push_back(pVert->getPos());
		pVert->setIndex(m_uiVertex++);
	}
	return pNode;
}

raaEdge* raaUndirectedGraph::addEdge(std::string sType, raaNode *pStart, raaNode *pEnd, float fWeight)
{
	raaEdge *pEdge=raaGraph::addEdge(sType, pStart, pEnd, fWeight);

	raaArc *pArc=dynamic_cast<raaArc*>(pEdge);
	raaVertex *pVStart=dynamic_cast<raaVertex*>(pStart);
	raaVertex *pVEnd=dynamic_cast<raaVertex*>(pEnd);

	if(pArc && pVStart && pVEnd)
	{
		m_pIndex->push_back(pVStart->index());
		m_pIndex->push_back(pVEnd->index());

		float f=(fWeight*0.7f)+0.3f;
		m_pCols->push_back(osg::Vec4f(f,f,f,f));
		pArc->setIndex(m_uiArc++);
	}

	return pEdge;
}

void raaUndirectedGraph::updateNode( raaNode *pNode, std::string sUpdate)
{
	if(sUpdate=="nodePos")
	{
		if(raaVertex *pVert=dynamic_cast<raaVertex*>(pNode)) m_pVerts->asVector()[pVert->index()]=pVert->getPos();
	}
	else
		raaGraph::updateNode(pNode, sUpdate);
}

void raaUndirectedGraph::updateEdge( raaEdge *pEdge, std::string sUpdate )
{
	if(sUpdate=="edgeWeight")
	{
		if(raaArc *pArc=dynamic_cast<raaArc*>(pEdge))
		{
			float f=(pArc->weight()*0.7f)+0.3f;
			m_pCols->asVector()[pArc->index()]=osg::Vec4f(f,f,f,f);
		}
	}
	else
		raaGraph::updateEdge(pEdge, sUpdate);
}

bool raaUndirectedGraph::solve( unsigned int uiNumIterations )
{
	for(unsigned int i=0;i<uiNumIterations;i++)
	{
		for(raaEdges::iterator it=m_mEdges.begin();it!=m_mEdges.end();it++)
		{
			raaArc *pArc=dynamic_cast<raaArc*>(*it);

			if(pArc) pArc->calcForce(); 
		}

		for(raaNodes::iterator it=m_mNodes.begin();it!=m_mNodes.end();it++)
		{
			raaVertex *pVert=dynamic_cast<raaVertex*>(it->second);

			if(pVert) pVert->setForces();
		}

		for(raaEdges::iterator it=m_mEdges.begin();it!=m_mEdges.end();it++)
		{
			raaArc *pArc=dynamic_cast<raaArc*>(*it);

			if(pArc)
			{
				if(raaVertex *pStart=dynamic_cast<raaVertex*>(pArc->start())) pStart->addForce(pArc->forceVec());
				if(raaVertex *pEnd=dynamic_cast<raaVertex*>(pArc->end())) pEnd->addForce(pArc->forceVec()*-1.0f);
			}
		}

		// repulsive forces

		for(raaNodes::iterator it=m_mNodes.begin();it!=m_mNodes.end();it++)
		{
			raaVertex *pStart=dynamic_cast<raaVertex*>(it->second);

			raaNodes::iterator itt=it;
			for(itt++;itt!=m_mNodes.end();itt++)
			{
				raaVertex *pEnd=dynamic_cast<raaVertex*>(itt->second);

				if(pStart && pEnd)
				{
					osg::Vec3f v=pEnd->getPos()-pStart->getPos();
					float fDist=v.normalize();
					float f=1.0f/(fDist*fDist);
					f*=0.00002f;
					v=v*f;
					pStart->addForce(v);
					pEnd->addForce(v*-1.0f);
				}
			}
		}

		m_fEnergy=0.0f;
		for(raaNodes::iterator it=m_mNodes.begin();it!=m_mNodes.end();it++)
		{
			raaVertex *pVert=dynamic_cast<raaVertex*>(it->second);

			if(pVert) m_fEnergy+=pVert->update();
		}
	}
	return true;
}

float raaUndirectedGraph::energy()
{
	return m_fEnergy;
}

void raaUndirectedGraph::operator()( osg::Node *pNode, osg::NodeVisitor *pNV )
{
	if(m_bContSolve)
	{
		solve(1);	
	
		std::cout << "Energy: " << m_fEnergy << std::endl;
	}
	pNV->traverse(*pNode);
}

void raaUndirectedGraph::contSolve( bool bCont )
{
	m_bContSolve=bCont;
}

void raaUndirectedGraph::applyMasses()
{
	for(raaNodes::iterator it=m_mNodes.begin();it!=m_mNodes.end();it++)
	{
		raaVertex *pVert=dynamic_cast<raaVertex*>(it->second);
		
		if(pVert) pVert->setMass(0.0f);
	}

	for(raaEdges::iterator it=m_mEdges.begin();it!=m_mEdges.end();it++)
	{
		raaArc *pArc=dynamic_cast<raaArc*>(*it);

		if(pArc)
		{
			if(raaVertex *pStart=dynamic_cast<raaVertex*>(pArc->start())) pStart->setMass(pStart->mass()+pArc->weight());
			if(raaVertex *pEnd=dynamic_cast<raaVertex*>(pArc->end())) pEnd->setMass(pEnd->mass()+pArc->weight());
		}
	}
}
