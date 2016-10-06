#pragma once

#include <string>
#include <map>

#include "raaDataEngineLayout.h"
#include "raaDataEngineLayoutManagerDefs.h"


typedef std::map<std::string, raaDataEngineLayout*> raaDataEngineLayouts;

class RAADATAENGINELAYOUTMANAGER_DLL_DEF raaDataEngineLayoutManager
{
public:
	static void start();
	static void stop();
	static raaDataEngineLayoutManager* instance();

	void addLayout(std::string sName, raaDataEngineLayout *pLayout);

	const raaDataEngineLayouts& layouts();
	void makeLayoutCurrent(std::string sName);
	void currentStart(raaDataEngineLayout::raaParameters& pParams);
	void currentFinish();
	void currentApply(float fProg);


protected:
	static raaDataEngineLayoutManager* sm_pInstance;
	static unsigned int sm_uiInstance;

	raaDataEngineLayouts m_mLayouts;
	raaDataEngineLayout *m_pCurrent;

	raaDataEngineLayoutManager();
	virtual ~raaDataEngineLayoutManager();
};

