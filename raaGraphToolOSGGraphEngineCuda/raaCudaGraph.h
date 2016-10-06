#pragma once

#include <map>
#include <list>
#include <vector>

typedef std::vector<float>floats;
typedef std::vector<unsigned int>uints;

class raaCudaGraph
{
public:
	raaCudaGraph(void);
	virtual ~raaCudaGraph(void);

	void clear();

	unsigned int addNode(float fX, float fY, float fZ, float fVX, float fVY, float fVZ, float fMass, float fState=1.0f);
	unsigned int addArc(unsigned int iNode0, unsigned int iNode1, float fLength, float fSpringCoef, float fDampCoef);

	void resolve();
	void resolveNodes();
	void resolveArcs();

	void solve(float fTime);

	float* vertexArray() const;
	unsigned int * indexArray() const;

	unsigned int numNodes() const;
	unsigned int numArcs() const;

	void normaliseWeights();

protected:
	void clearNodes();
	void clearArcs();

	float calcNodeSepperation(unsigned int i0, unsigned int i1);
	float calcSpringForce(unsigned int iArc);
	void calcNodeAcc(unsigned int iArc);
	void calcNodePosition(unsigned int iNode, float fTime);

	bool m_bNodesChanged;
	bool m_bArcsChanged;

	floats m_lPositions;
	floats m_lVelocities;
	floats m_lMasses;
	floats m_lStates;
	uints m_lArcs;
	floats m_lSpringCoef;
	floats m_lDampCoef;
	floats m_lSpringLength;

	float *m_pfPositions;
	float *m_pfVelocities;
	float *m_pfMasses;
	float *m_pfStates;
	float *m_pfNodeAcc;

	unsigned int *m_piArcs;
	float *m_pfSpringForce;
	float *m_pfSpringForceVector;
	float *m_pfSpringCoef;
	float *m_pfDampCoef;
	float *m_pfSpringLength;

	unsigned int m_uiNumArcs;
	unsigned int m_uiNumNodes;
};

