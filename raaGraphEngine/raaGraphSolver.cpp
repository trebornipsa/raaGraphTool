#include <iostream>
#include "raaGraphSolver.h"

raaGraphSolver::raaGraphSolver(void)
{
}

raaGraphSolver::~raaGraphSolver(void)
{
}

bool raaGraphSolver::solve( raaGraph *pGraph )
{
	std::cout << "raaGraphSolver: No appropriate solver could be found" <<std::endl;
	return false;
}
