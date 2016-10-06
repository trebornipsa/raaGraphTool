#include "raaDataNode.h"
#include "raaDataArc.h"
#include "raaDataModel.h"
#include "raaDefaultSolver.h"

float raaDE2::raaDefaultSolver::solve(raaDataModel* pModel, float fTime)
{
	if(pModel)
	{
		clearForce(pModel->nodes());
		calcForce(pModel->arcs());
		return calcMotion(pModel->nodes(), fTime, pModel->damping());
	}
	return 0.0f;
}

raaDE2::raaDefaultSolver::raaDefaultSolver(std::string sName) : raaSolverInterface(sName)
{
}

raaDE2::raaDefaultSolver::~raaDefaultSolver()
{
}

void raaDE2::raaDefaultSolver::aboutToDelete()
{
}

void raaDE2::raaDefaultSolver::activeChanged(std::string sName)
{
}

void raaDE2::raaDefaultSolver::attributeChanged(std::string sName)
{
}

void raaDE2::raaDefaultSolver::clearForce(const raaDataNodeList& lNodes)
{
	for (raaDataNodeList::const_iterator nit = lNodes.begin(); nit != lNodes.end(); nit++) (*nit)->zeroForce();
}

void raaDE2::raaDefaultSolver::calcForce(const raaDataArcList& lArcs)
{

	for (raaDataArcList::const_iterator ait = lArcs.begin(); ait != lArcs.end();ait++)
	{
		raaDataArc *pArc = (*ait);
		if (pArc->isActive())
		{
			raaVector vCentre;
			for (raaDataNodeList::const_iterator nit = pArc->nodes().begin(); nit != pArc->nodes().end(); nit++) vCentre += (*nit)->position();
			vCentre /= (float)pArc->nodes().size();
			(*ait)->setCentre(vCentre);

			for (raaDataNodeList::const_iterator nit = pArc->nodes().begin(); nit != pArc->nodes().end(); nit++)
			{
				raaDataNode *pNode = (*nit);
				if (pNode->isActive())
				{
					raaVector v;
					v = vCentre - pNode->position();
					v *= ((!v - pArc->idealLength()) / pArc->idealLength())*pArc->springCoef();
					pNode->addForce(v);
				}
			}
		}
	}
}

float raaDE2::raaDefaultSolver::calcMotion(const raaDataNodeList& lNodes, float fTime, float fDamping)
{
	float fEnergy = 0.0f;
	for (raaDataNodeList::const_iterator nit = lNodes.begin(); nit != lNodes.end(); nit++)
	{
		raaDataNode *pNode = (*nit);
		if (pNode->isActive())
		{
			raaVector vAcc = pNode->force()/pNode->mass();
			raaVector vDisp = (pNode->velocity()*fTime) + (vAcc*0.5f*fTime*fTime);
			pNode->addDisplacment(vDisp);
			vDisp *= fDamping/fTime;
			pNode->setVelocity(vDisp);
			float fSpeed = !vDisp;
			fEnergy += 0.5f*pNode->mass()*fSpeed*fSpeed;
		}
	}
	return fEnergy;
}
