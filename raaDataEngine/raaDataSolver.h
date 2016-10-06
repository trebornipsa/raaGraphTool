#pragma once

#include "raaDataModel.h"

#include "raaDataEngineDefs.h"

class RAADATAENGINE_DLL_DEF raaDataSolver
{
public:
	raaDataSolver();
	virtual ~raaDataSolver();

	virtual float solve(const raaDataNodeMap &nodes, const raaDataArcMap &arcs, float fTime, float fDamping) = 0;
};

