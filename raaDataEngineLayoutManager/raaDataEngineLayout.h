#pragma once

#include <map>
#include <string>



#include <raaUtilities/raaVector.h>

#include <raaDataEngine/raaDataModel.h>

class raaVectorPair
{
public:
	raaVector m_vStart;
	raaVector m_vEnd;

	raaVectorPair() {};
	raaVectorPair(const raaVectorPair& vp) : m_vStart(vp.m_vStart), m_vEnd(vp.m_vEnd)
	{

	}
	

	virtual ~raaVectorPair() {};

};

#include "raaDataEngineLayoutManagerDefs.h"

class raaDataNode;

typedef std::map<raaDataNode*, raaVectorPair> raaLayoutSet;

class RAADATAENGINELAYOUTMANAGER_DLL_DEF raaDataEngineLayout
{
public:
	typedef std::map<std::string, std::string> raaParameters;

	raaDataEngineLayout();
	virtual ~raaDataEngineLayout();

	virtual void start(raaParameters& pParams) = 0;
	virtual void finish() = 0;
	virtual void apply(float fProg);

	void unpin(raaDataNodeGroup& rGroup);
	void unpin(const raaDataNodeGroup& rGroup);
	void pin(raaDataNodeGroup& rGroup);
	void pin(const raaDataNodeGroup& rGroup);
	void unpinAll();
protected:
	raaLayoutSet m_mLayoutSet;
};

