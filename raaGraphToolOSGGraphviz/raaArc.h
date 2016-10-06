#pragma once

#include <raaGraphEngine/raaEdge.h>
#include <raaGraphEngine/raaEdgeFactory.h>

class raaNode;

class raaArc : public raaEdge
{
	friend class raaArcFactory;
public:

protected:
	raaArc(raaNode *pStart, raaNode *pEnd, float fWeight, raaGraph *pGraph)
	virtual ~raaArc();
};

class raaArcFactory : public raaEdgeFactory
{
public:
	virtual raaEdge* create(raaNode *pStart, raaNode *pEnd, float fWeight=1.0f, raaGraph *pGraph);
};

