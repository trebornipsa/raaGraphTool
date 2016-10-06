
#include "raaDataPeriod.h"
#include "raaDataLayer.h"
#include "raaDataNode.h"
#include "raaDataModelListener.h"
#include "raaDataArc.h"
#include "raaDataModel.h"
#include "raaDefaultSolver.h"
#include <iostream>

raaDE2::raaDataModel::raaDataModel(std::string sName)
{
	m_pSolver = new raaDefaultSolver(sName);
	m_sName = sName;
	m_fTransitionTime = 0.03f;
	m_fDamping = 0.975f;
	m_bSolving = false;
}

raaDE2::raaDataModel::~raaDataModel()
{
	if (m_pSolver) delete m_pSolver;
}

raaDE2::raaDataPeriod* raaDE2::raaDataModel::getOrCreatePeriod(std::string sName)
{
	raaDataPeriod *pPeriod = 0;
	if (sName.length())
	{
		if (m_mPeriods.find(sName) == m_mPeriods.end())
		{
			pPeriod = new raaDataPeriod(sName);
			m_mPeriods[sName] = pPeriod;
			m_lPeriods.push_back(pPeriod);
			pPeriod->ref();
		}
		else
		{
			pPeriod = m_mPeriods[sName];
		}
	}

	return pPeriod;
}

raaDE2::raaDataLayer* raaDE2::raaDataModel::getOrCreateLayer(std::string sName, raaDataPeriod* pPeriod)
{
	raaDataLayer *pLayer = 0;
	if(pPeriod && std::find(m_lPeriods.begin(), m_lPeriods.end(), pPeriod)!=m_lPeriods.end())
	{
		pLayer = pPeriod->getOrCreateLayer(sName);
		m_lLayers.push_back(pLayer);
	}
	return pLayer;
}

raaDE2::raaDataArc* raaDE2::raaDataModel::getOrCreateArc(std::string sName, raaDataLayer* pLayer)
{
	raaDataArc *pArc = 0;
	if (pLayer && std::find(m_lLayers.begin(), m_lLayers.end(), pLayer) != m_lLayers.end())
	{
		pArc = pLayer->getOrCreateArc(sName);

		if (std::find(m_lArcs.begin(), m_lArcs.end(), pArc) == m_lArcs.end()) m_lArcs.push_back(pArc);
	}



	return pArc;
}

raaDE2::raaDataNode* raaDE2::raaDataModel::getOrCreateNode(std::string sName)
{
	raaDataNode *pNode = 0;
	if (sName.length())
	{
		if (m_mNodes.find(sName) == m_mNodes.end())
		{
			pNode = new raaDataNode(sName);
			m_lNodes.push_back(pNode);
			m_mNodes[sName] = pNode;
			pNode->ref();
		}
		else
			pNode = m_mNodes[sName];
	}
	return pNode;
}

bool raaDE2::raaDataModel::addNodeToArc(raaDataArc* pArc, raaDataNode* pNode)
{
	if(hasNode(pNode) && hasArc(pArc))
	{
		if (std::find(pNode->m_lArcs.begin(), pNode->m_lArcs.end(), pArc) == pNode->m_lArcs.end() && std::find(pArc->m_lNodes.begin(), pArc->m_lNodes.end(), pNode) == pArc->m_lNodes.end())
		{
			pNode->m_lArcs.push_back(pArc);
			pArc->m_lNodes.push_back(pNode);
			pNode->ref();
			pArc->ref();
			return true;
		}
	}
	return false;
}

bool raaDE2::raaDataModel::removeNodeFromArc(raaDataArc* pArc, raaDataNode* pNode)
{
	if (hasNode(pNode) && hasArc(pArc))
	{
		if (std::find(pNode->m_lArcs.begin(), pNode->m_lArcs.end(), pArc) != pNode->m_lArcs.end() && std::find(pArc->m_lNodes.begin(), pArc->m_lNodes.end(), pNode) != pArc->m_lNodes.end())
		{
			pNode->m_lArcs.remove(pArc);
			pArc->m_lNodes.remove(pNode);
			pNode->unref();
			pArc->unref();
			return true;
		}
	}
	return false;
}

bool raaDE2::raaDataModel::hasNode(raaDataNode* pNode)
{
	if (pNode && std::find(m_lNodes.begin(), m_lNodes.end(), pNode) != m_lNodes.end()) return true;
	return false;
}

bool raaDE2::raaDataModel::hasNode(std::string sName)
{
	if (sName.length() && m_mNodes.find(sName) == m_mNodes.end()) return false;
	return true;
}

