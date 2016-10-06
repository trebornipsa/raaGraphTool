#include "raaNode.h"
#include "raaNodeFactory.h"

raaNodeFactory::raaNodeFactory(void)
{
}


raaNodeFactory::~raaNodeFactory(void)
{
}

raaNode* raaNodeFactory::create(std::string sID, std::string sName, raaGraph *pGraph)
{
	return new raaNode(sID, sName, pGraph);	
}
