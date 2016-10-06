#include <iostream>

#include "raaDataNode.h"
#include "raaDataArc.h"

#include "raaSpringSolver.h"

std::string sCheck = "relig3=98";

bool raaSpringSolver::sm_bUseSqrForce=false;

float raaSpringSolver::solve(const raaDataNodeMap& nodes, const raaDataArcMap& arcs, float fTime,float  fDamping)
{
	float fEnergy = 0.0f;
	#pragma omp parallel
	for (raaDataNodeMap::const_iterator it = nodes.begin(); it != nodes.end();it++) it->second->clearForce();

	float fMinF, fMinV, fMaxF, fMaxV;
	bool bFirst = true;

	#pragma omp parallel
	for (raaDataArcMap::const_iterator it = arcs.begin(); it != arcs.end();it++)
	{
		raaDataArc *pArc = it->second;
		if (pArc->active())
		{
			pArc->updateCentre(fTime, fDamping);
			float fLen = pArc->idealLength()*0.5f;

			for (raaDataNodes::const_iterator itN = pArc->nodes().begin(); itN != pArc->nodes().end(); itN++)
			{
				raaVector vDisp;
				vDisp = pArc->centre() - (*itN)->position();

				float fDisp = !vDisp;
				float fResLen = (fDisp - fLen);

//				if (sm_bUseSqrForce) fResLen *= fResLen;

				float fForce = fResLen*pArc->weight();

				if (sm_bUseSqrForce) fForce=powf(fForce, 3.0f);

				(*itN)->addForce(vDisp*fForce);
			}
		}
	}

	if (sm_bUseSqrForce)
	{
		fDamping *= fDamping;
	}
	#pragma omp parallel
	for (raaDataNodeMap::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		raaDataNode *pNode = it->second;

		float fForce = !(pNode->force());
		float fVel = !(pNode->velocity());


		fEnergy += it->second->applyForce(fTime, fDamping);

		fForce = !(pNode->force());
		fVel = !(pNode->velocity());

		if(bFirst)
		{
			fMinF = fMaxF = fForce;
			fMinV = fMaxV = fVel;
			bFirst = false;
		}
		else
		{
			fMinF = (fMinF > fForce) ? fForce : fMinF;
			fMaxF = (fMaxF < fForce) ? fForce : fMaxF;
			fMinV = (fMinV > fVel) ? fVel : fMinV;
			fMaxV = (fMaxV < fVel) ? fVel : fMaxV;
		}
	}
	return fEnergy;
}

raaSpringSolver::raaSpringSolver()
{
}


raaSpringSolver::~raaSpringSolver()
{

}

void raaSpringSolver::useSqrForce(bool bState)
{
	sm_bUseSqrForce = bState;
}

/*
float raaSpringSolver::solveArc(raaDataArc* pArc)
{
}
*/