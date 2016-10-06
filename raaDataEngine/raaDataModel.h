#pragma once

#include <map>
#include <string>
#include <vector>

#include <raaUtilities/raaUID.h>
#include <raaUtilities/raaNode.h>

#include "raaDataLayer.h"
#include "raaDataNode.h"
#include "raaDataArc.h"
#include "raaDataEngineDefs.h"

typedef std::map<std::string, raaDataNode*> raaDataNodeMap;
typedef std::map<std::string, raaDataArc*> raaDataArcMap;
typedef std::map<std::string, raaDataLayer*> raaDataLayerMap;

typedef std::list<raaDataNode*> raaDataNodeGroup;
typedef std::map<std::string, raaDataNodeGroup> raaDataNodeGroups;

typedef std::list<raaDataNode*> raaCluster;
typedef std::list<raaDataNode*> raaNodeGroup;
typedef std::list<raaCluster> raaClusterSet;

class RAADATAENGINE_DLL_DEF raaDataModel : public raaNode
{
public:
	raaDataModel(std::string sName, float fTransitionEnergy=10.0f);
	virtual ~raaDataModel();

	void addNode(raaDataNode *pNode);
	void removeNode(raaDataNode *pNode);
	void nodeMoved(raaDataNode *pNode);
	bool hasNode(std::string sName);
	bool hasNode(raaDataNode *pNode);
	raaDataNode* node(std::string sName);
	raaDataNode* node(unsigned int uiIndex);

	raaDataNode* getNode(std::string sName);
	raaDataArc* getArc(std::string sName);

	const raaDataNodeMap& nodes();
	const raaDataArcMap& arcs();
//	const raaDataLayerMap& layers() const;
	raaDataLayerMap& layers();

	void addArc(raaDataArc *pArc);
	void addArc(raaDataArc *pArc, std::string sLayer);
	void addArc(raaDataArc *pArc, raaDataLayer *pLayer);
	void removeArc(raaDataArc *pArc);
	raaDataArc* arc(unsigned int uiIndex);

	bool addLayer(raaDataLayer *pLayer);
	bool removeLayer(raaDataLayer *pLayer, bool bArcsToDefault=false);
	bool hasLayer(std::string sName);
	int layerIndex(raaDataLayer *pLayer);
	raaDataLayer* layer(std::string sName);
	raaDataLayer* layer(unsigned int uiIndex);
	raaDataLayer* defaultLayer();

	void computeBound();
	raaVector centre();
	float boundRadius();

	const raaClusterSet& clusterSet() const;
	const raaCluster& noise() const;
	void clearClusterSet();

	void addNoise(raaDataNode *pNode);
	void addCluster(raaCluster &cluster);
	void addToCluster(raaCluster &cluster);
	void addToCluster(raaDataNode *pNode);
	void clusterUnique();

	void setEnergy(float f);
	float energy();

	void nodeGroup(std::string sGroup, raaNodeGroup& group);
	void normaliseArcWeights();

	void addGroupNode(std::string sGroup, raaDataNode *pNode);
	bool hasGroup(std::string sGroup);
	const raaDataNodeGroup& nodeGroup(std::string sGroup);
	const raaDataNodeGroups& nodeGroups();

	float transitionEnergy();

protected:
	raaDataNodeMap m_mNodes;
	raaDataArcMap m_mArcs;
	raaDataLayerMap m_mLayers;
	raaDataNodeGroups m_mGroups;

	raaClusterSet m_vClusterSet;
	raaCluster m_vNoise;

	raaVector m_vCentre;
	float m_fBoundRadius;
	float m_fTransitionEnergy;
	float m_fEnergy;
};

