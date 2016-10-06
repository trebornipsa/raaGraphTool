#pragma once

#include <vector>

#include "raaGraphEngineDefs.h"

class raaNode;
class raaGraph;
class raaEdgeFactory;

class RAAGRAPHENGINE_DLL_DEF raaEdge
{
public:
	friend raaEdgeFactory;	
	friend raaGraph;	

	raaGraph* graph();

	float weight();
	void setWeight(float fWeight);

	raaNode* start();
	raaNode* end();

protected:
	raaEdge(raaNode *pStart, raaNode *pEnd, float fWeight, raaGraph *pGraph);
	virtual ~raaEdge(void);

	raaNode *m_pStart;
	raaNode *m_pEnd;
	float m_fWeight;
	raaGraph *m_pGraph;
};

typedef std::vector<raaEdge*>raaEdges;