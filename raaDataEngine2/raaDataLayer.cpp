#include "raaDataArc.h"
#include "raaDataLayer.h"

raaDE2::raaDataLayer::raaDataLayer(std::string sName) : raaDataObject(sName)
{
	refActivityCounter("layer");
}

raaDE2::raaDataLayer::~raaDataLayer()
{
}


raaDE2::raaDataArc* raaDE2::raaDataLayer::getOrCreateArc(std::string sName)
{
	raaDataArc *pArc = 0;

	if (sName.length())
	{
		if (m_mArcs.find(sName) == m_mArcs.end())
		{
			pArc = new raaDataArc(sName);
			pArc->ref();
			m_lArcs.push_back(pArc);
			m_mArcs[sName] = pArc;
		}
		else
			pArc = m_mArcs[sName];
	}

	return pArc;
}

void raaDE2::raaDataLayer::removeArc(raaDataArc* pArc)
{
	if (pArc && std::find(m_lArcs.begin(), m_lArcs.end(), pArc) != m_lArcs.end())
	{
		m_lArcs.remove(pArc);
		pArc->unref();
		if (isActive()) pArc->unrefActivityCounter("layer");
	}
}

bool raaDE2::raaDataLayer::hasArc(raaDataArc* pArc)
{
	if (pArc && std::find(m_lArcs.begin(), m_lArcs.end(), pArc) != m_lArcs.end()) return true;
	return false;
}

const raaDE2::raaDataArcList& raaDE2::raaDataLayer::arcs()
{
	return m_lArcs;
}

void raaDE2::raaDataLayer::aboutToDelete()
{
	for (raaDataArcList::iterator it = m_lArcs.begin(); it != m_lArcs.end();it++)
	{
		raaDataArc *pArc = (*it);
		if (isActive()) pArc->unrefActivityCounter("layer");
		pArc->unref();
	}
}

void raaDE2::raaDataLayer::activeChanged(std::string sName)
{
	if (isActive()) 	for (raaDataArcList::iterator it = m_lArcs.begin(); it != m_lArcs.end(); it++) (*it)->refActivityCounter("layer");
	else for (raaDataArcList::iterator it = m_lArcs.begin(); it != m_lArcs.end(); it++) (*it)->unrefActivityCounter("layer");
}

void raaDE2::raaDataLayer::attributeChanged(std::string sName)
{
}
