#include <raaUtilities/raaUtilities.h>

#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>

#include "raaDynamicResultsLayout.h"

void raaDynamicResultsLayout::start(raaParameters& pParams)
{
	unpinAll();
	m_mLayoutSet.clear();

	float fDist = 10.0f;
	if (pParams.find("dist") != pParams.end()) fDist = atof(pParams["dist"].c_str());


	unsigned int uiNumGroups = raaDataEngine::instance()->currentModel()->nodeGroups().size() - 3;

	raaVector v2(0.0f, 0.0f, fDist);
	raaVector vAxis(0.0f, 1.0f, 0.0f);

	float fAng = raaUtilities::deg2rad(-360.0f / ((float)(uiNumGroups)));

	raaMatrix m;
	m.rotate(vAxis, fAng);

	for (raaDataNodeGroups::const_iterator cit = raaDataEngine::instance()->currentModel()->nodeGroups().begin(); cit != raaDataEngine::instance()->currentModel()->nodeGroups().end();cit++)
	{
		if(cit->first!="Default" && cit->first.find("Result::")==std::string::npos)
		{
			unsigned int uiNum = cit->second.size();
			raaVector vPos(0.0f, -fDist, 0.0f);
			raaVector vStep(0.0f, (2.0f*fDist) / ((float)uiNum-1), 0.0f);

			for (raaDataNodeGroup::const_iterator it = cit->second.begin(); it != cit->second.end();it++)
			{
				m_mLayoutSet[(*it)].m_vStart = (*it)->position();
				m_mLayoutSet[(*it)].m_vEnd = vPos+v2;
				vPos += vStep;
			}
			pin(cit->second);
			v2 = v2*m;
		}
	}
}

void raaDynamicResultsLayout::finish()
{
	m_mLayoutSet.clear();
}

raaDynamicResultsLayout::raaDynamicResultsLayout()
{
}


raaDynamicResultsLayout::~raaDynamicResultsLayout()
{
}
