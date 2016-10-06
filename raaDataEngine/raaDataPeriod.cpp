#include "raaDataLayer.h"

#include "raaDataPeriod.h"

raaDataPeriod::raaDataPeriod(std::string sName) : raaNode(sName)
{
	m_uiActiveCount = 0;
	m_eTransition = raaDataPeriod::NONE;
	m_eCondition = raaDataPeriod::NO_CONDITION;
	m_fThreshold = 0.0f;
}

raaDataPeriod::~raaDataPeriod()
{
	for (raaDataLayers::iterator it = m_mLayers.begin(); it != m_mLayers.end();it++) if (m_uiActiveCount) it->second->unrefActive();
}

void raaDataPeriod::addLayer(raaDataLayer* pLayer)
{
	if(pLayer)
	{
		m_mLayers[pLayer->name()] = pLayer;
		if (m_uiActiveCount) pLayer->refActive(); else pLayer->unrefActive();
		addChild(pLayer);
	}
}

bool raaDataPeriod::removeLayer(raaDataLayer* pLayer)
{
	if(hasLayer(pLayer))
	{
		m_mLayers.erase(m_mLayers.find(pLayer->name()));
		if (m_uiActiveCount) pLayer->unrefActive();
		removeChild(pLayer);
		return true;
	}
	return false;
}

bool raaDataPeriod::hasLayer(raaDataLayer* pLayer)
{
	if(pLayer && pLayer->name().length())
	{
		if (m_mLayers.find(pLayer->name()) != m_mLayers.end() && m_mLayers[pLayer->name()] == pLayer)
			return true;
	}

	return false;
}

raaDataLayer* raaDataPeriod::layer(std::string sName)
{
	if (sName.length())
	{
		if (m_mLayers.find(sName) != m_mLayers.end())
			return m_mLayers[sName];
	}

	return 0;
}

const raaDataLayers& raaDataPeriod::layers()
{
	return m_mLayers;
}

void raaDataPeriod::refActive()
{
	if (++m_uiActiveCount) for (raaDataLayers::iterator it = m_mLayers.begin(); it != m_mLayers.end(); it++) it->second->refActive();
}

void raaDataPeriod::unrefActive()
{
	if (!--m_uiActiveCount) for (raaDataLayers::iterator it = m_mLayers.begin(); it != m_mLayers.end(); it++) it->second->unrefActive();
}

bool raaDataPeriod::active()
{
	return m_uiActiveCount?true:false;
}

void raaDataPeriod::setTransitionCondition(Transition eTransition, Condition eCondition, float fThreshold)
{
	m_eTransition = eTransition;
	m_eCondition = eCondition;
	m_fThreshold = fThreshold;
}

bool raaDataPeriod::testTransitionCondition(float fInput)
{
	bool bRet = false;
	switch(m_eCondition)
	{
		case Condition::LESS_THAN:
			if (fInput < m_fThreshold) bRet = true;
			break;
		case Condition::MORE_THAN:
			if (fInput > m_fThreshold) bRet = true;
			break;
		case Condition::EQUAL_TO:
			if (fInput == m_fThreshold) bRet = true;
			break;
		default:
			break;
	}
	return bRet;
}

raaDataPeriod::Transition raaDataPeriod::transitionType()
{
	return m_eTransition;
}

raaDataPeriod::Condition raaDataPeriod::transitionCondition()
{
	return m_eCondition;
}

float raaDataPeriod::transitionThreshold()
{
	return m_fThreshold;
}
