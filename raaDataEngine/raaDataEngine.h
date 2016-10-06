#pragma once

#include "raaDataEngineDefs.h"

#include <map>
#include <string>

class raaDataModel;
class raaDataSolver;
class raaDataCluster;

typedef std::map<std::string, raaDataModel*> raaDataModels;
typedef std::map<std::string, raaDataSolver*> raaDataSolvers;
typedef std::map<std::string, raaDataCluster*> raaDataClusterers;

class RAADATAENGINE_DLL_DEF raaDataEngine
{
public:
	static void start();
	static void end();
	static raaDataEngine* instance();

	bool addModel(std::string sName, bool bMakeCurrent=true);
	void makeModelCurrent(std::string sName);
	void removeModel(std::string sName);
	raaDataModel* currentModel();

	bool addSolver(std::string sName, raaDataSolver *pSolver, bool bMakeCurrent = true);
	void makeSolverCurrent(std::string sName);
	raaDataSolver* removeSolver(std::string sName);
	void solve(float fTime, float fDamping);

	bool addClusterer(std::string sName, raaDataCluster *pCluster, bool bMakeCurrent = true);
	void makeClusterCurrent(std::string sName);
	raaDataCluster* removeCluster(std::string sName);
	void cluster(float fEPS, float fMinSize);
	raaDataCluster* currentCluster();

protected:
	raaDataEngine();
	virtual ~raaDataEngine();

	static unsigned int sm_uiInstance;
	static  raaDataEngine *sm_pInstance;

	raaDataModels m_mModels;
	raaDataModel *m_pCurrentModel;

	raaDataSolvers m_mSolvers;
	raaDataSolver *m_pCurrentSolver;

	raaDataClusterers m_mClusterers;
	raaDataCluster *m_pCurrentCluster;
};

