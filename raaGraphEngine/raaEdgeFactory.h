#pragma once

#include <string>
#include <map>

#include "raaGraphEngineDefs.h"

class raaEdge;
class raaNode;
class raaGraph;

class RAAGRAPHENGINE_DLL_DEF raaEdgeFactory
{
public:
	raaEdgeFactory(void);
	~raaEdgeFactory(void);
	virtual raaEdge* create(raaNode *pStart, raaNode *pEnd, float fWeight=1.0f, raaGraph *pGraph=0);
};

typedef std::map<std::string, raaEdgeFactory*>raaEdgeFactories;