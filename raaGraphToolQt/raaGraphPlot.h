#pragma once

#include <list>
#include <string>
#include <raaUtilities/raaVector.h>

typedef std::list<float> raaPlotData;

class raaGraphPlot
{
public:
	const static unsigned int csm_uiNoNorm = 0;
	const static unsigned int csm_uiNormUp = 1;
	const static unsigned int csm_uiNormUpDown = 2;


	raaGraphPlot(std::string sName, raaVector &vColour, unsigned int uiMaxPoints=250, unsigned int uiNormMode=csm_uiNormUp);
	virtual ~raaGraphPlot();

	void setMaxPoints(unsigned int uiMaxPoints);
	unsigned int maxPoints();

	void addPoint(float f);
	void addPoint(int i);

	const raaPlotData& data() const;
	const raaPlotData& normData() const;

	const raaVector& colour() const;

protected:
	void calcMinMax();
	void normliseData();
	unsigned int m_uiMaxNumPoints;
	raaPlotData m_Data;
	raaPlotData m_NormData;
	raaVector m_vColour;
	std::string m_sName;
	float m_fMin;
	float m_fMax;
	unsigned int m_uiNormMode;
};

