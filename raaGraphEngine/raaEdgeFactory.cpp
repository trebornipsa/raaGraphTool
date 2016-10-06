#include "raaEdge.h"
#include "raaEdgeFactory.h"


raaEdgeFactory::raaEdgeFactory(void)
{
}


raaEdgeFactory::~raaEdgeFactory(void)
{
}

raaEdge* raaEdgeFactory::create( raaNode *pStart, raaNode *pEnd, float fWeight, raaGraph *pGraph )
{
	return new raaEdge(pStart, pEnd, fWeight, pGraph);
}
