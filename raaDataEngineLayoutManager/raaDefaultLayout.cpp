
#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>


#include "raaDefaultLayout.h"


void raaDefaultLayout::start(raaParameters& pParams)
{
	unpinAll();

	float fDist = 10.0f;
	if (pParams.find("dist") != pParams.end()) fDist = atof(pParams["dist"].c_str());

	raaDataNodeGroup res1 = raaDataEngine::instance()->currentModel()->nodeGroup("Result::1");
	raaDataNodeGroup res2 = raaDataEngine::instance()->currentModel()->nodeGroup("Result::2");

	raaVector vStep(0.0f, 0.0f, 3.0f);
	int iSize = res1.size() >> 1;
	raaVector vPos(-fDist, 0.0f, -3.0f*iSize);

	for (raaDataNodeGroup::iterator it = res1.begin(); it != res1.end();it++)
	{
		m_mLayoutSet[*it].m_vStart = (*it)->position();
		m_mLayoutSet[*it].m_vEnd = vPos;
		vPos += vStep;
	}

	vPos.set(fDist, 0.0f, -3.0f*iSize);

	for (raaDataNodeGroup::iterator it = res2.begin(); it != res2.end(); it++)
	{
		m_mLayoutSet[*it].m_vStart = (*it)->position();
		m_mLayoutSet[*it].m_vEnd = vPos;
		vPos += vStep;
	}

	pin(res1);
	pin(res2);
}

void raaDefaultLayout::finish()
{
	m_mLayoutSet.clear();
}

raaDefaultLayout::raaDefaultLayout()
{
}


raaDefaultLayout::~raaDefaultLayout()
{
}
