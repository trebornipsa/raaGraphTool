#pragma once

#include <tcl.h>

#include "raaDataEngineLayout.h"

#include "raaDataEngineLayoutManagerDefs.h"

class RAADATAENGINELAYOUTMANAGER_DLL_DEF raaTclLayout : public raaDataEngineLayout
{
public:
	virtual void start(raaParameters& pParams);
	virtual void finish();
	raaTclLayout();
	virtual ~raaTclLayout();

protected:
	Tcl_Interp *m_pInterp;

	static int testFunc(void* pData, Tcl_Interp *pInterp, int argc, char** argv);
	static int listGroups(void *pData, Tcl_Interp *pInterp, int argc, Tcl_Obj *const argv[]);

	std::string m_sTcl;
};

