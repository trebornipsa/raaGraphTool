#pragma once

#include <osg/NodeCallback>
#include <osg/MatrixTransform>

class raaCudaGraph;

class raaGraphIndexer: public osg::NodeCallback
{
public:
	raaGraphIndexer(int iIndex, raaCudaGraph *pGraph);
	virtual ~raaGraphIndexer(void);
	virtual void operator() (osg::Node *pNode, osg::NodeVisitor *pNV);

protected:
	int m_iIndex;
	osg::MatrixTransform *m_pTransform;
	raaCudaGraph *m_pGraph;
};

