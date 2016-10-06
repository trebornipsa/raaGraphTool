#include "raaReferenced.h"

unsigned int raaDE2::raaReferenced::raaReferencedManager::sm_uiInstance=0;
raaDE2::raaReferenced::raaReferencedManager* raaDE2::raaReferenced::raaReferencedManager::sm_pInstance=0;

raaDE2::raaReferenced::raaReferenced(bool bDeletable)
{
	if (!raaReferencedManager::instance()) raaReferencedManager::start();
	m_bDeletable = bDeletable;
	m_uiRefCount = 0;
	raaReferencedManager::instance()->add(this);
}

void raaDE2::raaReferenced::ref()
{
	m_uiRefCount++;
}

void raaDE2::raaReferenced::unref(bool bDelete)
{
	m_uiRefCount--;

	if(!m_uiRefCount && m_bDeletable && bDelete)
	{
		aboutToDelete();
		raaReferencedManager::instance()->toGarbage(this);
	}
}

unsigned raaDE2::raaReferenced::refCount()
{
	return m_uiRefCount;
}

raaDE2::raaDataUID& raaDE2::raaReferenced::uid()
{
	return m_uid;
}

raaDE2::raaReferenced::~raaReferenced()
{
}

void raaDE2::raaReferenced::raaReferencedManager::start()
{
	if (!sm_pInstance && !sm_uiInstance++) new raaReferencedManager();
}

void raaDE2::raaReferenced::raaReferencedManager::stop()
{
	if (sm_pInstance && !--sm_uiInstance) delete sm_pInstance;
}

raaDE2::raaReferenced::raaReferencedManager* raaDE2::raaReferenced::raaReferencedManager::instance()
{
	return sm_pInstance;
}

void raaDE2::raaReferenced::raaReferencedManager::add(raaReferenced* pRef)
{
	if(pRef)
	{
		if (m_mObjects.find(pRef->uid()) == m_mObjects.end()) m_mObjects[pRef->uid()] = pRef;
	}
}

void raaDE2::raaReferenced::raaReferencedManager::toGarbage(raaReferenced* pRef)
{
	if(pRef)
	{
		m_mObjects.erase(pRef->uid());
		m_lGarbage.push_back(pRef);
	}
}

void raaDE2::raaReferenced::raaReferencedManager::removeTrash()
{
	for (raaReferencedList::iterator it = m_lGarbage.begin(); it != m_lGarbage.end(); it++) delete (*it);
	m_lGarbage.clear();
}

raaDE2::raaReferenced* raaDE2::raaReferenced::raaReferencedManager::find(raaDataUID uid)
{
	if (m_mObjects.find(uid) != m_mObjects.end()) return m_mObjects[uid];
	return 0;
}

raaDE2::raaReferenced::raaReferencedManager::raaReferencedManager()
{
	if (!sm_pInstance) sm_pInstance = this;
}

raaDE2::raaReferenced::raaReferencedManager::~raaReferencedManager()
{
	if(sm_pInstance==this)
	{
		removeTrash();
		sm_pInstance = 0;
	}
}
