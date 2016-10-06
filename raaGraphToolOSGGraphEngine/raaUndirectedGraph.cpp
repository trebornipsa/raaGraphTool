#include "StdAfx.h"


#include <iostream>

#include <osg/BlendFunc>

#include <raaGraphEngine/raaNode.h>
#include <raaGraphEngine/raaEdge.h>

extern "C" {
#include <libqhull/user.h>
#include <libqhull/libqhull.h>
#include <libqhull/mem.h>
#include <libqhull/qset.h>
#include <libqhull/qhull_a.h>
#include <libqhull/geom.h>
#include <libqhull/merge.h>
#include <libqhull/poly.h>
#include <libqhull/io.h>
#include <libqhull/stat.h>

}

#include "raaArc.h"
#include "raaVertex.h"
#include "raaUndirectedGraph.h"

void raaUndirectedGraph::cluster()
{
	for (raaNodes::iterator it = m_mNodes.begin(); it != m_mNodes.end(); it++) it->second->initClustering();

	m_lNoise.clear();
	m_mClusters.clear();
	int iClusters = 0;

	for (raaNodes::iterator it = m_mNodes.begin(); it != m_mNodes.end(); it++)
	{
		raaNode *pN = it->second;

		pN->m_bClusterVisited = true;

		raaNodeList pts;
		clusterRegion(pN, pts);

		if (pts.size() < m_iMinClusterSize) m_lNoise.push_back(pN);
		else
		{
			m_mClusters[iClusters] = pts;
			m_mClusters[iClusters].push_back(pN);

			int i = 0;
			for (raaNodeList::iterator it2 = pts.begin(); it2 != pts.end(); it2++)
			{
				raaNode *p = (*it2);

				if(!p->m_bClusterVisited)
				{
					p->m_bClusterVisited = true;
					raaNodeList _pts;
					clusterRegion(p, _pts);
					
					if (_pts.size() >= m_iMinClusterSize) pts.splice(pts.end(), _pts);
				}

				if(!p->m_bClustered)
				{
					m_mClusters[iClusters].push_back(p);
					p->m_bClustered = true;
				}
			}

			iClusters++;
		}
	}

	if (m_pDrawable)
	{
		m_pDrawable->m_vNorms.clear();
		m_pDrawable->m_vVerts.clear();

		for (int i = 0; i < iClusters; i++)
		{
			coordT *points = new coordT[m_mClusters[i].size() * 3];
			coordT *p = points;
			boolT isMalloc = false;
			char flags[] = "qhull Tv QbB Qt";
			raaNodeArray a;

			int iIndex = 0;
			for (raaNodeList::iterator it = m_mClusters[i].begin(); it != m_mClusters[i].end(); it++, iIndex++)
			{
				*p++ = (*it)->getPos()[0];
				*p++ = (*it)->getPos()[1];
				*p++ = (*it)->getPos()[2];
				a[iIndex] = (*it);
			}

			qh_new_qhull(3, m_mClusters[i].size(), points, isMalloc, flags, 0, 0);

			facetT *facet;
			vertexT *vertex, **vertexp;
			int k;

//			printf("\n%d vertices and %d facets with normals:\n", qh num_vertices, qh num_facets);

			FORALLfacets
			{
				m_pDrawable->m_vNorms.push_back(facet->normal[0]);
				m_pDrawable->m_vNorms.push_back(facet->normal[1]);
				m_pDrawable->m_vNorms.push_back(facet->normal[2]);
//			printf("%6.2g %6.2g %6.2g\n", facet->normal[0], facet->normal[1], facet->normal[2]);


				FOREACHvertex_(facet->vertices)
				{
					raaNode *pNV = a[qh_pointid(vertex->point)];

					m_pDrawable->m_vVerts.push_back(pNV->getPos()[0]);
					m_pDrawable->m_vVerts.push_back(pNV->getPos()[1]);
					m_pDrawable->m_vVerts.push_back(pNV->getPos()[2]);

//					printf("\t%6.2g %6.2g %6.2g\n", pNV->getPos()[0], pNV->getPos()[1], pNV->getPos()[2]);
				}
			}
//			printf("\n");
		}
	}
}

raaGraph* raaUndirectedGraphFactory::create(std::string sName)
{
	return new raaUndirectedGraph(sName, m_pRoot);
}

void raaUndirectedGraphFactory::setRoot( osg::Group *pRoot )
{
	m_pRoot=pRoot;	
}

void raaUndirectedGraph::clusterRegion(raaNode* pNodeTarget,raaNodeList& l)
{
	for (raaNodes::iterator it = m_mNodes.begin(); it != m_mNodes.end();it++)
	{
		raaNode *pN = it->second;

		if (pN != pNodeTarget && distance(pN, pNodeTarget) < m_fEPS) l.push_back(pN);
	}
}

float raaUndirectedGraph::distance(raaNode* pN1, raaNode* pN2)
{
	osg::Vec3f v = pN1->getPos() - pN2->getPos();
	return fabs(v.length());
}

float raaUndirectedGraph::distance(osg::Vec3f vOrigin, raaNode* pN2)
{
	osg::Vec3f v = vOrigin - pN2->getPos();
	return fabs(v.length());
}

