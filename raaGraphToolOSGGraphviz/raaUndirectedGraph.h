#pragma once

#include <string>

#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>


#include <raaGraphEngine/raaGraph.h>
#include <raaGraphEngine/raaGraphFactory.h>

class raaUndirectedGraph : public raaGraph
{
	friend class raaUndirectedGraphFactory;
public:
	virtual raaNode* addNode( std::string sID, std::string sType, std::string sName);
	virtual raaEdge* addEdge(std::string sType, raaNode *pStart, raaNode *pEnd, float fWeight=1.0f);

protected:
	raaUndirectedGraph(std::string sName);

	virtual ~raaUndirectedGraph();

	osg::Group *m_pArcGroup;
	osg::Group *m_pVertexGroup;
	osg::Geometry *m_pGeom;
	osg::Vec4Array *m_pCols;
	osg::Vec3Array *m_pVerts;
	osg::DrawElementsUByte *m_pIndex;
};

class raaUndirectedGraphFactory : public raaGraphFactory
{
public:
	virtual raaGraph* create(std::string sName)
	{
		return new raaUndirectedGraph(sName);
	}
};
