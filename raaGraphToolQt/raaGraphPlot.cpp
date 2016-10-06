#include "stdafx.h"
#include "raaGraphPlot.h"


raaGraphPlot::raaGraphPlot(std::string sName, raaVector &vColour, unsigned int uiMaxPoints, unsigned int uiNormMode)
{
	setMaxPoints(uiMaxPoints);
	m_sName = sName;
	m_vColour = vColour;
	m_uiNormMode = uiNormMode;
}

raaGraphPlot::~raaGraphPlot()
{
}

void raaGraphPlot::setMaxPoints(unsigned uiMaxPoints)
{
	m_uiMaxNumPoints = uiMaxPoints;
	while (m_Data.size() > uiMaxPoints) m_Data.pop_front();
	while (m_Data.size() < uiMaxPoints) m_Data.push_front(0.0f);
	while (m_NormData.size() > uiMaxPoints) m_NormData.pop_front();
	while (m_NormData.size() < uiMaxPoints) m_NormData.push_front(0.0f);
	calcMinMax();
	normliseData();
}

unsigned raaGraphPlot::maxPoints()
{
	return m_uiMaxNumPoints;
}



void raaGraphPlot::addPoint(float f)
{
	m_Data.push_back(f);
	if (m_Data.size() > m_uiMaxNumPoints) m_Data.pop_front();



	switch (m_uiNormMode)
	{
	case csm_uiNormUp:
		if (f > m_fMax) m_fMax = f;
		normliseData();
		break;
	case csm_uiNormUpDown:
		calcMinMax();
		normliseData();
		break;
	default:
	{
		raaPlotData::iterator nit = m_NormData.begin();

		for (raaPlotData::iterator it = m_Data.begin(); it != m_Data.end() && nit != m_NormData.end(); it++, nit++) (*nit) = (*it);
	}
	break;
	}
}

void raaGraphPlot::addPoint(int i)
{
	m_Data.push_back((float)i);
	if (m_Data.size() > m_uiMaxNumPoints) m_Data.pop_front();

	switch (m_uiNormMode)
	{
	case csm_uiNormUp:
		if (((float)i) > m_fMax) m_fMax = ((float)i);
		normliseData();
		break;
	case csm_uiNormUpDown:
		calcMinMax();
		normliseData();
		break;
	default:
		{
			raaPlotData::iterator nit = m_NormData.begin();

			for (raaPlotData::iterator it = m_Data.begin(); it != m_Data.end() && nit != m_NormData.end(); it++, nit++) (*nit) = (*it);
		}
		break;
	}
}

const raaPlotData& raaGraphPlot::data() const
{
	return m_Data;
}

const raaPlotData& raaGraphPlot::normData() const
{
	return m_NormData;
}

const raaVector& raaGraphPlot::colour() const
{
	return m_vColour;
}

void raaGraphPlot::calcMinMax()
{
	raaPlotData::iterator it = m_Data.begin();
	m_fMax = m_fMin = (*it);
	for (it++;it!=m_Data.end();it++)
	{
		m_fMax = (m_fMax < (*it)) ? (*it) : m_fMax;
		m_fMin = (m_fMin > (*it)) ? (*it) : m_fMin;
	}
}

void raaGraphPlot::normliseData()
{
	raaPlotData::iterator nit = m_NormData.begin();
	if (m_fMax > 0.0001f)
		for (raaPlotData::iterator it = m_Data.begin(); it != m_Data.end() && nit!=m_NormData.end(); it++, nit++) (*nit)= (*it) / m_fMax;
	else
		for (raaPlotData::iterator it = m_Data.begin(); it != m_Data.end() && nit != m_NormData.end(); it++, nit++) (*nit) = (*it);
}
