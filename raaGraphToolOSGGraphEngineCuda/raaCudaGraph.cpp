#include "stdafx.h"
#include "raaCudaGraph.h"


raaCudaGraph::raaCudaGraph(void)
{
	m_bNodesChanged=false;
	m_bArcsChanged=false;

	m_pfPositions=0;
	m_pfVelocities=0;
	m_pfMasses=0;
	m_pfStates=0;
	m_pfNodeAcc=0;

	m_piArcs=0;
	m_pfSpringCoef=0;
	m_pfDampCoef=0;
	m_pfSpringLength=0;
	m_pfSpringForce=0;
	m_pfSpringForceVector=0;

	m_uiNumArcs=0;
	m_uiNumNodes=0;
}

raaCudaGraph::~raaCudaGraph(void)
{
	clear();
}

void raaCudaGraph::clear()
{
	clearNodes();
	clearArcs();
}

unsigned int raaCudaGraph::addNode( float fX, float fY, float fZ, float fVX, float fVY, float fVZ, float fMass, float fState )
{
	m_lPositions.push_back(fX);
	m_lPositions.push_back(fY);
	m_lPositions.push_back(fZ);

	m_lVelocities.push_back(fVX);
	m_lVelocities.push_back(fVY);
	m_lVelocities.push_back(fVZ);

	m_lMasses.push_back(fMass);

	m_lStates.push_back(fState);

	m_bNodesChanged=true;
	return ((unsigned int)m_lMasses.size())-1;
}

unsigned int raaCudaGraph::addArc( unsigned int iNode0, unsigned int iNode1, float fLength, float fSpringCoef, float fDampCoef )
{
	m_lArcs.push_back(iNode0);
	m_lArcs.push_back(iNode1);
	
	m_lSpringLength.push_back(fLength);

	m_lSpringCoef.push_back(fSpringCoef);
	m_lDampCoef.push_back(fDampCoef);

	m_bArcsChanged=true;
	return ((unsigned int)m_lSpringLength.size())-1;
}

void raaCudaGraph::resolveNodes()
{
	if(m_bNodesChanged)
	{
		if(m_pfPositions) delete [] m_pfPositions;
		if(m_pfVelocities) delete [] m_pfVelocities;
		if(m_pfMasses) delete [] m_pfMasses;
		if(m_pfStates) delete [] m_pfStates;
		if(m_pfNodeAcc) delete [] m_pfNodeAcc; 

		m_pfPositions=new float[m_lPositions.size()];
		m_pfVelocities=new float[m_lVelocities.size()];
		m_pfMasses=new float[m_lMasses.size()];
		m_pfStates=new float[m_lStates.size()];
		m_pfNodeAcc=new float[m_lPositions.size()];

		floats::iterator pit=m_lPositions.begin();
		floats::iterator vit=m_lVelocities.begin();

		for(unsigned int i=0;pit!=m_lPositions.end();pit++, vit++, i++)
		{
			m_pfPositions[i]=*pit;
			m_pfVelocities[i]=*vit;
		}

		floats::iterator mit=m_lMasses.begin();
		floats::iterator sit=m_lStates.begin();

		for(unsigned int i=0;mit!=m_lMasses.end();mit++, sit++, i++)
		{
			m_pfMasses[i]=*mit;
			m_pfStates[i]=*sit;
		}

		m_uiNumNodes=((unsigned int)m_lMasses.size());

		m_bNodesChanged=false;
	}
}

void raaCudaGraph::resolveArcs()
{
	if(m_bArcsChanged)
	{
		if(m_piArcs) delete [] m_piArcs;
		if(m_pfSpringCoef) delete [] m_pfSpringCoef;
		if(m_pfDampCoef) delete [] m_pfDampCoef;
		if(m_pfSpringLength) delete [] m_pfSpringLength;
		if(m_pfSpringLength) delete [] m_pfSpringForce;

		m_piArcs=new unsigned int[m_lArcs.size()];
		m_pfSpringCoef=new float[m_lSpringCoef.size()];
		m_pfDampCoef=new float[m_lDampCoef.size()];
		m_pfSpringLength=new float[m_lSpringLength.size()];
		m_pfSpringForce=new float[m_lSpringLength.size()];
		m_pfSpringForceVector=new float[3*m_lSpringLength.size()];

		uints::iterator ait=m_lArcs.begin();
		for(unsigned int i=0;ait!=m_lArcs.end();ait++, i++) m_piArcs[i]=*ait;

		floats::iterator scit=m_lSpringCoef.begin();
		floats::iterator dcit=m_lDampCoef.begin();
		floats::iterator slit=m_lSpringLength.begin();

		for(unsigned int i=0;scit!=m_lSpringCoef.end();i++, scit++, dcit++, slit++)
		{
			m_pfSpringCoef[i]=*scit;
			m_pfDampCoef[i]=*dcit;
			m_pfSpringLength[i]=*slit;
		}

		m_uiNumArcs=((unsigned int)m_lSpringCoef.size());
		m_bArcsChanged=false;
	}
}

