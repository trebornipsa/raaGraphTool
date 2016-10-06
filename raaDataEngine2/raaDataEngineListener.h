#pragma once

#include <string>
#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaDataEngineListener
	{
	public:
		raaDataEngineListener();
		~raaDataEngineListener();

		virtual void modelAdded(std::string sName) = 0;
		virtual void modelRemoved(std::string sName) = 0;
	};
}
