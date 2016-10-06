#include "raaGraphSolver.h"
#include "raaGraphSolverFactory.h"

raaGraphSolverFactory::raaGraphSolverFactory(void)
{
}

raaGraphSolverFactory::~raaGraphSolverFactory(void)
{
}

raaGraphSolver* raaGraphSolverFactory::create()
{
	return new raaGraphSolver();
}
