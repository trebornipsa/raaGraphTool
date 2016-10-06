#include "raaDataLayer.h"
#include "raaDataNode.h"
#include "raaDataArc.h"
#include "raaDataPeriod.h"


bool raaDE2::raaDataPeriod::removeLayer(raaDataLayer* pLayer)
{
	if (pLayer && std::find(m_lLayers.begin(), m_lLayers.end(), pLayer) != m_lLayers.end())
	{
		m_lLayers.remove(pLayer);
		m_mLayers.erase(pLayer->name());
		pLayer->unref();
		return true;
	}
	return false;
}

void raaDE2::raaDataPeriod::setTransitionState(unsigned uiState, float fTransitionTime)
{
	if (m_uiState != uiState)
	{
		m_uiState = uiState;
		m_fTransitionTime = fTransitionTime;

		bool bActive = false;
		switch(m_uiState)
		{
			case cs_PeriodTransitionOut:
			case cs_PeriodTransitionIn:
			case cs_PeriodActive:
				bActive = true;
				break;
			default:
				bActive = false;
				break;
		}
		for (raaDataLayerList::iterator it = m_lLayers.begin(); it != m_lLayers.end(); it++) (*it)->setActivityCount("period", bActive);
	}
}

float raaDE2::raaDataPeriod::transitionTime()
{
	return m_fTransitionTime;
}

unsigned raaDE2::raaDataPeriod::transitionState()
{
	return m_uiState;
}

void raaDE2::raaDataPeriod::addToGroup(std::string sGroup, raaDataNode* pNode)
{
	if(sGroup.length() && pNode)
	{
		if (std::find(m_mGroups[sGroup].begin(), m_mGroups[sGroup].end(), pNode) == m_mGroups[sGroup].end())
		{
			m_mGroups[sGroup].push_back(pNode);
			pNode->m_lGroups.push_back(sGroup);
		}
	}
}

void raaDE2::raaDataPeriod::removeFromGroup(std::string sGroup, raaDataNode* pNode)
{
	if (sGroup.length() && pNode)
	{
		if (m_mGroups.find(sGroup) != m_mGroups.end())
		{
			if (std::find(m_mGroups[sGroup].begin(), m_mGroups[sGroup].end(), pNode) != m_mGroups[sGroup].end())
			{
				m_mGroups[sGroup].remove(pNode);
				pNode->m_lGroups.remove(sGroup);
			}
		}
	}
}

const raaDE2::raaDataNodeList& raaDE2::raaDataPeriod::group(std::string sGroup)
{
	if (hasGroup(sGroup))
		return m_mGroups[sGroup];
	else
		return m_lEmptyList;
}

bool raaDE2::raaDataPeriod::hasGroup(std::string sGroup)
{

	if (sGroup.length() && m_mGroups.find(sGroup) != m_mGroups.end()) return true;
	return false;
}

void raaDE2::raaDataPeriod::normaliseArcs()
{
	raaDataArcList lArcs;

	float fMax, fMin;
	bool bFirst = true;

	for (raaDataLayerList::iterator it = m_lLayers.begin(); it != m_lLayers.end(); it++)
	{
		raaDataLayer *pLayer = (*it);

		for (raaDataArcList::const_iterator ait = pLayer->arcs().begin(); ait != pLayer->arcs().end(); ait++)
		{
			if (bFirst)
			{
				fMax = fMin = (*ait)->springCoef();
			}
			else
			{
				fMax = (fMax < (*ait)->springCoef()) ? (*ait)->springCoef() : fMax;
				fMin = (fMin > (*ait)->springCoef()) ? (*ait)->springCoef() : fMin;
			}
			lArcs.push_back(*ait);
		}
	}

	float fRange = fMax - fMin;


	for (raaDataArcList::iterator it = lArcs.begin(); it != lArcs.end(); it++)
	{
		raaDataArc *pArc = (*it);
		pArc->setSpringCoef((((pArc->springCoef() - fMin) / fRange)*0.99f) + 0.01f);
	}
}

raaDE2::raaDataPeriod::raaDataPeriod(std::string sName) : raaDataObject(sName)
{
}

raaDE2::raaDataPeriod::~raaDataPeriod()
{
}

raaDE2::raaDataLayer* raaDE2::raaDataPeriod::getOrCreateLayer(std::string sName)
{
	raaDataLayer *pLayer = 0;
	if (sName.length())
	{
		if (m_mLayers.find(sName) == m_mLayers.end())
		{
			pLayer = new raaDataLayer(sName);
			m_lLayers.push_back(pLayer);
			m_mLayers[sName] = pLayer;
			pLayer->ref();
		}
		else
			pLayer = m_mLayers[sName];
	}

	return pLayer;
}

void raaDE2::raaDataPeriod::aboutToDelete()
{
}

void raaDE2::raaDataPeriod::activeChanged(std::string sName)
{
}

void raaDE2::raaDataPeriod::attributeChanged(std::string sName)
{
}
