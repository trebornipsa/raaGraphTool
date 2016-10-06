#pragma once

#include <list>

#include "raaDataEngineDefs.h"

class raaDataNode;

typedef std::list<raaDataNode*> raaCluster;
	
class RAADATAENGINE_DLL_DEF raaDataClusterInfo
{
public:
	raaDataClusterInfo();
	virtual ~raaDataClusterInfo();

protected:
	raaCluster m_lCluster;


};

