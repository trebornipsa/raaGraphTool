#pragma once

#include <osg/Vec3f>

#include "raaGraphSolver.h"

#include "raaGraphEngineDefs.h"

class raaGraphEngine;
class raaUndirectedSolverFactory;

class RAAGRAPHENGINE_DLL_DEF raaUndirectedSolver : public raaGraphSolver
{
	friend raaGraphEngine;
	friend raaUndirectedSolverFactory;
public:
protected:
	float randFloat(float fMin, float fMax);
	osg::Vec3f randVec(float fMin, float fMax);

	virtual bool solve(raaGraph *pGraph);
	raaUndirectedSolver(void);
	virtual ~raaUndirectedSolver(void);

	unsigned int m_uiIterations;
};

