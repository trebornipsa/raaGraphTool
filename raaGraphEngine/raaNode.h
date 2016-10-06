#pragma once

#include <string>
#include <map>
#include <osg/Vec3f>

#include "raaGraphEngineDefs.h"

class raaNodeFactory;
class raaGraph;

class RAAGRAPHENGINE_DLL_DEF raaNode
{
	friend raaNodeFactory;
	friend raaGraph;
public:
	std::string getName();
	std::string getID();
	
	void setMass(float fMass=1.0f);
	float mass();
	
	virtual void setFixed(bool bFixed=false);
	bool fixed();

	virtual osg::Vec3f getPos();
	virtual void setPos(osg::Vec3f v);

	float distance(osg::Vec3f v);

	raaGraph* graph();

	void setRandPos(float fMin=-10.0f, float fMax=10.0f);

	void initClustering();
	bool m_bClustered;
	bool m_bClusterVisited;


protected:



	std::string m_sID;
	std::string m_sName;
	osg::Vec3f m_vPos;
	raaNode(std::string sID, std::string sName="", raaGraph *pGraph=0);
	virtual ~raaNode(void);
	
	float m_fMass;
	bool m_bFixed;
	raaGraph *m_pGraph;

	float randFloat(float fMin, float fMax);
	osg::Vec3f randVec(float fMin, float fMax);

	unsigned int m_uiIndex;
};

typedef std::map<std::string, raaNode*>raaNodes;