bool raaDE2::raaDataModel::hasArc(raaDataArc* pArc)
{
	if (pArc && std::find(m_lArcs.begin(), m_lArcs.end(), pArc) != m_lArcs.end()) return true;
	return false;
}

float raaDE2::raaDataModel::transitionTime()
{
	return m_fTransitionTime;
}

void raaDE2::raaDataModel::setTransitionTime(float fTransTime)
{
	m_fTransitionTime = fTransTime;
}

void raaDE2::raaDataModel::setCurrentPeriod(raaDataPeriod* pPeriod)
{
	if (m_pCurrentPeriod != pPeriod)
	{
		if (m_pCurrentPeriod) m_pCurrentPeriod->setTransitionState(cs_PeriodInactive);
		m_pCurrentPeriod = pPeriod;
		if (m_pCurrentPeriod) m_pCurrentPeriod->setTransitionState(cs_PeriodActive);
	}
}

void raaDE2::raaDataModel::setTransitionPeriod(raaDataPeriod* pPeriod)
{
	if(m_pCurrentPeriod != pPeriod)
	{
		if (m_pCurrentPeriod) m_pCurrentPeriod->setTransitionState(cs_PeriodTransitionOut);
		m_pTransitionalPeriod = pPeriod;
		m_fCurrentTransitionTime = m_fTransitionTime;
		if (m_pTransitionalPeriod) m_pTransitionalPeriod->setTransitionState(cs_PeriodTransitionIn);
	}
}

void raaDE2::raaDataModel::tick(float fTime)
{
	// in transition
	if(m_pTransitionalPeriod)
	{
		if(m_fCurrentTransitionTime<=0.0f)
		{
			if (m_pCurrentPeriod) m_pCurrentPeriod->setTransitionState(cs_PeriodInactive);
			if (m_pTransitionalPeriod) m_pTransitionalPeriod->setTransitionState(cs_PeriodActive);
			m_pCurrentPeriod = m_pTransitionalPeriod;
			m_pTransitionalPeriod = 0;
		}
		else
		{
			m_fCurrentTransitionTime -= fTime;
			m_fCurrentTransitionTime = m_fCurrentTransitionTime / m_fTransitionTime;
		}
	}
}

void raaDE2::raaDataModel::setDamping(float fDamping)
{
	m_fDamping = fDamping;
}

float raaDE2::raaDataModel::damping()
{
	return m_fDamping;
}

const raaDE2::raaDataNodeList& raaDE2::raaDataModel::nodes()
{
	return m_lNodes;
}

const raaDE2::raaDataArcList& raaDE2::raaDataModel::arcs()
{
	return m_lArcs;
}

void raaDE2::raaDataModel::addListener(raaDataModelListener* pListener)
{
	if (pListener && std::find(m_lListeners.begin(), m_lListeners.end(), pListener) == m_lListeners.end())
	{
		m_lListeners.push_back(pListener);

		for (raaDataNodeList::iterator it = m_lNodes.begin(); it != m_lNodes.end(); it++) pListener->newNode((*it));
		for (raaDataArcList::iterator it = m_lArcs.begin(); it != m_lArcs.end(); it++) pListener->newArc(*it);
	}
}

void raaDE2::raaDataModel::removeListener(raaDataModelListener* pListener)
{
	if (pListener && std::find(m_lListeners.begin(), m_lListeners.end(), pListener) != m_lListeners.end()) m_lListeners.remove(pListener);
}

void raaDE2::raaDataModel::solve(bool bSolve)
{
	if (bSolve)
	{
		std::cout << "data Model solving" << std::endl;
	
		if(!isLooping()) start();
	}

	else
	{
		std::cout << "data Model not solving" << std::endl;
		if (isLooping()) end();
	}

	m_bSolving = bSolve;
}

bool raaDE2::raaDataModel::isSolving()
{
	return m_bSolving;
}

void raaDE2::raaDataModel::startLoop()
{
	std::cout << "Start Solve" << std::endl;
}

void raaDE2::raaDataModel::loop()
{
	if (m_pSolver)
	{
		m_pSolver->solve(this, 0.1f);
	
		for (raaDataModelListenersList::iterator it = m_lListeners.begin(); it != m_lListeners.end(); it++)
			(*it)->updatedNodes(this);
	}
}

void raaDE2::raaDataModel::endLoop()
{
	std::cout << "End Solve" << std::endl;
}

