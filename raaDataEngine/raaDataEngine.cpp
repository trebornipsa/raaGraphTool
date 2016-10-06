#include "raaDataModel.h"
#include "raaDataSolver.h"
#include "raaDataCluster.h"

#include "raaDataEngine.h"

unsigned int raaDataEngine::sm_uiInstance=0;
raaDataEngine *raaDataEngine::sm_pInstance=0;

void raaDataEngine::start()
{
	if (!sm_pInstance && !sm_uiInstance++) new raaDataEngine();
}

void raaDataEngine::end()
{
	if (sm_pInstance && !--sm_uiInstance) delete sm_pInstance;
}

raaDataEngine* raaDataEngine::instance()
{
	return sm_pInstance;
}

bool raaDataEngine::addModel(std::string sName, bool bMakeCurrent)
{
	if(sName.length() && sName!="null" && m_mModels.find(sName)==m_mModels.end())
	{
		m_mModels[sName] = new raaDataModel(sName);

		if (bMakeCurrent) m_pCurrentModel = m_mModels[sName];
		return true;
	}

	return false;
}

void raaDataEngine::makeModelCurrent(std::string sName)
{
	if (m_mModels.find(sName) != m_mModels.end()) m_pCurrentModel = m_mModels[sName];
	else m_pCurrentModel = 0;
}

void raaDataEngine::removeModel(std::string sName)
{
	if (sName.length() && sName != "null" && m_mModels.find(sName) != m_mModels.end())
	{
		if (m_pCurrentModel == m_mModels[sName]) m_pCurrentModel = 0;

		delete m_mModels[sName];
		m_mModels.erase(sName);
	}
}

raaDataModel* raaDataEngine::currentModel()
{
	return m_pCurrentModel;
}

bool raaDataEngine::addSolver(std::string sName, raaDataSolver *pSolver, bool bMakeCurrent)
{
	if (sName.length() && sName != "null" && m_mSolvers.find(sName) == m_mSolvers.end())
	{
		m_mSolvers[sName] = pSolver;

		if (bMakeCurrent) m_pCurrentSolver = pSolver;
		return true;
	}

	return false;
}

void raaDataEngine::makeSolverCurrent(std::string sName)
{
	if (m_mSolvers.find(sName) != m_mSolvers.end()) m_pCurrentSolver = m_mSolvers[sName];
	else m_pCurrentSolver = 0;
}

raaDataSolver* raaDataEngine::removeSolver(std::string sName)
{
	if (sName.length() && sName != "null" && m_mSolvers.find(sName) != m_mSolvers.end())
	{
		if (m_pCurrentSolver == m_mSolvers[sName]) m_pCurrentSolver = 0;

		raaDataSolver *pSolver = m_mSolvers[sName];
		m_mSolvers.erase(sName);
		return pSolver;
	}

	return 0;
}

void raaDataEngine::solve(float fTime, float fDamping)
{
	if(m_pCurrentSolver && m_pCurrentModel)
	{
		m_pCurrentModel->setEnergy(m_pCurrentSolver->solve(m_pCurrentModel->nodes(), m_pCurrentModel->arcs(), fTime, fDamping));
		m_pCurrentModel->computeBound();
	}
}

bool raaDataEngine::addClusterer(std::string sName, raaDataCluster* pCluster, bool bMakeCurrent)
{
	if (sName.length() && sName != "null" && m_mClusterers.find(sName) == m_mClusterers.end())
	{
		m_mClusterers[sName] = pCluster;

		if (bMakeCurrent) m_pCurrentCluster = pCluster;
		return true;
	}

	return false;
}

void raaDataEngine::makeClusterCurrent(std::string sName)
{
	if (m_mClusterers.find(sName) != m_mClusterers.end()) m_pCurrentCluster = m_mClusterers[sName];
	else m_pCurrentCluster = 0;
}

raaDataCluster* raaDataEngine::removeCluster(std::string sName)
{
	if (sName.length() && sName != "null" && m_mClusterers.find(sName) != m_mClusterers.end())
	{
		if (m_pCurrentCluster == m_mClusterers[sName]) m_pCurrentCluster = 0;

		raaDataCluster *pCluster = m_mClusterers[sName];
		m_mClusterers.erase(sName);
		return pCluster;
	}

	return 0;
}

void raaDataEngine::cluster(float fEPS, float fMinSize)
{
	if (m_pCurrentCluster && m_pCurrentModel)
	{
		m_pCurrentCluster->cluster(m_pCurrentModel, m_pCurrentModel->nodes(), fEPS, fMinSize);
		m_pCurrentModel->computeBound();
	}
}

raaDataCluster* raaDataEngine::currentCluster()
{
	return m_pCurrentCluster;
}

raaDataEngine::raaDataEngine()
{
	m_pCurrentModel = 0;
	if (!sm_pInstance) sm_pInstance = this;
}

raaDataEngine::~raaDataEngine()
{
	if (sm_pInstance == this) sm_pInstance = 0;
}
