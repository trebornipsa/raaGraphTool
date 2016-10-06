#include "StdAfx.h"

#include "raaUndirectedGraph.h"


raaUndirectedGraph::raaUndirectedGraph(std::string sName) : raaGraph(sName)
{
	m_pVertexGroup=new osg::Group();
	m_pVertexGroup->setName("vertices");
	m_pVertexGroup->ref();
	g_pRoot->addChild(m_pVertexGroup);

	m_pArcGroup=new osg::Group();
	m_pArcGroup->setName("arcs");
	m_pArcGroup->ref();
	g_pRoot->addChild(m_pArcGroup);

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
	m_pGeom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);
	m_pGeom->setUseDisplayList(false);
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
	}
}

raaEdge* raaUndirectedGraph::addEdge(std::string sType, raaNode *pStart, raaNode *pEnd, float fWeight=1.0f)
{
	raaEdge *pEdge=raaGraph::addEdge(sType pStart, pEnd, fWeight)

		if(raaArc *pArc=dynamic_cast<raaArc*>(pEdge))		
		{
			unsigned int uiSize=m_pVerts->size();
			m_pVerts->push_back(pStart->getPos());
			m_pVerts->push_back(pEnd->getPos());

			m_pIndex->push_back(uiSize++);
			m_pIndex->push_back(uiSize++);

			m_pCols->push_back(osg::Vec4f(pArc->weight(), pArc->weight(), pArc->weight(), pArc->weight()));
		}

		return pEdge;
}
