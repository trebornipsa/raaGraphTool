#include <raaUtilities/raaUtilities.h>

#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>

#include "raaOpposingRingLayout.h"

void raaOpposingRingLayout::start(raaParameters& pParams)
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


	float fAng2 = raaUtilities::deg2rad(-180.0f / ((float)(res2.size() + 1)));
	float fAng1 = raaUtilities::deg2rad(-180.0f / ((float)(res1.size() + 1)));

	raaMatrix m2, m1;
	m2.rotate(vAxis, fAng2);
	m1.rotate(vAxis, fAng1);

	for (raaNodeGroup::iterator it = res2.begin(); it != res2.end(); it++)
	{
		v2 = v2*m2;
		raaVector vPos = v2*(fDist);

		m_mLayoutSet[*it].m_vStart = (*it)->position();
		m_mLayoutSet[*it].m_vEnd = vPos;
	}

	for (raaNodeGroup::iterator it = res1.begin(); it != res1.end(); it++)
	{
		v1 = v1*m1;
		raaVector vPos = v1*(fDist);
		m_mLayoutSet[*it].m_vStart = (*it)->position();
		m_mLayoutSet[*it].m_vEnd = vPos;
	}

	pin(res1);
	pin(res2);
}

void raaOpposingRingLayout::finish()
{
	m_mLayoutSet.clear();
}

raaOpposingRingLayout::raaOpposingRingLayout()
{
}


raaOpposingRingLayout::~raaOpposingRingLayout()
{
}