void raaCudaGraph::clearNodes()
{
	m_lPositions.clear();
	m_lVelocities.clear();
	m_lMasses.clear();
	m_lStates.clear();

	if(m_pfPositions) delete [] m_pfPositions;
	if(m_pfVelocities) delete [] m_pfVelocities;
	if(m_pfMasses) delete [] m_pfMasses;
	if(m_pfStates) delete [] m_pfStates;
	if(m_pfNodeAcc) delete [] m_pfNodeAcc;

	m_pfPositions=0;
	m_pfVelocities=0;
	m_pfMasses=0;
	m_pfStates=0;
	m_pfNodeAcc=0;

	m_uiNumNodes=0;

	m_bNodesChanged=true;
}

void raaCudaGraph::clearArcs()
{
	m_lArcs.clear();
	m_lSpringCoef.clear();
	m_lDampCoef.clear();
	m_lSpringLength.clear();

	if(m_piArcs) delete [] m_piArcs;
	if(m_pfSpringCoef) delete [] m_pfSpringCoef;
	if(m_pfDampCoef) delete [] m_pfDampCoef;
	if(m_pfSpringLength) delete [] m_pfSpringLength;
	if(m_pfSpringForce) delete [] m_pfSpringForce;
	if(m_pfSpringForceVector) delete [] m_pfSpringForceVector;

	m_piArcs=0;
	m_pfSpringCoef=0;
	m_pfDampCoef=0;
	m_pfSpringLength=0;
	m_pfSpringForce=0;
	m_pfSpringForceVector=0;

	m_uiNumArcs=0;

	m_bArcsChanged=true;
}

void raaCudaGraph::resolve()
{
	resolveNodes();
	resolveArcs();
	normaliseWeights();
}

void raaCudaGraph::solve( float fTime )
{
	if(m_pfPositions && m_piArcs)
	{
		// calc forces		
		for(unsigned int i=0;i<m_uiNumNodes*3;i++) m_pfNodeAcc[i]=0.0f;

		for(unsigned int i=0;i<m_uiNumArcs;i++)
		{
			m_pfSpringForce[i]=calcNodeSepperation(m_piArcs[i*2], m_piArcs[i*2+1]);
			m_pfSpringForce[i]=calcSpringForce(i);
			calcNodeAcc(i);	
		}

		for(unsigned int i=0;i<m_uiNumNodes;i++) calcNodePosition(i, fTime);
	}
}

float raaCudaGraph::calcNodeSepperation( unsigned int i0, unsigned int i1 )
{
	return sqrtf(powf(m_pfPositions[i1*3]-m_pfPositions[i0*3], 2.0)+powf(m_pfPositions[i1*3+1]-m_pfPositions[i0*3+1], 2.0)+powf(m_pfPositions[i1*3+2]-m_pfPositions[i0*3+2], 2.0));	
}

