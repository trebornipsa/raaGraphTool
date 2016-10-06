#pragma once

#include<list>
#include <string>
#include <map>

#include <raaUtilities/raaVector.h>
#include <raaUtilities/raaNode.h>

#include "raaDataEngineDefs.h"

typedef std::list<std::string> raaNodeGroups;
typedef std::map<std::string, unsigned int> raaNodeGroupCounts;

class RAADATAENGINE_DLL_DEF raaDataNode : public raaNode
{
public:
	virtual raaVector position();
	virtual void setPosition(raaVector v);

	virtual void setMass(float fMass);
	virtual float mass();

	raaDataNode(std::string sName, std::string sGroup = "default");
	raaDataNode(std::string sName, raaNodeGroups& groups);

	void clearForce();
	void addForce(raaVector v);
	float applyForce(float fTime, float fDamping);
	raaVector force();

	void setActive(bool bActive);
	bool isActive();
	void toggleActive();
	void suspendActive(bool bSuspend);

	void initCluster();
	void setClusterVisited(bool bVisited=true);
	void setClustered(bool bClustered=true);
	bool clusterVisited();
	bool clustered();

	raaVector velocity();

	unsigned int activityCount();
	virtual void activityRef();
	virtual void activityUnref();

	void addToGroup(std::string sGroup);
	void addToGroups(raaNodeGroups &groups);
	void removeFromGroup(std::string sGroup);
	void removeFromGroups(raaNodeGroups &groups);
	bool isInGroup(std::string sName);
	const raaNodeGroups& groups();

	static bool hasGroup(std::string sGroup);
	static unsigned int numInGroup(std::string sGroup);
	static const raaNodeGroupCounts& nodeGroups();

	virtual void pin(bool bPin);
	virtual bool pinned();
	virtual void togglePin();

protected:
	virtual ~raaDataNode();
	float m_fMass;
	raaVector m_vPosition;
	raaVector m_vForce;
	raaVector m_vVelocity;
//	bool m_bActive;

	bool m_bPinned;

	bool m_bClustered;
	bool m_bClusterVisited;

	unsigned int m_uiActivityCount;
	unsigned int m_uiSuspendedActivityCount;

	raaNodeGroups m_lGroups;
	static raaNodeGroupCounts sm_lNodeGroups;

};
