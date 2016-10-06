#pragma once

#include <list>
#include <map>
#include <string>

#include "raaDataEngine2Defs.h"
#include "raaDataUID.h"

namespace raaDE2
{
	class raaDataModel;
	class raaDataPeriod;
	class raaDataNode;
	class raaDataLayer;
	class raaDataArc;
	class raaReferenced;
	class raaDataModelListener;
	class raaDataEngineListener;

	typedef std::map<std::string, raaDataModel*> raaDataModelMap;
	typedef std::map<std::string, raaDataPeriod*> raaDataPeriodMap;
	typedef std::map<std::string, raaDataLayer*> raaDataLayerMap;
	typedef std::map<std::string, raaDataArc*> raaDataArcMap;
	typedef std::map<std::string, raaDataNode*> raaDataNodeMap;
	typedef std::map<std::string, unsigned int> raaUIMap;
	typedef std::map<std::string, float> raaFloatMap;
	typedef std::map<raaDataUID, raaReferenced*> raaUIDReferencedMap;

	typedef std::list<std::string> raaStringList;

	typedef std::list<raaDataPeriod*> raaDataPeriodList;
	typedef std::list<raaDataNode*> raaDataNodeList;
	typedef std::list<raaDataLayer*> raaDataLayerList;
	typedef std::list<raaDataArc*> raaDataArcList;
	typedef std::list<raaReferenced*> raaReferencedList;
	typedef std::list<raaDataModelListener*> raaDataModelListenersList;
	typedef std::list<raaDataEngineListener*> raaDataEngineListenersList;

	typedef std::map<std::string, raaDataNodeList> raaDataNodeListMap;

	const static unsigned int cs_PeriodInactive = 0;
	const static unsigned int cs_PeriodActive = 1;
	const static unsigned int cs_PeriodTransitionIn = 2;
	const static unsigned int cs_PeriodTransitionOut = 3;
	const static unsigned int cs_PeriodTransition = 4;

	const static unsigned int csm_uiModelDecisionTreesWekaSingleYear = 0;
	const static unsigned int csm_uiModelDecisionTreesWekaMultiYear = 1;
}
