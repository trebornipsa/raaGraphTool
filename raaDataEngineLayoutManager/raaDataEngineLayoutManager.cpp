
#include "raaDefaultLayout.h"
#include "raaOpposingRingLayout.h"
#include "raaNegativeCentreRing.h"
#include "raaPositiveCentredRing.h"
#include "raaDataEngineLayout.h"
#include "raaDynamicResultsLayout.h"
#include "raaDynamicResultsFlatLayout.h"
#include "raaTclLayout.h"
#include "raaDataEngineLayoutManager.h"

raaDataEngineLayoutManager* raaDataEngineLayoutManager::sm_pInstance=0;
unsigned int raaDataEngineLayoutManager::sm_uiInstance=0;

void raaDataEngineLayoutManager::start()
{
	if (!sm_pInstance && !sm_uiInstance++) new raaDataEngineLayoutManager();
}

void raaDataEngineLayoutManager::stop()
{
	if (sm_pInstance && !--sm_uiInstance) delete sm_pInstance;
}

raaDataEngineLayoutManager* raaDataEngineLayoutManager::instance()
{
	return sm_pInstance;
}

void raaDataEngineLayoutManager::addLayout(std::string sName, raaDataEngineLayout *pLayout)
{
	if(sName.length() && pLayout)
	{
		m_mLayouts[sName] = pLayout;
	}
}

const raaDataEngineLayouts& raaDataEngineLayoutManager::layouts()
{
	return m_mLayouts;
}

void raaDataEngineLayoutManager::makeLayoutCurrent(std::string sName)
{
	if (sName.length() && m_mLayouts.find(sName) != m_mLayouts.end()) m_pCurrent = m_mLayouts[sName];
}

void raaDataEngineLayoutManager::currentStart(raaDataEngineLayout::raaParameters& pParams)
{
	if (m_pCurrent) m_pCurrent->start(pParams);
}

void raaDataEngineLayoutManager::currentFinish()
{
	if (m_pCurrent) m_pCurrent->finish();
}

void raaDataEngineLayoutManager::currentApply(float fProg)
{
	if (m_pCurrent) m_pCurrent->apply(fProg);
}

raaDataEngineLayoutManager::raaDataEngineLayoutManager()
{
	addLayout("Default", new raaDefaultLayout());
	addLayout("Opposing Ring", new raaOpposingRingLayout());
	addLayout("Positive Ring", new raaPositiveCentredRing());
	addLayout("Negative Ring", new raaNegativeCentreRing());
	addLayout("Dynamic Results Cylinder", new raaDynamicResultsLayout());
	addLayout("Dynamic Results Ring", new raaDynamicResultsFlatLayout());
	addLayout("Tcl Layout", new raaTclLayout());
	if (!sm_pInstance) sm_pInstance = this;
}


raaDataEngineLayoutManager::~raaDataEngineLayoutManager()
{
	if (sm_pInstance == this) sm_pInstance = 0;

	for (raaDataEngineLayouts::iterator it = m_mLayouts.begin(); it != m_mLayouts.end(); it++) delete it->second;

}
