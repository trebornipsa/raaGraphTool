#pragma once

#include <vector>

#include <raaUtilities/raaNode.h>
#include <raaUtilities/raaVector.h>

#include "raaDataEngineDefs.h"

class raaDataNode;
class raaDataArc;

typedef std::vector<raaDataNode*>raaDataNodes;
typedef std::vector<raaDataArc*> raaDataArcs;

class RAADATAENGINE_DLL_DEF raaDataArc : public raaNode
{
public:
	raaDataArc(std::string sName);

	virtual void addNode(raaDataNode *pNode);
	virtual void removeNode(raaDataNode *pNode);

	raaVector centre();
	void updateCentre(float fTime, float fDamping);

	bool containsNode(raaDataNode *pNode);

	void setWeight(float fWeight);
	float weight();

	void setIdealLength(float fLength);
	float idealLength();

	const raaDataNodes& nodes();

	const float mass();

	void clearForce();
	void addToForce(raaVector v);
	float applyForce(float fTime, float fDamping);

	void refActiveCount();
	void unrefActiveCount(bool bNoChange=false);
	unsigned int activityCount();
	bool active();

	const raaVector& colour();
	void setColour(raaVector &v);

	static void useArcCenreSqrForce(bool bState);

	void setWeightMultiplier(float fWeight);
	float weightMultiplier();

protected:
	unsigned int m_uiActiveCount;

	static bool sm_bCenSqrForce;

	float m_fMass;
	raaVector m_vForce;
	raaVector m_vVelocity;

	virtual ~raaDataArc();

	raaDataNodes m_lNodes;

	float m_fWeight;
	float m_fIdealLength;
	raaVector m_vCentre;

	bool m_bActive;

	raaVector m_vColour;

	float m_fWeightMultiplier;

};

