#include "raaDataModel.h"

#include "raaDefaultCluster.h"


void raaDefaultCluster::cluster(raaDataModel *pModel, const raaDataNodeMap& nodes, float fEPS, float fMinSize)
{
	if (pModel)
	{
		#pragma omp parallel
		for (raaDataNodeMap::const_iterator it = nodes.begin(); it != nodes.end(); it++) it->second->initCluster();

		pModel->clearClusterSet();

#pragma omp parallel
		for (raaDataNodeMap::const_iterator it = nodes.begin(); it != nodes.end(); it++)
		{
			raaDataNode *pN = it->second;

			if (!pN->clusterVisited())
			{
				pN->setClusterVisited();

				if (pN->isActive() && !pN->pinned())
				{
					raaCluster pts;
					clusterRegion(pN, nodes, pts, fEPS);

					if (pts.size() < fMinSize) pModel->addNoise(pN);
					else
					{
						pModel->addCluster(pts);
						pModel->addToCluster(pN);

						for (raaCluster::iterator it2 = pts.begin(); it2 != pts.end(); it2++)
						{
							raaDataNode *p = *it2;

							if (!p->clusterVisited())
							{
								p->setClusterVisited();
								raaCluster _pts;
								clusterRegion(p, nodes, _pts, fEPS);

								if (_pts.size() >= fMinSize) pts.splice(pts.end(), _pts);
							}

							if (!p->clustered())
							{
								pModel->addToCluster(p);
								p->setClustered();
							}
						}
						pModel->clusterUnique();
					}
				}
			}
		}
	}
}

void raaDefaultCluster::clusterRegion(raaDataNode* pNodeTarget, const raaDataNodeMap& nodes, raaCluster& cluster, float fEPS)
{
	#pragma omp parallel
	for (raaDataNodeMap::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		raaDataNode *pN = it->second;

		if (pN != pNodeTarget && pN->isActive() && !pN->pinned() && pN->position().distance(pNodeTarget->position()) < fEPS) cluster.push_back(pN);
	}
}

raaDefaultCluster::raaDefaultCluster()
{
}


raaDefaultCluster::~raaDefaultCluster()
{
}