float raaCudaGraph::calcSpringForce( unsigned int iArc )
{
	float afRelV[3];

	afRelV[0]=(m_pfVelocities[m_piArcs[iArc*2+1]*3]-m_pfVelocities[m_piArcs[iArc*2]*3])*m_pfDampCoef[iArc];
	afRelV[1]=(m_pfVelocities[m_piArcs[iArc*2+1]*3+1]-m_pfVelocities[m_piArcs[iArc*2]*3+1])*m_pfDampCoef[iArc];
	afRelV[2]=(m_pfVelocities[m_piArcs[iArc*2+1]*3+2]-m_pfVelocities[m_piArcs[iArc*2]*3+2])*m_pfDampCoef[iArc];

	float fForce=((m_pfSpringLength[iArc]-m_pfSpringForce[iArc])*m_pfSpringCoef[iArc]);

	m_pfSpringForceVector[iArc*3]=m_pfPositions[m_piArcs[iArc*2+1]*3]-m_pfPositions[m_piArcs[iArc*2]*3];
	m_pfSpringForceVector[iArc*3+1]=m_pfPositions[m_piArcs[iArc*2+1]*3+1]-m_pfPositions[m_piArcs[iArc*2]*3+1];
	m_pfSpringForceVector[iArc*3+2]=m_pfPositions[m_piArcs[iArc*2+1]*3+2]-m_pfPositions[m_piArcs[iArc*2]*3+2];

	float fLen=sqrtf(powf(m_pfSpringForceVector[iArc*3], 2.0)+powf(m_pfSpringForceVector[iArc*3]+1, 2.0)+powf(m_pfSpringForceVector[iArc*3+2], 2.0));	

	m_pfSpringForceVector[iArc*3]=((m_pfSpringForceVector[iArc*3]/fLen)*fForce)-afRelV[0];
	m_pfSpringForceVector[iArc*3+1]=((m_pfSpringForceVector[iArc*3+1]/fLen)*fForce)-afRelV[1];
	m_pfSpringForceVector[iArc*3+2]=((m_pfSpringForceVector[iArc*3+2]/fLen)*fForce)-afRelV[2];

	return fForce;
}

void raaCudaGraph::calcNodeAcc( unsigned int iArc )
{
	m_pfNodeAcc[m_piArcs[iArc*2]*3]-=(m_pfSpringForceVector[iArc*3]/m_pfMasses[m_piArcs[iArc*2]]);
	m_pfNodeAcc[m_piArcs[iArc*2]*3+1]-=(m_pfSpringForceVector[iArc*3+1]/m_pfMasses[m_piArcs[iArc*2]]);
	m_pfNodeAcc[m_piArcs[iArc*2]*3+2]-=(m_pfSpringForceVector[iArc*3+2]/m_pfMasses[m_piArcs[iArc*2]]);

	m_pfNodeAcc[m_piArcs[iArc*2+1]*3]+=(m_pfSpringForceVector[iArc*3]/m_pfMasses[m_piArcs[iArc*2+1]]);
	m_pfNodeAcc[m_piArcs[iArc*2+1]*3+1]+=(m_pfSpringForceVector[iArc*3+1]/m_pfMasses[m_piArcs[iArc*2+1]]);
	m_pfNodeAcc[m_piArcs[iArc*2+1]*3+2]+=(m_pfSpringForceVector[iArc*3+2]/m_pfMasses[m_piArcs[iArc*2+1]]);
}

void raaCudaGraph::calcNodePosition( int unsigned iNode, float fTime)
{

	m_pfPositions[iNode*3]+=m_pfVelocities[iNode*3]=(m_pfVelocities[iNode*3]*fTime)+0.5f*m_pfNodeAcc[iNode*3]*powf(fTime, 2.0f);
	m_pfPositions[iNode*3+1]+=m_pfVelocities[iNode*3+1]=(m_pfVelocities[iNode*3+1]*fTime)+0.5f*m_pfNodeAcc[iNode*3+1]*powf(fTime, 2.0f);
	m_pfPositions[iNode*3+2]+=m_pfVelocities[iNode*3+2]=(m_pfVelocities[iNode*3+2]*fTime)+0.5f*m_pfNodeAcc[iNode*3+2]*powf(fTime, 2.0f);

	m_pfVelocities[iNode*3]/=fTime;
	m_pfVelocities[iNode*3+1]/=fTime;
	m_pfVelocities[iNode*3+2]/=fTime;



}

float* raaCudaGraph::vertexArray() const
{
	return m_pfPositions;
}

unsigned int * raaCudaGraph::indexArray() const
{
	return m_piArcs;
}

unsigned int raaCudaGraph::numNodes() const
{
	return m_uiNumNodes;
}

unsigned int raaCudaGraph::numArcs() const
{
	return m_uiNumArcs;
}

void raaCudaGraph::normaliseWeights()
{
	float fMax=m_pfSpringCoef[0];
	float fMin=m_pfSpringCoef[0];

	for(unsigned int i=1;i<m_uiNumArcs;i++)
	{
		fMax=(m_pfSpringCoef[i]>fMax)?m_pfSpringCoef[i]:fMax;
		fMin=(m_pfSpringCoef[i]<fMin)?m_pfSpringCoef[i]:fMin;
	}

	float fRange=fMax-fMin;

	for(unsigned int i=0;i<m_uiNumArcs;i++)
		m_pfSpringCoef[i]=(m_pfSpringCoef[i]-fMin)/fRange;
}
