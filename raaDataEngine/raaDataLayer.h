#pragma once

#include <string>

#include <raaUtilities/raaNode.h>

#include "raaDataArc.h"
#include "raaDataEngineDefs.h"

class RAADATAENGINE_DLL_DEF raaDataLayer : public raaNode
{
public:
	raaDataLayer(std::string sName);

	const raaDataArcs& arcs();

	void addArc(raaDataArc *pArc);
	void removeArc(raaDataArc *pArc);
	bool containsArc(raaDataArc *pArc);
	bool hasArc(raaDataArc *pArc);
	int arcIndex(raaDataArc *pArc);

	void refActive();
	void unrefActive();
	bool active();

	void normaliseArcWeights();
	void normaliseArcLengths(float fMin, float fMax);


	const raaVector& colour();
	void setColour(raaVector v);

	void setLayerStrength(float fWeight);
	float layerStrength();

protected:
	float m_fLayerStrength;

	raaVector m_vColour;
	raaDataArcs m_lArcs;
	unsigned int m_uiActiveCount;

	virtual ~raaDataLayer();
};

