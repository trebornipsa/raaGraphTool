#pragma once

#include "raaDataObject.h"
#include "raaDataEngineTypes.h"
#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaSolverInterface : public raaDataObject
	{
	public:
		raaSolverInterface(std::string sName);
		virtual ~raaSolverInterface();
		virtual float solve(raaDataModel* pModel, float fTime)=0;
	};
}
