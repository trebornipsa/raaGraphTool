#pragma once
#include "raaDataEngineLayout.h"

#include "raaDataEngineLayoutManagerDefs.h"

class RAADATAENGINELAYOUTMANAGER_DLL_DEF raaNegativeCentreRing : public raaDataEngineLayout
{
public:
	virtual void start(raaParameters& pParams);
	virtual void finish();
	raaNegativeCentreRing();
	virtual ~raaNegativeCentreRing();
};

