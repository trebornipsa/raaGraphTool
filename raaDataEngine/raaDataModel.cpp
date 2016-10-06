#include "raaDataModel.h"
#include "raaDataCluster.h"

raaDataModel::raaDataModel(std::string sName, float fTransitionEnergy) : raaNode(sName)
{
	m_fBoundRadius = 1.0f;
	m_vCentre.set(0.0f, 0.0f, 0.0f, 0.0f);
	m_fEnergy = 0;
	m_mLayers["default"] = new raaDataLayer("default");
	addChild(m_mLayers["default"]);
	m_mGroups["default"].size();
	m_fTransitionEnergy = fTransitionEnergy;
}

raaDataModel::~raaDataModel()
{
}

void raaDataModel::addNode(raaDataNode* pNode)
{
	if(pNode)
	{
		m_mNodes[pNode->name()] = pNode;
		addChild(pNode);
	}
}

void raaDataModel::removeNode(raaDataNode* pNode)
{
	if(pNode && hasNode(pNode))
	{
		m_mNodes.erase(m_mNodes.find(pNode->name()));
		removeChild(pNode);
	}
}

void raaDataModel::nodeMoved(raaDataNode* pNode)
{
	if (pNode)
	{
		for (raaDataArcMap::iterator it = m_mArcs.begin(); it != m_mArcs.end(); it++)
		{
			raaDataArc *pArc = it->second;
			if (pArc->hasChild(pNode)) pArc->updateCentre(0.03f, 0.97f);
		}
	}
}

bool raaDataModel::hasNode(std::string sName)
{
	if (m_mNodes.find(sName) != m_mNodes.end()) return true;
	return false;
}

bool raaDataModel::hasNode(raaDataNode* pNode)
{
	if (pNode) return hasNode(pNode->name());

	return false;
}

raaDataNode* raaDataModel::node(std::string sName)
{
	if (sName.length() && m_mNodes.find(sName) != m_mNodes.end()) return m_mNodes[sName];
	return 0;
	
}

raaDataNode* raaDataModel::node(unsigned uiIndex)
{
	if (uiIndex < m_mNodes.size())
	{
		for (raaDataNodeMap::iterator it = m_mNodes.begin(); it != m_mNodes.end(); it++, uiIndex--)
			if (!uiIndex) return it->second;
	}
	return 0;
}

raaDataNode* raaDataModel::getNode(std::string sName)
{
	if (m_mNodes.find(sName) != m_mNodes.end()) return m_mNodes[sName];
	return 0;
}

raaDataLayerMap& raaDataModel::layers()
{
	return m_mLayers;
}
/*
const raaDataLayerMap& raaDataModel::layers() const
{
	return m_mLayers;
}
*/
void raaDataModel::addArc(raaDataArc* pArc)
{
	if (pArc)
	{
		m_mArcs[pArc->name()] = pArc;
		m_mLayers["default"]->addArc(pArc);
	}
}

void raaDataModel::addArc(raaDataArc* pArc, std::string sLayer)
{
	if (pArc)
	{
		if (m_mLayers.find(sLayer) == m_mLayers.end()) m_mLayers[sLayer] = new raaDataLayer(sLayer);
		m_mArcs[pArc->name()] = pArc;
		m_mLayers[sLayer]->addArc(pArc);
	}
}

void raaDataModel::addArc(raaDataArc* pArc, raaDataLayer* pLayer)
{
	if(pArc && pLayer)
	{
		m_mArcs[pArc->name()] = pArc;
		m_mLayers[pLayer->name()]->addArc(pArc);
	}
}

void raaDataModel::removeArc(raaDataArc* pArc)
{
	if (pArc)
	{
		m_mArcs.erase(m_mArcs.find(pArc->name()));

		for (raaDataLayerMap::iterator it = m_mLayers.begin(); it != m_mLayers.end();it++) it->second->removeChild(pArc);
	}
}

raaDataArc* raaDataModel::arc(unsigned uiIndex)
{
	for (raaDataArcMap::iterator it = m_mArcs.begin(); it != m_mArcs.end(); it++, uiIndex--) if (!uiIndex) return it->second;
	return 0;
}

bool raaDataModel::addLayer(raaDataLayer* pLayer)
{
	if(pLayer && pLayer->name().length() && !hasLayer(pLayer->name()))
	{
		m_mLayers[pLayer->name()] = pLayer;
		addChild(pLayer);
		return true;
	}
	return false;
}

bool raaDataModel::removeLayer(raaDataLayer* pLayer, bool bArcsToDefault)
{
	if (pLayer && hasLayer(pLayer->name()))
	{
		for (raaDataArcs::const_iterator it = pLayer->arcs().begin(); it != pLayer->arcs().end(); it++) m_mLayers["default"]->addArc(*it);

		m_mLayers.erase(pLayer->name());

		removeChild(pLayer);
		return true;
	}
	return false;
}

bool raaDataModel::hasLayer(std::string sName)
{
	if (sName.length() && m_mLayers.find(sName)!=m_mLayers.end())
				return true;
	return false;
}

int raaDataModel::layerIndex(raaDataLayer* pLayer)
{
	if(hasLayer(pLayer->name()))
	{
		return std::distance(m_mLayers.begin(), m_mLayers.find(pLayer->name()));
	}
	return -1;
}

