#include "StdAfx.h"
#include "raaVertexCallback.h"


raaVertexCallback::raaVertexCallback(osg::Geometry *pGeom, unsigned int uiIndex)
{
	m_uiVertexIndex=uiIndex;
	m_pMT=0;
	m_pGeom=pGeom;
	m_bActive=false;
}


raaVertexCallback::~raaVertexCallback(void)
{
}

void raaVertexCallback::setTransform( osg::MatrixTransform *pMT )
{
	m_pMT=pMT;
}

void raaVertexCallback::setActive( bool bActive )
{
	m_bActive=bActive;
}

void raaVertexCallback::operator()( osg::Node *pNode, osg::NodeVisitor *pNV )
{
	if(m_bActive && m_pMT && m_pGeom)
	{
		osg::Vec3f v=m_pMT->getMatrix().getTrans();

		((float*)m_pGeom->getVertexArray()->getDataPointer())[3*m_uiVertexIndex]=v[0];
		((float*)m_pGeom->getVertexArray()->getDataPointer())[3*m_uiVertexIndex+1]=v[1];
		((float*)m_pGeom->getVertexArray()->getDataPointer())[3*m_uiVertexIndex+2]=v[2];
		m_pGeom->getVertexArray()->dirty();
		m_pGeom->dirtyDisplayList();
	}
	else pNV->traverse(*pNode);
}
