#include "raaDataNode.h"

raaDE2::raaDataNode::raaDataNode(std::string sName) : raaDataObject(sName)
{
	m_bPinned = false;

	m_mAttributes["size"] = 1.0f;
	m_mAttributes["mass"] = 1.0f;
	m_mAttributes["damping"] = 1.0f;

	useAttributeAsMass("mass");
	useAttributeAsDamping("damping");
	useAttributeAsSize("size");
}

void raaDE2::raaDataNode::setPosition(raaVector& vPos)
{
	m_vPosition = vPos;
}

void raaDE2::raaDataNode::addDisplacment(raaVector& vDisp)
{
	m_vPosition += vDisp;
}

const raaVector& raaDE2::raaDataNode::position()
{
	return m_vPosition;
}

void raaDE2::raaDataNode::setVelocity(raaVector& vVel)
{
	m_vVelocity = vVel;
}

const raaVector& raaDE2::raaDataNode::velocity()
{
	return m_vVelocity;
}

void raaDE2::raaDataNode::addForce(raaVector& vForce)
{
	m_vForce += vForce;
}

void raaDE2::raaDataNode::setForce(raaVector& vForce)
{
	m_vForce = vForce;
}

const raaVector& raaDE2::raaDataNode::force()
{
	return m_vForce;
}

void raaDE2::raaDataNode::zeroForce()
{
	m_vForce.set(0.0f, 0.0f, 0.0f);
}

void raaDE2::raaDataNode::setPinned(bool bPinned)
{
	m_bPinned = bPinned;
}

bool raaDE2::raaDataNode::pinned()
{
	return m_bPinned;
}

void raaDE2::raaDataNode::useAttributeAsMass(std::string sName)
{
	m_sMassAttribute = sName;
	if (sName.length() && m_mAttributes.find(sName) != m_mAttributes.end()) m_fMass = m_mAttributes[sName];
	else m_fMass = 1.0f;
}

void raaDE2::raaDataNode::useAttributeAsDamping(std::string sName)
{
	m_sDampingAttribute = sName;
	if (sName.length() && m_mAttributes.find(sName) != m_mAttributes.end()) m_fDamping = m_mAttributes[sName];
	else m_fDamping = 1.0f;
}

void raaDE2::raaDataNode::useAttributeAsSize(std::string sName)
{
	m_sSizeAttribute = sName;
	if (sName.length() && m_mAttributes.find(sName) != m_mAttributes.end()) m_fSize = m_mAttributes[sName];
	else m_fSize = 1.0f;
}

float raaDE2::raaDataNode::mass()
{
	return m_fMass;
}

float raaDE2::raaDataNode::damping()
{
	return m_fDamping;
}

float raaDE2::raaDataNode::size()
{
	return m_fSize;
}

void raaDE2::raaDataNode::setMass(float fMass)
{
	if (m_sMassAttribute.length()) setAttribute(m_sMassAttribute, fMass);
	else m_fMass = fMass;
}

void raaDE2::raaDataNode::setDamping(float fDamping)
{
	if (m_sDampingAttribute.length()) setAttribute(m_sDampingAttribute, fDamping);
	else m_fDamping = fDamping;
}

void raaDE2::raaDataNode::setSize(float fSize)
{
	if (m_sSizeAttribute.length()) setAttribute(m_sSizeAttribute, fSize);
	else m_fSize = fSize;
}

const raaDE2::raaStringList& raaDE2::raaDataNode::groups()
{
	return m_lGroups;
}

raaDE2::raaDataNode::~raaDataNode()
{
}

void raaDE2::raaDataNode::aboutToDelete()
{
}

void raaDE2::raaDataNode::activeChanged(std::string sName)
{
}

void raaDE2::raaDataNode::attributeChanged(std::string sName)
{
	if (sName == m_sMassAttribute) m_fMass = m_mAttributes[sName];
	if (sName == m_sSizeAttribute) m_fSize = m_mAttributes[sName];
	if (sName == m_sDampingAttribute) m_fDamping = m_mAttributes[sName];
}
