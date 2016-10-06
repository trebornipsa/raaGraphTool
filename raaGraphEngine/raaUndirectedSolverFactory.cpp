#include "raaUndirectedSolver.h"
#include "raaUndirectedSolverFactory.h"

raaUndirectedSolverFactory::raaUndirectedSolverFactory(void)
{
}


raaUndirectedSolverFactory::~raaUndirectedSolverFactory(void)
{
}

raaGraphSolver* raaUndirectedSolverFactory::create()
{
	return new raaUndirectedSolver();
}
