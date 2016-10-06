#pragma once

#include <map>
#include <string>

#include "raaGraphEngineDefs.h"

class raaGraphSolver;

class RAAGRAPHENGINE_DLL_DEF raaGraphSolverFactory
{
public:
	raaGraphSolverFactory(void);
	virtual ~raaGraphSolverFactory(void);

	virtual raaGraphSolver* create();
};

typedef std::map<std::string, raaGraphSolverFactory*>raaGraphSolverFactories;
