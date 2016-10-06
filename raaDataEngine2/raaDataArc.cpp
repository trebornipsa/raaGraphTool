
#include "raaDataNode.h"
#include "raaDataArc.h"

raaDE2::raaDataArc::raaDataArc(std::string sName) : raaDataObject(sName)
{
	setAttribute("spring_coef", 1.0f);
	setAttribute("ideal_length", 1.0f);
	useAttributeAsIdealLength("ideal_length");
	useAttributeAsSpringCoef("spring_coef");
}

raaDE2::raaDataArc::~raaDataArc()
{
}

void raaDE2::raaDataArc::aboutToDelete()
{
	for (raaDataNodeList::iterator it = m_lNodes.begin(); it != m_lNodes.end(); it++)
	{
		(*it)->m_lArcs.remove(this);
		(*it)->unref();
	}
}

void raaDE2::raaDataArc::activeChanged(std::string sName)
{
	if(isActive()&&!wasActive())
	{
		for (raaDataNodeList::iterator it = m_lNodes.begin(); it != m_lNodes.end(); it++) (*it)->refActivityCounter("raaDataArc");
	}
	else if (!isActive() && wasActive())
	{
		for (raaDataNodeList::iterator it = m_lNodes.begin(); it != m_lNodes.end(); it++) (*it)->unrefActivityCounter("raaDataArc");
	}
}

void raaDE2::raaDataArc::attributeChanged(std::string sName)
{
	if (sName == m_sIdealLengthAttribute) m_fIdealLength = m_mAttributes[m_sIdealLengthAttribute];
	if (sName == m_sSpringCoefAttribute) m_fSpringCoef = m_mAttributes[m_sSpringCoefAttribute];
}

bool raaDE2::raaDataArc::hasNode(raaDataNode* pNode)
{
	if (pNode && std::find(m_lNodes.begin(), m_lNodes.end(), pNode) != m_lNodes.end()) return true;
	return false;
}

const raaDE2::raaDataNodeList& raaDE2::raaDataArc::nodes()
{
	return m_lNodes;
}

void raaDE2::raaDataArc::setCentre(raaVector& v)
{
	m_vCentre = v;
}

const raaVector& raaDE2::raaDataArc::centre()
{
	return m_vCentre;
}

void raaDE2::raaDataArc::useAttributeAsIdealLength(std::string sName)
{
	if(sName.length() && m_mAttributes.find(sName)!=m_mAttributes.end())
	{
		m_sIdealLengthAttribute = sName;
		m_fIdealLength = m_mAttributes[m_sIdealLengthAttribute];
	}
}

void raaDE2::raaDataArc::setIdealLength(float fIdealLength)
{
	if (m_sIdealLengthAttribute.length()) setAttribute(m_sIdealLengthAttribute, fIdealLength);
	else m_fIdealLength = fIdealLength;
}

float raaDE2::raaDataArc::idealLength()
{
	return m_fIdealLength;
}

void raaDE2::raaDataArc::useAttributeAsSpringCoef(std::string sName)
{
	if (sName.length() && m_mAttributes.find(sName) != m_mAttributes.end())
	{
		m_sSpringCoefAttribute = sName;
		m_fSpringCoef = m_mAttributes[m_sSpringCoefAttribute];
	}
}

void raaDE2::raaDataArc::setSpringCoef(float fSpringCoef)
{
	if (m_sSpringCoefAttribute.length()) setAttribute(m_sSpringCoefAttribute, fSpringCoef);
	else m_fSpringCoef = fSpringCoef;
}

float raaDE2::raaDataArc::springCoef()
{
	return m_fSpringCoef;
}
