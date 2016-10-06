#include "raaUndirectedSolverFactory.h"

#include "raaGraphEngine.h"

unsigned int raaGraphEngine::sm_uiInstance=0;
raaGraphEngine* raaGraphEngine::sm_pInstance=0;


raaGraphEngine::raaGraphEngine(void)
{
	m_mGraphFactories["graph"]=new raaGraphFactory();	
	m_mEdgeFactories["edge"]=new raaEdgeFactory();	
	m_mNodeFactories["node"]=new raaNodeFactory();	
	m_mGraphSolverFactories["default"]=new raaGraphSolverFactory();	
	m_mGraphSolverFactories["undirected"]=new raaUndirectedSolverFactory();	

	if(!sm_pInstance) sm_pInstance=this;
}

raaGraphEngine::~raaGraphEngine(void)
{
	if(sm_pInstance==this) sm_pInstance=0;
}

raaGraphEngine* raaGraphEngine::instance()
{
	return sm_pInstance;
}

void raaGraphEngine::stop()
{
	if(sm_pInstance && !--sm_uiInstance) delete sm_pInstance;	
}

void raaGraphEngine::start()
{
	if(!sm_pInstance && !sm_uiInstance++) new raaGraphEngine();
}

raaGraph* raaGraphEngine::createGraph(std::string sType, std::string sName )
{
	raaGraph *pGraph=0;
	
	if(sName.length() && sType.length() && m_mGraphs.find(sName)==m_mGraphs.end())
	{
		if(m_mGraphFactories.find(sType)!=m_mGraphFactories.end()) pGraph=m_mGraphFactories[sType]->create(sName);
		else pGraph=m_mGraphFactories["graph"]->create(sName);

		m_mGraphs[sName]=pGraph;
	}

	return pGraph;
}

raaGraph* raaGraphEngine::getGraph( std::string sName )
{
	if(sName.length() && m_mGraphs.find(sName)!=m_mGraphs.end()) return m_mGraphs[sName];

	return 0;
}

void raaGraphEngine::removeGraph( raaGraph* pGraph )
{
}

void raaGraphEngine::registerNodeFactory( std::string sName, raaNodeFactory *pFactory )
{
	if(sName.length() && pFactory)
	{
		m_mNodeFactories[sName]=pFactory;
	}
}

void raaGraphEngine::registerEdgeFactory( std::string sName, raaEdgeFactory *pFactory )
{
	if(sName.length() && pFactory)
	{
		m_mEdgeFactories[sName]=pFactory;
	}
}

void raaGraphEngine::registerGraphFactory( std::string sName, raaGraphFactory *pFactory )
{
	if(sName.length() && pFactory)
	{
		m_mGraphFactories[sName]=pFactory;
	}
}

raaGraphSolver* raaGraphEngine::getSolver( std::string sType )
{
	raaGraphSolver *pSolver=0;

	if(sType.length())
	{
		if(m_mGraphSolverFactories.find(sType)!=m_mGraphSolverFactories.end()) pSolver=m_mGraphSolverFactories[sType]->create();
		else pSolver=m_mGraphSolverFactories["default"]->create();

	}

	return pSolver;
}

