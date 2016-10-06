#include "stdafx.h"
#include "raaCudaGraph.h"
#include "raaGraphIndexer.h"

raaGraphIndexer::raaGraphIndexer(int iIndex, raaCudaGraph *pGraph)
{
	m_pGraph=pGraph;
	m_iIndex=iIndex;
}


raaGraphIndexer::~raaGraphIndexer(void)
{
}

void raaGraphIndexer::operator()( osg::Node *pNode, osg::NodeVisitor *pNV )
{

	if(m_pGraph)
	{
		osg::MatrixTransform *pMT=dynamic_cast<osg::MatrixTransform*>(pNode);
		if(pMT)
		{
			osg::Vec3f v(m_pGraph->vertexArray()[3*m_iIndex], m_pGraph->vertexArray()[3*m_iIndex+1], m_pGraph->vertexArray()[3*m_iIndex+2]);
			osg::Matrixf m;
			m.makeTranslate(v);
			pMT->setMatrix(m);
		}
	}


	pNV->traverse(*pNode); 
}
