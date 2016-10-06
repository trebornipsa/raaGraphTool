#pragma once

#include <map>
#include <string>

#include "raaNodeFactory.h"
#include "raaEdgeFactory.h"
#include "raaGraphFactory.h"
#include "raaGraphSolverFactory.h"

#include "raaGraph.h"

#include "raaGraphEngineDefs.h"

class RAAGRAPHENGINE_DLL_DEF raaGraphEngine
{
	friend raaGraph;
public:
	static void start();
	static void stop();
	static raaGraphEngine* instance();

	raaGraph* createGraph(std::string sType, std::string sName);
	raaGraph* getGraph(std::string sName);
	void removeGraph(raaGraph* pGraph);

	raaGraphSolver* getSolver(std::string sType);

	void registerNodeFactory(std::string sName, raaNodeFactory *pFactory);
	void registerEdgeFactory(std::string sName, raaEdgeFactory *pFactory);
	void registerGraphFactory(std::string sName, raaGraphFactory *pFactory);

protected:
	static unsigned int sm_uiInstance;
	static raaGraphEngine* sm_pInstance;

	raaGraphEngine(void);
	virtual ~raaGraphEngine(void);

	raaNodeFactories m_mNodeFactories;
	raaEdgeFactories m_mEdgeFactories;
	raaGraphFactories m_mGraphFactories;
	raaGraphSolverFactories m_mGraphSolverFactories;

	raaGraphs m_mGraphs;
};

