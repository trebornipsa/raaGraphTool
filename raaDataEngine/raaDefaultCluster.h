#pragma once

#include "raaDataCluster.h"

#include "raaDataEngineDefs.h"

class RAADATAENGINE_DLL_DEF raaDefaultCluster: public raaDataCluster
{
public:
	void cluster(raaDataModel *pModel, const raaDataNodeMap& nodes, float fEPS, float fMinSize) override;
	raaDefaultCluster();
	virtual ~raaDefaultCluster();
protected:
	void clusterRegion(raaDataNode* pNodeTarget, const raaDataNodeMap& nodes, raaCluster& cluster, float fEPS);
};

