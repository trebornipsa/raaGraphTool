#include "stdafx.h"

#include <windows.h>
#include <gl/gl.h>

#include <osg/Material>
#include <sstream>
#include <EBCNode.h>
#include "raaOSGDataNode.h"

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
#include "raaArcSet.h"
#include "raaClustersSet.h"

osg::Material *raaClustersSet::sm_pNormalMaterial=0;
osg::Material *raaClustersSet::sm_pHighlightMaterial=0;

raaClustersSet::raaClustersSet(raaDataModel *pModel)
{
	m_bClusterBuffer = true;
	m_pModel = pModel;
	m_bDraw = false;
	m_uiNumClusters = 0;

	m_pBase = new osg::Group();
	m_pBase->ref();
	m_pSwitch = new osg::Switch();
	m_pSwitch->setAllChildrenOff();

	m_pMT = new osg::MatrixTransform();
	m_pGeode = new osg::Geode();

	if (!sm_pNormalMaterial)
	{
		sm_pNormalMaterial = new osg::Material();
		sm_pNormalMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.3f, 0.3f, 0.0f, 1.0f));
		sm_pNormalMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.9f, 0.9f, 0.0f, 1.0f));
		sm_pNormalMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.9f, 0.9f, 0.0f, 1.0f));
		sm_pNormalMaterial->setShininess(osg::Material::FRONT_AND_BACK, 10.0f);
		sm_pNormalMaterial->setAlpha(osg::Material::FRONT_AND_BACK, 0.3f);
	}

	if (!sm_pHighlightMaterial)
	{
		sm_pHighlightMaterial = new osg::Material();
		sm_pHighlightMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.3f, 0.0f, 0.0f, 1.0f));
		sm_pHighlightMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
		sm_pHighlightMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.9f, 0.0f, 0.0f, 1.0f));
		sm_pHighlightMaterial->setShininess(osg::Material::FRONT_AND_BACK, 10.0f);
		sm_pHighlightMaterial->setAlpha(osg::Material::FRONT_AND_BACK, 0.3f);
	}

	m_pBase->addChild(m_pSwitch);
	m_pSwitch->addChild(m_pMT);
	m_pMT->addChild(m_pGeode);
//	m_pGeode->getOrCreateStateSet()->setAttributeAndModes(sm_pNormalMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
}

raaClustersSet::~raaClustersSet()
{
	if (m_pBase) m_pBase->unref();
}

osg::Group* raaClustersSet::clusterGroup()
{
	return m_pBase;
}

void raaClustersSet::setModel(raaDataModel* pModel)
{
	m_pModel = pModel;
}

void raaClustersSet::genClusterGeom()
{
	if (m_pModel && m_bDraw)
	{
		m_mClusters[!m_bClusterBuffer].clear();
		while(m_vGeoms.size()<m_pModel->clusterSet().size())
		{
			osg::Geometry *pGeom = new osg::Geometry();
			pGeom->ref();
			pGeom->setUseDisplayList(false);
			pGeom->setName("raaOSGMouseOverData");
			pGeom->setUserData(this);
			m_vGeoms.push_back(pGeom);
		}

		m_pGeode->removeDrawables(0, m_pGeode->getNumDrawables());
		for (unsigned int i = 0; i < m_pModel->clusterSet().size(); i++) m_pGeode->addDrawable(m_vGeoms[i]);

		m_uiNumClusters = m_pModel->clusterSet().size();
		unsigned int uiCluster = 0;
		for (raaClusterSet::const_iterator csit = m_pModel->clusterSet().begin(); csit != m_pModel->clusterSet().end(); csit++, uiCluster++)
		{
			coordT *points = new coordT[csit->size() * 3];
			coordT *p = points;
			boolT isMalloc = false;
			char flags[] = "qhull QbB Qt Pp";

			for (raaCluster::const_iterator it = csit->begin(); it != csit->end(); it++)
			{
				*p++ = (*it)->position()[0];
				*p++ = (*it)->position()[1];
				*p++ = (*it)->position()[2];
				m_mClusters[!m_bClusterBuffer][uiCluster].push_back((raaOSGDataNode*)(*it));
			}

			qh_new_qhull(3, csit->size(), points, isMalloc, flags, 0, 0);

			facetT *facet;
			vertexT *vertex, **vertexp;

			osg::Vec3Array *pVerts = new osg::Vec3Array();
			osg::Vec3Array *pNorms = new osg::Vec3Array();
			pNorms->setNormalize(true);

			FORALLfacets
			{
				pNorms->push_back(osg::Vec3f(facet->normal[0], facet->normal[1], facet->normal[2]));
				pNorms->push_back(osg::Vec3f(facet->normal[0], facet->normal[1], facet->normal[2]));
				pNorms->push_back(osg::Vec3f(facet->normal[0], facet->normal[1], facet->normal[2]));

				FOREACHvertex_(facet->vertices)
				{
					pVerts->push_back(osg::Vec3f(m_mClusters[!m_bClusterBuffer][uiCluster][qh_pointid(vertex->point)]->position().get()[0], m_mClusters[!m_bClusterBuffer][uiCluster][qh_pointid(vertex->point)]->position().get()[1], m_mClusters[!m_bClusterBuffer][uiCluster][qh_pointid(vertex->point)]->position().get()[2]));
				}
			}

			osg::Geometry *pGeom = m_vGeoms[uiCluster];		
			pGeom->getOrCreateStateSet()->setAttributeAndModes(sm_pNormalMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			pGeom->setVertexArray(pVerts);
			pGeom->setNormalArray(pNorms, osg::Array::BIND_PER_VERTEX);
			pGeom->removePrimitiveSet(0, pGeom->getNumPrimitiveSets());
			pGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, pVerts->size()));
		}
		m_bClusterBuffer = !m_bClusterBuffer;
	}
}

void raaClustersSet::drawCluster(bool bDraw)
{
	m_bDraw = bDraw;

	if(m_pSwitch)
	{
		if (m_bDraw) m_pSwitch->setAllChildrenOn();
		else
		{
			m_pSwitch->setAllChildrenOff();
			m_uiNumClusters = 0;
		}
	}
}

unsigned raaClustersSet::numClusters()
{
	return m_uiNumClusters;
}

std::string raaClustersSet::getDescription(osg::Drawable* pDrawable)
{
	std::stringstream sClusterDesc;

	if(m_pGeode && pDrawable)
	{
		unsigned int uiCluster = 0;	
		unsigned int uiIndex = std::find(m_vGeoms.begin(), m_vGeoms.end(), pDrawable)- m_vGeoms.begin();
//		pDrawable->getOrCreateStateSet()->setAttributeAndModes(sm_pHighlightMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

		sClusterDesc << "Cluster -> " << uiIndex << "\n";
		for (unsigned int i = 0; i < m_mClusters[m_bClusterBuffer][uiIndex].size();i++) sClusterDesc << "--->" << m_mClusters[m_bClusterBuffer][uiIndex][i]->description() << "\n";
	}
	return  sClusterDesc.str();
}
