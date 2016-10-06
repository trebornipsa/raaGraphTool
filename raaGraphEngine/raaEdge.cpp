#include "raaGraph.h"
#include "raaEdge.h"

raaEdge::raaEdge(raaNode *pStart, raaNode *pEnd, float fWeight, raaGraph *pGraph)
{
	m_pStart=pStart;
	m_pEnd=pEnd;
	m_fWeight=fWeight;
	m_pGraph=pGraph;
}


raaEdge::~raaEdge(void)
{
}

raaGraph* raaEdge::graph()
{
	return m_pGraph;
}

float raaEdge::weight()
{
	return m_fWeight;
}

void raaEdge::setWeight( float fWeight )
{
	m_fWeight=fWeight;
	if(m_pGraph) m_pGraph->updateEdge(this, "edgeWeight");
}

raaNode* raaEdge::start()
{
	return m_pStart;
}

raaNode* raaEdge::end()
{
	return m_pEnd;
}
