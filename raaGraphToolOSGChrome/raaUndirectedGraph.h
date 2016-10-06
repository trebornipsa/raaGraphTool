#pragma once

#include <string>

#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>


#include <raaGraphEngine/raaGraph.h>
#include <raaGraphEngine/raaGraphFactory.h>

class raaUndirectedGraph : public raaGraph, osg::NodeCallback
{
	friend class raaUndirectedGraphFactory;
public:
	virtual raaNode* addNode(std::string sID, std::string sType, std::string sName);
	virtual raaEdge* addEdge(std::string sType, raaNode *pStart, raaNode *pEnd, float fWeight=1.0f);
	
	virtual void updateNode(raaNode *pNode, std::string sUpdate);
	virtual void updateEdge(raaEdge *pEdge, std::string sUpdate);

	virtual bool solve(unsigned int uiNumIterations);

	virtual float energy();
	virtual void operator()(osg::Node *pNode, osg::NodeVisitor *pNV);

	void contSolve(bool bCont);

	void applyMasses();

protected:
	raaUndirectedGraph(std::string sName, osg::Group *pRoot);

	virtual ~raaUndirectedGraph();

	osg::Group *m_pArcGroup;
	osg::Group *m_pVertexGroup;
	osg::Geometry *m_pGeom;
	osg::Vec4Array *m_pCols;
	osg::Vec3Array *m_pVerts;
	osg::DrawElementsUByte *m_pIndex;

	unsigned int m_uiVertex;
	unsigned int m_uiArc;

	float m_fEnergy;
	bool m_bContSolve;
};

class raaUndirectedGraphFactory : public raaGraphFactory
{
public:
	virtual raaGraph* create(std::string sName);
	void setRoot(osg::Group *pRoot);
protected:
	osg::Group *m_pRoot;

};
