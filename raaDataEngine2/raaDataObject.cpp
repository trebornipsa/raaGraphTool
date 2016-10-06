#include "raaDataObject.h"

raaDE2::raaDataObject::raaDataObject(std::string sName)
{
	m_sName=sName;
	m_bIsActive = true;
}

raaDE2::raaDataObject::raaDataObject(std::string sName, bool bDeletable) :raaReferenced(bDeletable)
{
	m_sName = sName;
}

raaDE2::raaDataObject::raaDataObject(bool bDeletable) : raaReferenced(bDeletable)
{
}

raaDE2::raaDataObject::raaDataObject()
{
}

raaDE2::raaDataObject::~raaDataObject()
{
}

std::string raaDE2::raaDataObject::name()
{
	return m_sName;
}

void raaDE2::raaDataObject::refActivityCounter(std::string sName)
{
	if (sName.length())
	{
		initCounter(sName);
		m_mLastActivityCounters[sName]=m_mActivityCounters[sName]++;
		m_bIsActive = _isActive();
		m_bWasActive = _wasActive();
		activeChanged(sName);
	}
}

unsigned int raaDE2::raaDataObject::unrefActivityCounter(std::string sName)
{
	if (sName.length())
	{
		initCounter(sName);
		m_mLastActivityCounters[sName] = m_mActivityCounters[sName]--;
		m_bIsActive = _isActive();
		m_bWasActive = _wasActive();
		activeChanged(sName);
		return m_mActivityCounters[sName];
	}
	return 0;
}

unsigned raaDE2::raaDataObject::activityCount(std::string sName)
{
	if (sName.length())
	{
		initCounter(sName);
		return m_mActivityCounters[sName];
	}
	return 0;
}

void raaDE2::raaDataObject::setActivityCount(std::string sName, unsigned uiCount)
{
	if (sName.length())
	{
		initCounter(sName);
		m_mLastActivityCounters[sName] = m_mActivityCounters[sName];
		m_mActivityCounters[sName] = uiCount;
		m_bIsActive = _isActive();
		m_bWasActive = _wasActive();
		activeChanged(sName);
	}
}

void raaDE2::raaDataObject::setActivityCount(std::string sName, bool bState)
{
	if (sName.length())
	{
		initCounter(sName);
		m_mLastActivityCounters[sName] = m_mActivityCounters[sName];
		m_mActivityCounters[sName] = bState ? 1 : 0;
		m_bIsActive = _isActive();
		m_bWasActive = _wasActive();
		activeChanged(sName);
	}
}

bool raaDE2::raaDataObject::isActive(std::string sName)
{
	if (sName.length() && m_mActivityCounters.find(sName) != m_mActivityCounters.end()) return m_mActivityCounters[sName] ? true : false;;
	return false;
}

bool raaDE2::raaDataObject::isActive(raaStringList& lNames)
{
	bool bRet = false;

	for (raaStringList::iterator it = lNames.begin(); it != lNames.end(); it++) bRet = isActive(*it) ? true : bRet;

	return bRet;
}

bool raaDE2::raaDataObject::_isActive()
{
	bool bRet = false;

	for (raaUIMap::iterator it = m_mActivityCounters.begin(); it != m_mActivityCounters.end(); it++) bRet = it->second ? true : bRet;

	return bRet;
}

bool raaDE2::raaDataObject::_wasActive()
{
	bool bRet = false;

	for (raaUIMap::iterator it = m_mLastActivityCounters.begin(); it != m_mLastActivityCounters.end(); it++) bRet = it->second ? true : bRet;

	return bRet;
}

bool raaDE2::raaDataObject::isActive()
{
	return m_bIsActive;
}

bool raaDE2::raaDataObject::wasActive()
{
	return m_bWasActive;
}


bool raaDE2::raaDataObject::wasActive(std::string sName)
{
	if (sName.length() && m_mLastActivityCounters.find(sName) != m_mLastActivityCounters.end()) return m_mLastActivityCounters[sName] ? true : false;;
	return false;
}

bool raaDE2::raaDataObject::wasActive(raaStringList& lNames)
{
	bool bRet = false;

	for (raaStringList::iterator it = lNames.begin(); it != lNames.end(); it++) bRet = wasActive(*it) ? true : bRet;

	return bRet;
}

void raaDE2::raaDataObject::setAttribute(std::string sName, float fAttrib)
{
	if(sName.length()) m_mAttributes[sName] = fAttrib;
}

float raaDE2::raaDataObject::attribute(std::string sName)
{
	if (sName.length() && m_mAttributes.find(sName) != m_mAttributes.end()) return m_mAttributes[sName];
	return 0.0f;
}

void raaDE2::raaDataObject::initCounter(std::string sName)
{
	if (m_mActivityCounters.find(sName) == m_mActivityCounters.end())
	{
		m_mActivityCounters[sName] = 0;
		m_mLastActivityCounters[sName] = 0;
	}
}
