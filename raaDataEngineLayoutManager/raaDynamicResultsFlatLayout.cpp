#include <raaUtilities/raaUtilities.h>

#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>

#include "raaDynamicResultsFlatLayout.h"

void raaDynamicResultsFlatLayout::start(raaParameters& pParams)
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

	for (raaDataNodeGroups::const_iterator cit = raaDataEngine::instance()->currentModel()->nodeGroups().begin(); cit != raaDataEngine::instance()->currentModel()->nodeGroups().end(); cit++)
	{
		if (cit->first != "Default" && cit->first.find("Result::") == std::string::npos)
		{
			for (raaDataNodeGroup::const_iterator it = cit->second.begin(); it != cit->second.end(); it++)
			{
				m_mLayoutSet[(*it)].m_vStart = (*it)->position();
				m_mLayoutSet[(*it)].m_vEnd = v2;
			}
			pin(cit->second);
			v2 = v2*m;
		}
	}

}

void raaDynamicResultsFlatLayout::finish()
{
	m_mLayoutSet.clear();
}

raaDynamicResultsFlatLayout::~raaDynamicResultsFlatLayout()
{
}

raaDynamicResultsFlatLayout::raaDynamicResultsFlatLayout()
{
}
