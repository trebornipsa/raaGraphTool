#include <cstdlib>
#include <sstream>
#include <iostream>
#include "raaDataUID.h"


unsigned int raaDE2::raaDataUID::sm_uiInstance = 0;
bool raaDE2::raaDataUID::sm_bInit = false;;
time_t raaDE2::raaDataUID::sm_Timer;

raaDE2::raaDataUID::raaDataUID()
{
	init();
	m_Data.m_uiInstance = sm_uiInstance++;
	m_Data.m_uiTime = ::time(&sm_Timer);
	m_Data.m_uiRand = ::rand();
	std::stringstream ss;
	ss << m_Data.m_uiTime << ":" << m_Data.m_uiInstance << ":" << m_Data.m_uiRand;
	m_sUID = ss.str();
}

raaDE2::raaDataUID::raaDataUID(const raaDataUID& uid)
{
	m_Data.m_uiInstance = uid.m_Data.m_uiInstance;
	m_Data.m_uiTime = uid.m_Data.m_uiTime;
	m_Data.m_uiRand = uid.m_Data.m_uiRand;
	std::stringstream ss;
	ss << m_Data.m_uiTime << ":" << m_Data.m_uiInstance << ":" << m_Data.m_uiRand;
	m_sUID = ss.str();
}

raaDE2::raaDataUID::raaDataUID(const raaUID& uid)
{
	m_Data.m_uiInstance = uid.m_uiInstance;
	m_Data.m_uiTime = uid.m_uiTime;
	m_Data.m_uiRand = uid.m_uiRand;
	std::stringstream ss;
	ss << m_Data.m_uiTime << ":" << m_Data.m_uiInstance << ":" << m_Data.m_uiRand;
	m_sUID = ss.str();
}

raaDE2::raaDataUID::~raaDataUID()
{
}

bool raaDE2::raaDataUID::operator==(const raaDataUID& uid) const
{
	if (m_Data.m_uiInstance == uid.m_Data.m_uiInstance && m_Data.m_uiRand == uid.m_Data.m_uiRand && m_Data.m_uiTime == uid.m_Data.m_uiTime) return true;
	return false;
}

bool raaDE2::raaDataUID::operator<(const raaDataUID& uid) const
{
	unsigned int uiD = m_Data.m_uiInstance + m_Data.m_uiTime + m_Data.m_uiRand;
	unsigned int uiS = uid.m_Data.m_uiInstance + uid.m_Data.m_uiTime + uid.m_Data.m_uiRand;

	if (uiD < uiS) return true;
	if (uiD > uiS) return false;

	unsigned int uiD2 = m_Data.m_uiInstance + m_Data.m_uiRand;
	unsigned int uiS2 = uid.m_Data.m_uiInstance + uid.m_Data.m_uiRand;

	if (uiD2 < uiS2) return true;
	if (uiD2 > uiS2) return false;

	return m_Data.m_uiInstance < uid.m_Data.m_uiInstance;
}

const raaDE2::raaDataUID& raaDE2::raaDataUID::operator=(const raaDataUID& uid)
{
	m_Data.m_uiTime = uid.m_Data.m_uiTime;
	m_Data.m_uiInstance = uid.m_Data.m_uiInstance;
	m_Data.m_uiRand = uid.m_Data.m_uiRand;
	m_sUID = uid.m_sUID;
//	m_sSerialUID = serialize(*this);
	return uid;
}

unsigned raaDE2::raaDataUID::instance()
{
	return m_Data.m_uiInstance;
}

unsigned raaDE2::raaDataUID::time()
{
	return m_Data.m_uiTime;
}

unsigned raaDE2::raaDataUID::rand()
{
	return m_Data.m_uiRand;
}

std::string raaDE2::raaDataUID::uid()
{
	return m_sUID;
}

std::string raaDE2::raaDataUID::serialUid()
{
	return m_sSerialUID;
}


void raaDE2::raaDataUID::print()
{
	std::cout << "uid->" << m_Data.m_uiInstance << "::" << m_Data.m_uiTime << "::" << m_Data.m_uiRand << std::endl;
}

const char* raaDE2::raaDataUID::serialize()
{
	return (const char*)&m_Data;
}

void raaDE2::raaDataUID::unserialize(const char *pcData)
{
	raaUID *pData = (raaUID*)pcData;
	m_Data.m_uiInstance = pData->m_uiInstance;
	m_Data.m_uiTime = pData->m_uiTime;
	m_Data.m_uiRand = pData->m_uiRand;
}

void raaDE2::raaDataUID::init()
{
	if(!sm_bInit)
	{
		::srand(sm_Timer);
		sm_bInit = true;
	}
}
