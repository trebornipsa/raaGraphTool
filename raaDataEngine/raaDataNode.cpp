
#include "raaDataModel.h"
#include "raaDataNode.h"

raaNodeGroupCounts raaDataNode::sm_lNodeGroups;

raaVector raaDataNode::position()
{
	return m_vPosition;
}

void raaDataNode::setPosition(raaVector v)
{
	m_vPosition = v;
}

void raaDataNode::setMass(float fMass)
{
	m_fMass = fMass;
}

float raaDataNode::mass()
{
	return m_fMass;
}

raaDataNode::raaDataNode(std::string sName, std::string sGroup) : raaNode(sName)
{
	m_fMass = 1.0f;
	m_vPosition.set(0.0f, 0.0f, 0.0f, 0.0f);
	m_vVelocity.set(0.0f, 0.0f, 0.0f, 0.0f);
	m_bPinned = false;
	m_uiActivityCount = 0;

	m_uiSuspendedActivityCount = 0;

	m_lGroups.push_back(sGroup);
	if (sm_lNodeGroups.find(sGroup) == sm_lNodeGroups.end()) sm_lNodeGroups[sGroup] = 0;
	sm_lNodeGroups[sGroup]++;
}

raaDataNode::raaDataNode(std::string sName, raaNodeGroups& groups)
{
	m_fMass = 1.0f;
	m_vPosition.set(0.0f, 0.0f, 0.0f, 0.0f);
	m_vVelocity.set(0.0f, 0.0f, 0.0f, 0.0f);
//	m_bActive = true;
	m_bPinned = false;

	m_uiActivityCount = 0;
	m_uiSuspendedActivityCount = 0;

	if (groups.size())
	{
		m_lGroups.splice(m_lGroups.end(), groups);

		for (raaNodeGroups::iterator it = m_lGroups.begin(); it != m_lGroups.end(); it++)
		{
			std::string sGroup = (*it);
			if (sm_lNodeGroups.find(sGroup) == sm_lNodeGroups.end()) sm_lNodeGroups[sGroup] = 0;
			sm_lNodeGroups[sGroup]++;
		}
	}
}


void raaDataNode::togglePin()
{
	pin(!m_bPinned);
}

raaDataNode::~raaDataNode()
{
	for (raaNodeGroups::iterator it = m_lGroups.end(); it != m_lGroups.end(); it++)
	{
		std::string sGroup = (*it);
		if (--sm_lNodeGroups[sGroup]) sm_lNodeGroups.erase(sGroup);
	}
}

void raaDataNode::clearForce()
{
	m_vForce.set(0.0f, 0.0f, 0.0f, 0.0f);
}

void raaDataNode::addForce(raaVector v)
{
	if(m_uiActivityCount && !m_bPinned) m_vForce += v;
}

float raaDataNode::applyForce(float fTime, float fDamping)
{
	if (m_uiActivityCount && !m_bPinned)
	{
		raaVector vAcc, vDisp;
		vAcc = m_vForce/ m_fMass;
		vDisp = (m_vVelocity*fTime) + (vAcc*(0.5f*fTime*fTime));
		setPosition( m_vPosition+vDisp);
		m_vVelocity = (vDisp / fTime)*fDamping;
	//	m_vVelocity *= fDamping;
		return m_fMass*m_vVelocity.length();
	}
	return 0.0f;
}

raaVector raaDataNode::force()
{
	return m_vForce;
}

void raaDataNode::setActive(bool bActive)
{


	if (!bActive) m_uiActivityCount++;
	else m_vVelocity.set(0.0f, 0.0f, 0.0f, 0.0f);
}

bool raaDataNode::isActive()
{
	return m_uiActivityCount ? 1 : 0;
}

void raaDataNode::toggleActive()
{
	setActive(!isActive());
}

void raaDataNode::suspendActive(bool bSuspend)
{
	if(bSuspend)
	{
		if (!m_uiSuspendedActivityCount)
		{
			m_uiSuspendedActivityCount = m_uiActivityCount;
			m_vVelocity.set(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}
	else
	{
		m_uiActivityCount = m_uiSuspendedActivityCount;
	}
}

void raaDataNode::initCluster()
{
	m_bClusterVisited = false;
	m_bClustered = false;
}

void raaDataNode::setClusterVisited(bool bVisited)
{
	m_bClusterVisited = bVisited;
}

void raaDataNode::setClustered(bool bClustered)
{
	m_bClustered = bClustered;
}

bool raaDataNode::clusterVisited()
{
	return m_bClusterVisited;
}

bool raaDataNode::clustered()
{
	return m_bClustered;
}

raaVector raaDataNode::velocity()
{
	return m_vVelocity;
}

unsigned raaDataNode::activityCount()
{
	return m_uiActivityCount;
}

void raaDataNode::activityRef()
{
	m_uiActivityCount++;
	dataChanged();
}

void raaDataNode::activityUnref()
{
	if(m_uiActivityCount) m_uiActivityCount--;
	dataChanged();
	if (!m_uiActivityCount) m_vVelocity.set(0.0f, 0.0f, 0.0f, 0.0f);
}

void raaDataNode::addToGroup(std::string sGroup)
{
	if(sGroup.size() && std::find(m_lGroups.begin(), m_lGroups.end(), sGroup)==m_lGroups.end())
	{

		if (!hasGroup(sGroup)) sm_lNodeGroups[sGroup] = 0;
		sm_lNodeGroups[sGroup]++;
		m_lGroups.push_back(sGroup);
	}
}

void raaDataNode::addToGroups(raaNodeGroups &groups)
{
	if(groups.size())
	{
		for (raaNodeGroups::iterator it = groups.begin(); it != groups.end();it++)
		{
			std::string sGroup = (*it);
			addToGroup(sGroup);
		}
	}
}

void raaDataNode::removeFromGroup(std::string sGroup)
{
	if (sGroup.size() && std::find(m_lGroups.begin(), m_lGroups.end(),sGroup)!=m_lGroups.end())
	{
		if (!--sm_lNodeGroups[sGroup]) sm_lNodeGroups.erase(sGroup);
		m_lGroups.erase(std::find(m_lGroups.begin(), m_lGroups.end(), sGroup));
	}
}

void raaDataNode::removeFromGroups(raaNodeGroups &groups)
{
	if(groups.size())
	{
		for (raaNodeGroups::iterator it = groups.begin(); it != groups.end();it++)
		{
			std::string sGroup = (*it);
			removeFromGroup(sGroup);
		}
	}
}


bool raaDataNode::isInGroup(std::string sName)
{
	if (sName.size() && std::find(m_lGroups.begin(), m_lGroups.end(), sName) != m_lGroups.end()) return true;
	return false;
}

const raaNodeGroups& raaDataNode::groups()
{
	return m_lGroups;
}

bool raaDataNode::hasGroup(std::string sGroup)
{
	if (sGroup.size() && sm_lNodeGroups.find(sGroup) != sm_lNodeGroups.end()) return true;
	return false;
}

unsigned int raaDataNode::numInGroup(std::string sGroup)
{
	if (sGroup.size() && sm_lNodeGroups.find(sGroup) != sm_lNodeGroups.end()) return sm_lNodeGroups[sGroup];
	return 0;
}

const raaNodeGroupCounts& raaDataNode::nodeGroups()
{
	return sm_lNodeGroups;
}

void raaDataNode::pin(bool bPin)
{
	m_bPinned = bPin;
	if (!m_bPinned) m_vVelocity.set(0.0f, 0.0f, 0.0f, 0.0f);
}

bool raaDataNode::pinned()
{
	return m_bPinned;
}
