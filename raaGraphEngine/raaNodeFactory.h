#pragma once

#include <string>
#include <map>

#include "raaGraphEngineDefs.h"

class raaNode;
class raaGraph;

class RAAGRAPHENGINE_DLL_DEF raaNodeFactory
{
public:
	raaNodeFactory(void);
	virtual ~raaNodeFactory(void);

	virtual raaNode* create(std::string sID, std::string sName, raaGraph *pGraph);
};

typedef std::map<std::string, raaNodeFactory*>raaNodeFactories;

