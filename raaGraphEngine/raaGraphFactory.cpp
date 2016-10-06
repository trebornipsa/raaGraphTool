#include "raaGraph.h"
#include "raaGraphFactory.h"

raaGraphFactory::raaGraphFactory()
{
}

raaGraphFactory::~raaGraphFactory(void)
{
}

raaGraph* raaGraphFactory::create( std::string sName )
{
	return new raaGraph(sName);
}