raaUndirectedGraph::raaUndirectedGraph(std::string sName, osg::Group *pRoot) : raaGraph(sName)
{
	m_fEPS = 1.0f;
	m_iMinClusterSize = 5;
	m_bContSolve=false;
	m_fEnergy=0.0f;
	m_pVertexGroup=new osg::Group();
	m_pVertexGroup->setName("vertices");
	m_pVertexGroup->ref();
	pRoot->addChild(m_pVertexGroup);
	pRoot->setUpdateCallback(this);
	m_pClusterSwitch = 0;
	m_pClusterGroup = 0;
	m_pClusterGeode = 0;
	m_pClusterShapeDrawable = 0;

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


	pRoot->addChild(createClusterRender());
}

raaUndirectedGraph::~raaUndirectedGraph(void)
{
	if (m_pClusterSwitch) m_pClusterSwitch->unref();
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

		float f=(fWeight*0.4f)+0.6f;
		m_pCols->push_back(osg::Vec4f(f,0.3f,f,f));
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
			float f=(pArc->weight()*0.4f)+0.6f;
			m_pCols->asVector()[pArc->index()]=osg::Vec4f(f,f,f,f*0.3f);
		}
	}
	else
		raaGraph::updateEdge(pEdge, sUpdate);
}

bool raaUndirectedGraph::solve( unsigned int uiNumIterations )
{
	for(unsigned int i=0;i<uiNumIterations;i++)
	{
//		#pragma omp parallel
		for(raaEdges::iterator it=m_mEdges.begin();it!=m_mEdges.end();it++)
		{
			raaArc *pArc=dynamic_cast<raaArc*>(*it);

			if(pArc) pArc->calcForce(); 
		}
		
//		#pragma omp parallel
		for(raaNodes::iterator it=m_mNodes.begin();it!=m_mNodes.end();it++)
		{
			raaVertex *pVert=dynamic_cast<raaVertex*>(it->second);

			if(pVert) pVert->setForces();
		}

//		#pragma omp parallel
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

//		#pragma omp parallel
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


		cluster();

		m_fEnergy=0.0f;
//		m_fRadius = 0.0f;
		m_vCentre = osg::Vec3f(0.0, 0.0, 0.0);
		
//		#pragma omp parallel
		for(raaNodes::iterator it=m_mNodes.begin();it!=m_mNodes.end();it++)
		{
			raaVertex *pVert=dynamic_cast<raaVertex*>(it->second);

			if(pVert) m_fEnergy+=pVert->update();

			m_vCentre += pVert->getPos();
		}

		m_vCentre = m_vCentre / ((float)m_mNodes.size());

		if(m_pClusterShapeDrawable)
		{
			((osg::Sphere*)m_pClusterShapeDrawable->getShape())->setCenter(m_vCentre);
		}

//		#pragma omp parallel
//		for (raaNodes::iterator it = m_mNodes.begin(); it != m_mNodes.end(); it++)
//		{
//			float fDist = distance(m_vCentre, it->second);
//			if (fDist > m_fRadius) m_fRadius = fDist;
//		}
/*
		if (m_pClusterShapeDrawable)
		{
			m_pDrawable->setData(m_fRadius, m_vCentre);
		}
*/

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

osg::Switch* raaUndirectedGraph::createClusterRender()
{
	if (!m_pClusterSwitch)
	{
		m_pClusterSwitch = new osg::Switch();
		m_pClusterSwitch->ref();
		m_pClusterSwitch->setSingleChildOn(0);

//		m_pClusterSwitch->setAllChildrenOff();

		m_pClusterGroup = new osg::Group();
		m_pClusterGeode = new osg::Geode();

		m_pClusterShapeDrawable = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), 0.1f));

		m_pClusterSwitch->addChild(m_pClusterGroup);
		m_pClusterGroup->addChild(m_pClusterGeode);
		m_pClusterGeode->addDrawable(m_pClusterShapeDrawable);
		m_pClusterGeode->setDataVariance(osg::Object::DataVariance::DYNAMIC);
		m_pClusterShapeDrawable->setDataVariance(osg::Object::DataVariance::DYNAMIC);
		m_pClusterShapeDrawable->setUseDisplayList(false);

		osg::Material *pMaterial = new osg::Material();
		pMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.3, 0.3, 0.0, 0.3));
		pMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8, 0.8, 0.0, 0.3));
		pMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.7, 0.7, 0.0, 0.4));
		pMaterial->setShininess(osg::Material::FRONT_AND_BACK, 1.3);

		m_pDrawable = new raaDrawable();

		m_pClusterShapeDrawable->setDrawCallback(m_pDrawable);
		m_pClusterShapeDrawable->setCullCallback(new raaCull());

		m_pClusterGeode->getOrCreateStateSet()->setAttributeAndModes(pMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

		m_pClusterGeode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

		osg::BlendFunc *pBF = new osg::BlendFunc(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);

		m_pClusterGeode->getOrCreateStateSet()->setAttributeAndModes(pBF, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		m_pClusterGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);


		
	}
	return m_pClusterSwitch;
}