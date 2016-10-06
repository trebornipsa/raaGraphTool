#pragma once

#include "raaGraphEngineDefs.h"

class raaGraphSolverFactory;
class raaGraphEngine;
class raaGraph;

class RAAGRAPHENGINE_DLL_DEF raaGraphSolver
{
	friend raaGraph;
	friend raaGraphEngine;
	friend raaGraphSolverFactory;
public:
protected:
	virtual bool solve(raaGraph *pGraph);
	raaGraphSolver(void);
	virtual ~raaGraphSolver(void);
};
