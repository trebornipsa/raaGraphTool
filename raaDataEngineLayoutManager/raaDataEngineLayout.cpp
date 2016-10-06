#include <raaDataEngine/raaDataNode.h>
#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>
#include "raaDataEngineLayout.h"

raaDataEngineLayout::raaDataEngineLayout()
{
}

raaDataEngineLayout::~raaDataEngineLayout()
{
}

void raaDataEngineLayout::apply(float fProg)
{
	for (raaLayoutSet::iterator it = m_mLayoutSet.begin(); it != m_mLayoutSet.end();it++)
	{
		it->first->setPosition(it->second.m_vStart.slerp(it->second.m_vEnd, fProg));
	}
}

void raaDataEngineLayout::unpin(raaDataNodeGroup& rGroup)
{
	for (raaDataNodeGroup::iterator it = rGroup.begin(); it != rGroup.end(); it++) (*it)->pin(false);
}

void raaDataEngineLayout::unpin(const raaDataNodeGroup& rGroup)
{
	for (raaDataNodeGroup::const_iterator it = rGroup.begin(); it != rGroup.end(); it++) (*it)->pin(false);
}

void raaDataEngineLayout::pin(raaDataNodeGroup& rGroup)
{
	for (raaDataNodeGroup::iterator it = rGroup.begin(); it != rGroup.end(); it++) (*it)->pin(true);
}

void raaDataEngineLayout::pin(const raaDataNodeGroup& rGroup)
{
	for (raaDataNodeGroup::const_iterator it = rGroup.begin(); it != rGroup.end(); it++) (*it)->pin(true);
}

void raaDataEngineLayout::unpinAll()
{
	for (raaDataNodeMap::const_iterator it = raaDataEngine::instance()->currentModel()->nodes().begin(); it != raaDataEngine::instance()->currentModel()->nodes().end(); it++)
		it->second->pin(false);
}
