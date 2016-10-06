#pragma once

#include "raaDataSolver.h"

#include "raaDataEngineDefs.h"


class RAADATAENGINE_DLL_DEF raaSpringSolver: public raaDataSolver
{
public:
	float solve(const raaDataNodeMap& nodes, const raaDataArcMap& arcs, float fTime, float fDamping) override;
	raaSpringSolver();
	virtual ~raaSpringSolver();

	static void useSqrForce(bool bState);

protected:
	static bool sm_bUseSqrForce;
};

