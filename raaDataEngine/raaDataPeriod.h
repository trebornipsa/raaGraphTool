#pragma once

#include <map>

#include <raaUtilities/raaNode.h>
#include "raaDataEngineDefs.h"

class raaDataLayer;

typedef std::map<std::string, raaDataLayer*>raaDataLayers;

class RAADATAENGINE_DLL_DEF raaDataPeriod : public raaNode
{
public:
	enum Transition
	{
		NONE,
		ENERGY,
	};

	enum Condition
	{
		NO_CONDITION,
		LESS_THAN,
		MORE_THAN,
		EQUAL_TO,
	};

	raaDataPeriod(std::string sName);
	virtual ~raaDataPeriod();

	void addLayer(raaDataLayer *pLayer);
	bool removeLayer(raaDataLayer *pLayer);
	bool hasLayer(raaDataLayer *pLayer);
	raaDataLayer* layer(std::string sName);
	const raaDataLayers& layers();

	void refActive();
	void unrefActive();
	bool active();

	void setTransitionCondition(Transition eTransition, Condition eCondition, float fThreshold);
	bool testTransitionCondition(float fInput);
	Transition transitionType();
	Condition transitionCondition();
	float transitionThreshold();

protected:
	raaDataLayers m_mLayers;
	unsigned int m_uiActiveCount;
	Transition m_eTransition;
	Condition m_eCondition;
	float m_fThreshold;
};

