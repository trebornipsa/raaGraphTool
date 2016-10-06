#pragma once

#include <string>
#include <map>

#include "raaNode.h"
#include "raaEdge.h"

#include "raaGraphEngineDefs.h"

class raaGraphEngine;
class raaGraphFactory;
class raaGraphSolver;

class RAAGRAPHENGINE_DLL_DEF raaGraph
{
	friend raaGraphEngine;
	friend raaGraphFactory;
public:

	virtual raaNode* addNode(std::string sID, std::string sType, std::string sName);
	raaNode* getNode(std::string sID);
	bool nodeIsMember(raaNode *pNode);

	virtual raaEdge* addEdge(std::string sType, raaNode *pStart, raaNode *pEnd, float fWeight=1.0f);

	void setIdealEdgeLength(float flen=1.0f);
	float idealEdgeLength();

	void setSolver(std::string sType);
	void setSolver(raaGraphSolver *pSolver);
	virtual bool solve(unsigned int uiNumIterations);

	bool hasSolution();

	const raaNodes& nodes();
	const raaEdges& edges();

	virtual void updateNode(raaNode *pNode, std::string sUpdate);
	virtual void updateEdge(raaEdge *pEdge, std::string sUpdate);

	void normaliseEdgeWeights();

	virtual float energy();

	void graphToArrays();


protected:

	raaGraph(std::string sName="");
	virtual ~raaGraph(void);

	std::string m_sName;

	raaNodes m_mNodes;
	raaEdges m_mEdges;

	float m_fIdealEdgeLen;

	raaGraphSolver *m_pSolver;

	bool m_bUnsolved;

	

};

typedef std::map<std::string, raaGraph*>raaGraphs;