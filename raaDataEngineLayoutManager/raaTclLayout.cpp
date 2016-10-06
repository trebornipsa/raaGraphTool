#include "raaTclLayout.h"
#include <iostream>
#include <fstream>


void raaTclLayout::start(raaParameters& pParams)
{
	if(m_pInterp)
	{
		Tcl_Eval(m_pInterp, "puts [testFunc]");

	}
}

void raaTclLayout::finish()
{
}

raaTclLayout::raaTclLayout()
{
//	Tcl_FindExecutable(EXECNAME);
	m_pInterp = Tcl_CreateInterp();
	Tcl_Init(m_pInterp);

	Tcl_CreateCommand(m_pInterp, "testFunc", (Tcl_CmdProc*)testFunc, (ClientData)this, 0);
	Tcl_CreateObjCommand(m_pInterp, "groups", (Tcl_ObjCmdProc*)listGroups, (ClientData)this, 0);

	std::ifstream in("tcl.txt");

	if(in)
	{
		in.seekg(0, in.end);
		int iLen = in.tellg();
		in.seekg(0, in.beg);

		char *pcBuffer = (char*)_alloca(sizeof(char)*iLen);
		in.read(pcBuffer, iLen);
		m_sTcl = std::string(pcBuffer);
		in.close();
	}

}


raaTclLayout::~raaTclLayout()
{
	if (m_pInterp)
	{
		Tcl_DeleteInterp(m_pInterp);
		m_pInterp = 0;
	}
}

int raaTclLayout::testFunc(void* pData, Tcl_Interp* pInterp, int argc, char** argv)
{
	std::cout << "Hi Robbie" << std::endl;
//	m_pInterp->
//	pInterp->

//	sprintf(, "Robbie");
	
	Tcl_SetResult(pInterp, "fish", TCL_STATIC);
	return TCL_OK;
}

int raaTclLayout::listGroups(void* pData, Tcl_Interp* pInterp, int argc, Tcl_Obj *const argv[])
{
//	Tcl_NewListObj()

//	Tcl_SetRe

	return 0;

}
