
#include "raaGraph.h"
#include "raaNode.h"

#include "raaUndirectedSolver.h"

//http://www.mpi-inf.mpg.de/~pettie/papers/undirected-sp.pdf
//http://cs.wellesley.edu/~cs315/Papers/Kamada-Graph%20Drawing.pdf

raaUndirectedSolver::raaUndirectedSolver(void)
{
	m_uiIterations=10;
}


raaUndirectedSolver::~raaUndirectedSolver(void)
{
}

bool raaUndirectedSolver::solve( raaGraph *pGraph )
{
	if(pGraph)
	{
		if(!pGraph->hasSolution())
		{
		}


//		for(unsigned int i=0;i<m_uiIterations;i++)
//		{
			// calculate forces


//		}
	}

	return false;
}
