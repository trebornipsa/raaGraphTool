#pragma once

#include "raaDataEngineLayout.h"

#include "raaDataEngineLayoutManagerDefs.h"

class RAADATAENGINELAYOUTMANAGER_DLL_DEF raaDefaultLayout : public raaDataEngineLayout
{
public:
	virtual void start(raaParameters& pParams);
	virtual void finish();

	raaDefaultLayout();
	virtual ~raaDefaultLayout();
};

