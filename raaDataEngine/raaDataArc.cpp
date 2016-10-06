#include "raaDataNode.h"
#include "raaDataArc.h"
#include <iostream>

bool raaDataArc::sm_bCenSqrForce = false;

raaDataArc::raaDataArc(std::string sName) : raaNode(sName), m_vVelocity(0.0f, 0.0f, 0.0f, 0.0f)
{
	m_fMass = 0.0f;
	m_fWeight = 1.0f;
	m_sName = sName;
	m_fIdealLength = 3.0f;
	m_bActive = true;
	m_uiActiveCount = 0;
	m_vColour.set(0.25, 0.7, 0.35, 0.4);
	m_fWeightMultiplier = 1.0f;
}

void raaDataArc::addNode(raaDataNode* pNode)
{
	if(pNode && std::find(m_lNodes.begin(), m_lNodes.end(), pNode)==m_lNodes.end())
	{
		m_lNodes.push_back(pNode);
		addChild(pNode);
		pNode->activityRef();
		m_fMass += pNode->mass();
//		updateCentre();  
	}
}

void raaDataArc::removeNode(raaDataNode* pNode)
{
	if (pNode && std::find(m_lNodes.begin(), m_lNodes.end(), pNode) != m_lNodes.end())
	{
		m_lNodes.erase(std::find(m_lNodes.begin(), m_lNodes.end(), pNode));
		pNode->activityUnref();
		removeChild(pNode);
		m_fMass -= pNode->mass();
		m_vVelocity.set(0.0f, 0.0f, 0.0f, 1.0f);
		updateCentre(0.03f, 0.97f);
	}
}

raaVector raaDataArc::centre()
{
	return m_vCentre;
}

void raaDataArc::setWeight(float fWeight)
{
	m_fWeight = fWeight;
}

float raaDataArc::weight()
{
	return m_fWeight;
}

void raaDataArc::setIdealLength(float fLength)
{
	m_fIdealLength = fLength;
}

float raaDataArc::idealLength()
{
	return m_fIdealLength;
}

const raaDataNodes& raaDataArc::nodes()
{
	return m_lNodes;
}

const float raaDataArc::mass()
{
	return m_fMass;
}

void raaDataArc::clearForce()
{
	m_vForce.set(0.0f, 0.0f, 0.0f, 0.0f);
}

void raaDataArc::addToForce(raaVector v)
{
	m_vForce += v;
}

float raaDataArc::applyForce(float fTime, float fDamping)
{
	raaVector vAcc, vDisp;
	if (m_bActive)
	{
		vAcc = (m_vForce / m_fMass)*m_fWeightMultiplier;
		vDisp = (m_vVelocity*fTime) + (vAcc*(0.5f*fTime*fTime));
		m_vCentre = m_vCentre + vDisp;
		m_vVelocity = vDisp / fTime;
		m_vVelocity *= fDamping;
	}

	return m_fMass*m_vVelocity.length();
}

void raaDataArc::refActiveCount()
{
	if(!m_uiActiveCount)
	{
		for (unsigned int i = 0; i < m_lNodes.size(); i++)
			m_lNodes[i]->activityRef();
	}

	m_uiActiveCount++;
	m_bActive = true;
//	std::cout << "\tArc active -> " << m_uiActiveCount << std::endl;

	dataChanged();
}

void raaDataArc::unrefActiveCount(bool bNoChange)
{
	if (!--m_uiActiveCount && !bNoChange)
	{
		for (unsigned int i = 0; i < m_lNodes.size(); i++) 
			m_lNodes[i]->activityUnref();
		m_bActive = false;
	}

//	std::cout << "\tArc active -> " << m_uiActiveCount << std::endl;
	dataChanged();
}

unsigned raaDataArc::activityCount()
{
	return m_uiActiveCount;
}

bool raaDataArc::active()
{
	return m_bActive;
}

const raaVector& raaDataArc::colour()
{
	return m_vColour;
}

void raaDataArc::setColour(raaVector& v)
{
	m_vColour = v;
}

void raaDataArc::useArcCenreSqrForce(bool bState)
{
	sm_bCenSqrForce = bState;
}

void raaDataArc::setWeightMultiplier(float fWeight)
{
	m_fWeightMultiplier = fWeight;
}

float raaDataArc::weightMultiplier()
{
	return m_fWeightMultiplier;
}

void raaDataArc::updateCentre(float fTime, float fDamping)
{
//	if (m_bActive)
	{
			if (m_lNodes.size())
			{
				m_vCentre.set(0.0f, 0.0f, 0.0f, 0.0f);

				for (raaDataNodes::iterator it = m_lNodes.begin(); it != m_lNodes.end(); it++) m_vCentre += (*it)->position();
				m_vCentre /= ((float)(m_lNodes.size()));

				if (m_bActive)
				{
					raaVector vForce;

					for (raaDataNodes::iterator it = m_lNodes.begin(); it != m_lNodes.end(); it++)
					{
						raaVector vDisp;

						vDisp = (*it)->position() - m_vCentre;
						float f = !vDisp;
						f -= (0.5f*m_fIdealLength);

						if (sm_bCenSqrForce)
						{
							f *= f;
							fDamping *= fDamping;
						}


						vForce += vDisp*(f*m_fWeightMultiplier);
					}
/*
					raaVector vDisp;
					vDisp = (vForce / m_fMass)*(0.03f*0.03f*0.5f);
					vDisp += m_vVelocity*0.03f;
					m_vCentre += (vDisp);
					m_vVelocity = (vDisp / 0.03f)*0.99f;
*/

					raaVector vDisp;
					//					vDisp = (vForce / m_fMass)*(0.03f*0.03f*0.5f);
					vDisp = vForce*(fTime*fTime*0.5f);
					vDisp += m_vVelocity*fTime;
					m_vCentre += (vDisp);
					m_vVelocity = (vDisp / fTime)*fDamping;

				}
			}
	}
}

bool raaDataArc::containsNode(raaDataNode* pNode)
{
	if (std::find(m_lNodes.begin(), m_lNodes.end(), pNode) != m_lNodes.end()) return true;
	return false;
}

raaDataArc::~raaDataArc()
{
	for (unsigned int i = 0; i < m_lNodes.size(); i++)
	{
		m_lNodes[i]->activityUnref();
	}
	m_lNodes.clear();
}
