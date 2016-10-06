#pragma once

#include "raaGraphSolverFactory.h"

class raaGraphSolver;

class RAAGRAPHENGINE_DLL_DEF raaUndirectedSolverFactory : public raaGraphSolverFactory
{
public:
	raaUndirectedSolverFactory(void);
	virtual ~raaUndirectedSolverFactory(void);
	virtual raaGraphSolver* create();
};

