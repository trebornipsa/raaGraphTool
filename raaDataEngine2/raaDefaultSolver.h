#pragma once

#include "raaSolverInterface.h"
#include "raaDataEngineTypes.h"
#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaDefaultSolver: public raaSolverInterface
	{
	public:
		virtual float solve(raaDataModel* pModel, float fTime);
		raaDefaultSolver(std::string sName);
	protected:
		virtual ~raaDefaultSolver();
		virtual void aboutToDelete();
		virtual void activeChanged(std::string sName);
		virtual void attributeChanged(std::string sName);

		void clearForce(const raaDataNodeList &lNodes);
		void calcForce(const raaDataArcList& lArcs);
		float calcMotion(const raaDataNodeList &lNodes, float fTime, float fDamping);

	};
}