raaDataLayer* raaDataModel::layer(std::string sName)
{
	if (sName.length() && m_mLayers.find(sName) != m_mLayers.end()) return m_mLayers[sName];
	return 0;
}

raaDataLayer* raaDataModel::layer(unsigned uiIndex)
{
	for (raaDataLayerMap::iterator it = m_mLayers.begin(); it != m_mLayers.end();uiIndex--, it++) if (!uiIndex) return it->second;

	return 0;
}

raaDataLayer* raaDataModel::defaultLayer()
{
	return m_mLayers["default"];
}

void raaDataModel::computeBound()
{
	m_vCentre.set(0.0f, 0.0f, 0.0f, 0.0f);
	m_fBoundRadius = 0.0f;

	for (raaDataNodeMap::iterator it = m_mNodes.begin(); it != m_mNodes.end();it++) m_vCentre += it->second->position();
	m_vCentre /= (float)m_mNodes.size();

	for (raaDataNodeMap::iterator it = m_mNodes.begin(); it != m_mNodes.end(); it++)
	{
		float fDist = it->second->position().distance(m_vCentre);

		if (fDist > m_fBoundRadius) m_fBoundRadius = fDist;
	}
}

raaVector raaDataModel::centre()
{
	return m_vCentre;
}

float raaDataModel::boundRadius()
{
	return m_fBoundRadius;
}

raaDataArc* raaDataModel::getArc(std::string sName)
{
	if (m_mArcs.find(sName) != m_mArcs.end()) return m_mArcs[sName];
	return 0;
}

const raaDataNodeMap& raaDataModel::nodes()
{
	return m_mNodes;
}

const raaDataArcMap& raaDataModel::arcs()
{
	return m_mArcs;
}

const raaClusterSet& raaDataModel::clusterSet() const
{
	return m_vClusterSet;
}

const raaCluster& raaDataModel::noise() const
{
	return m_vNoise;
}

void raaDataModel::clearClusterSet()
{
	m_vClusterSet.clear();
	m_vNoise.clear();
}

void raaDataModel::addNoise(raaDataNode* pNode)
{
	m_vNoise.push_back(pNode);
}

void raaDataModel::addCluster(raaCluster& cluster)
{
	m_vClusterSet.push_back(cluster);
}

void raaDataModel::addToCluster(raaCluster& cluster)
{
	m_vClusterSet.back().splice(m_vClusterSet.back().end(), cluster);


//	for (raaCluster::iterator it = cluster.begin(); it != cluster.end(); it++)


//	for (unsigned int i = 0; i < cluster.size();i++)
//		m_vClusterSet.back().push_back(*it);
}

void raaDataModel::addToCluster(raaDataNode* pNode)
{
	m_vClusterSet.back().push_back(pNode);
}

void raaDataModel::clusterUnique()
{
	m_vClusterSet.back().unique();
}

void raaDataModel::setEnergy(float f)
{
	m_fEnergy = f;
}

float raaDataModel::energy()
{
	return m_fEnergy;
}

void raaDataModel::nodeGroup(std::string sGroup, raaNodeGroup& group)
{
	group.clear();
	if(sGroup.size() && raaDataNode::hasGroup(sGroup))
	for (unsigned int i = 0; i < m_vChildren.size();i++)
	{
		if(raaDataNode *pDN=dynamic_cast<raaDataNode*>(m_vChildren[i]))
		{
			if (pDN->isInGroup(sGroup)) group.push_back(pDN);
		}
	}
}

void raaDataModel::normaliseArcWeights()
{
	float fMin, fMax;
	bool bFirst = true;

	for (raaDataArcMap::iterator it = m_mArcs.begin(); it != m_mArcs.end();it++)
	{
		if(bFirst)
		{
			fMin = fMax = it->second->weight();
			bFirst = false;
		}
		else
		{
			fMin = (fMin < it->second->weight()) ? it->second->weight() : fMin;
			fMax = (fMax > it->second->weight()) ? it->second->weight() : fMax;
		}
	}

	float fRange = fMax - fMin;

	for (raaDataArcMap::iterator it = m_mArcs.begin(); it != m_mArcs.end(); it++)
	{
		it->second->setWeight(0.1f+(it->second->weight() - fMin) / fRange);
	}
}

void raaDataModel::addGroupNode(std::string sGroup, raaDataNode* pNode)
{
	if(sGroup.length() && pNode)
	{
		if(hasGroup(sGroup))
		{
			if (std::find(m_mGroups[sGroup].begin(), m_mGroups[sGroup].end(), pNode) == m_mGroups[sGroup].end()) m_mGroups[sGroup].push_back(pNode);
		}
		else
			m_mGroups[sGroup].push_back(pNode);
	}
}

bool raaDataModel::hasGroup(std::string sGroup)
{
	if (sGroup.length() && m_mGroups.find(sGroup) != m_mGroups.end()) return true;
	return false;
}

const raaDataNodeGroup& raaDataModel::nodeGroup(std::string sGroup)
{
	if (hasGroup(sGroup)) return m_mGroups[sGroup];
	else return m_mGroups["default"];
}

const raaDataNodeGroups& raaDataModel::nodeGroups()
{
	return m_mGroups;
 }

float raaDataModel::transitionEnergy()
{
	return m_fTransitionEnergy;
}
