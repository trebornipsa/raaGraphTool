#include "StdAfx.h"
#include "raaArc.h"

raaEdge* raaArcFactory::create(raaNode *pStart, raaNode *pEnd, float fWeight=1.0f, raaGraph *pGraph)
{
	return new raaArc(pStart, pEnd, fWeight, pGraph);
}


raaArc::raaArc(raaNode *pStart, raaNode *pEnd, float fWeight, raaGraph *pGraph) : raaEdge(pStart, pEnd, fWeight, pGraph)
{
}


raaArc::~raaArc(void)
{
}
