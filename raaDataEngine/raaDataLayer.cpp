#include <raaUtilities/raaUtilities.h>

#include "raaDataLayer.h"
#include <iostream>

raaDataLayer::raaDataLayer(std::string sName) : raaNode(sName)
{
	m_uiActiveCount=0;
	m_vColour.set(raaUtilities::randfloat(0.0f, 1.0f), raaUtilities::randfloat(0.0f, 1.0f), raaUtilities::randfloat(0.0f, 1.0f), 0.3f);
	!m_vColour;
	m_vColour *= 0.65f;
	m_vColour.get()[3] = 0.8f;
	m_fLayerStrength = 1.0f;
}

const raaDataArcs& raaDataLayer::arcs()
{
	return m_lArcs; 
}

void raaDataLayer::addArc(raaDataArc* pArc)
{
	if(pArc && !containsArc(pArc))
	{
		if (m_uiActiveCount) pArc->refActiveCount();
		m_lArcs.push_back(pArc);
		addChild(pArc);
		pArc->setColour(m_vColour);
	}
}

void raaDataLayer::removeArc(raaDataArc* pArc)
{
	if (pArc && containsArc(pArc))
	{
		if (m_uiActiveCount) pArc->unrefActiveCount();
		m_lArcs.erase(std::find(m_lArcs.begin(), m_lArcs.end(), pArc));
		removeChild(pArc);
	}
}

bool raaDataLayer::containsArc(raaDataArc* pArc)
{
	if(std::find(m_lArcs.begin(), m_lArcs.end(), pArc) != m_lArcs.end()) return  true;
	return false;
}

bool raaDataLayer::hasArc(raaDataArc* pArc)
{
	if (pArc&&std::find(m_lArcs.begin(), m_lArcs.end(), pArc)!=m_lArcs.end()) return true;
	return false;
}

int raaDataLayer::arcIndex(raaDataArc* pArc)
{
	if (hasArc(pArc))
		return std::find(m_lArcs.begin(), m_lArcs.end(), pArc) - m_lArcs.begin();

		return -1;
}

void raaDataLayer::refActive()
{
	if (++m_uiActiveCount)
	{
//		std::cout << "Layer active -> " << m_uiActiveCount << std::endl;
		for (raaDataArcs::iterator it = m_lArcs.begin(); it != m_lArcs.end(); it++)
			(*it)->refActiveCount();
	}
}

void raaDataLayer::unrefActive()
{
	if (!--m_uiActiveCount)
	{
//		std::cout << "Layer active -> " << m_uiActiveCount << std::endl;
		for (raaDataArcs::iterator it = m_lArcs.begin(); it != m_lArcs.end(); it++)
			(*it)->unrefActiveCount();
	}
}

bool raaDataLayer::active()
{
//	std::cout << "Layer active -> " << m_uiActiveCount << std::endl;
	return m_uiActiveCount?true:false;
}

void raaDataLayer::normaliseArcWeights()
{
	float fMin, fMax;
	bool bFirst = true;

	for (int i = 0; i < m_lArcs.size();i++)
	{
		if (bFirst)
		{
			fMin = fMax = m_lArcs[i]->weight();
			bFirst = false;
		}
		else
		{
			fMin = (fMin < m_lArcs[i]->weight()) ? m_lArcs[i]->weight() : fMin;
			fMax = (fMax > m_lArcs[i]->weight()) ? m_lArcs[i]->weight() : fMax;
		}
	}

	float fRange = fMax - fMin;

	for (int i = 0; i < m_lArcs.size(); i++)
	{
		m_lArcs[i]->setWeight(0.1f + (m_lArcs[i]->weight() - fMin) / fRange);
	}
}

void raaDataLayer::normaliseArcLengths(float fMin, float fMax)
{
	float _fMin, _fMax;
	bool bFirst = true;

	for (int i = 0; i < m_lArcs.size(); i++)
	{
		if (bFirst)
		{
			_fMin = _fMax = m_lArcs[i]->idealLength();
			bFirst = false;
		}
		else
		{
			_fMin = (_fMin < m_lArcs[i]->idealLength()) ? m_lArcs[i]->idealLength() : _fMin;
			_fMax = (_fMax > m_lArcs[i]->idealLength()) ? m_lArcs[i]->idealLength() : _fMax;
		}
	}

	float fRange = _fMax - _fMin;
	float fR = fMax - fMin;

	for (int i = 0; i < m_lArcs.size(); i++)
	{
		m_lArcs[i]->setIdealLength(((m_lArcs[i]->weight() - _fMin) / fRange)*fR+fMin);
	}
}

const raaVector& raaDataLayer::colour()
{
	return m_vColour;
}

void raaDataLayer::setColour(raaVector v)
{
	m_vColour = v;

	for (raaDataArcs::iterator it = m_lArcs.begin(); it != m_lArcs.end(); it++) (*it)->setColour(v);
}

void raaDataLayer::setLayerStrength(float fWeight)
{
	if (fWeight == 0.0f) fWeight = 0.001f;
	
	m_fLayerStrength = fWeight;

	for (raaDataArcs::iterator it = m_lArcs.begin(); it != m_lArcs.end(); it++) (*it)->setWeightMultiplier(m_fLayerStrength);

}

float raaDataLayer::layerStrength()
{
	return m_fLayerStrength;
}

raaDataLayer::~raaDataLayer()
{
	for (raaDataArcs::iterator it = m_lArcs.begin(); it != m_lArcs.end();it++) (*it)->unrefActiveCount(true);
}
