#pragma once

#include <map>
#include <string>

#include "raaGraphEngineDefs.h"

class raaGraph;

class RAAGRAPHENGINE_DLL_DEF raaGraphFactory
{
public:
	raaGraphFactory();
	virtual ~raaGraphFactory(void);

	virtual raaGraph* create(std::string sName);
};

typedef std::map<std::string, raaGraphFactory*>raaGraphFactories;