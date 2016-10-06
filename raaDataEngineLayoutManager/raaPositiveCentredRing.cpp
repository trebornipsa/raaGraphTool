#include <raaUtilities/raaUtilities.h>

#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>

#include "raaPositiveCentredRing.h"

void raaPositiveCentredRing::start(raaParameters& pParams)
{
	unpinAll();
	m_mLayoutSet.clear();

	float fDist = 10.0f;
	if (pParams.find("dist") != pParams.end()) fDist = atof(pParams["dist"].c_str());

	raaDataNodeGroup res1 = raaDataEngine::instance()->currentModel()->nodeGroup("Result::1");
	raaDataNodeGroup res2 = raaDataEngine::instance()->currentModel()->nodeGroup("Result::2");

	raaVector v2(0.0f, 0.0f, 1.0f);
	raaVector v1(0.0f, 0.0f, -1.0f);
	raaVector vOrigin(0.0f, 0.0f, 0.0f);
	raaVector vAxis(0.0f, 1.0f, 0.0f);

	raaVector vO2(0.0f, 0.0f, 0.0f);
	raaVector vA2(1.0f, 0.0f, 0.0f);
	raaVector v3(0.0f, 1.0f, 0.0f);

	float fAng = raaUtilities::deg2rad(-360.0f / ((float)(res2.size())));

	raaMatrix m;
	m.rotate(vAxis, fAng);

	for (raaNodeGroup::iterator it = res1.begin(); it != res1.end(); it++)
	{
		v2 = v2*m;
		raaVector vPos = v2*(fDist);

		m_mLayoutSet[*it].m_vStart = (*it)->position();
		m_mLayoutSet[*it].m_vEnd = vPos;
	}

	for (raaNodeGroup::iterator it = res2.begin(); it != res2.end(); it++)
	{
		m_mLayoutSet[*it].m_vStart = (*it)->position();
		m_mLayoutSet[*it].m_vEnd = raaVector(0.0f, 0.0f, 0.0f);
	}

	pin(res1);
	pin(res2);
}

void raaPositiveCentredRing::finish()
{
	m_mLayoutSet.clear();
}

raaPositiveCentredRing::raaPositiveCentredRing()
{
}


raaPositiveCentredRing::~raaPositiveCentredRing()
{
}
