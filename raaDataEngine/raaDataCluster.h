#pragma once

#include <vector>

#include "raaDataModel.h"

#include "raaDataEngineDefs.h"



class RAADATAENGINE_DLL_DEF raaDataCluster
{
public:
	raaDataCluster();
	virtual ~raaDataCluster();

	virtual void cluster(raaDataModel *pModel, const raaDataNodeMap &nodes, float fEPS, float fMinSize)=0;



protected:

};

