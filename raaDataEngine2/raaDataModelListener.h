#pragma once

#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class raaDataNode;
	class raaDataArc;
	class raaDataModel;

	class RAADATAENGINE2_DLL_DEF raaDataModelListener
	{
	public:
		raaDataModelListener();
		virtual ~raaDataModelListener();

		virtual void updatedNode(raaDataNode *pNode)=0;
		virtual void newNode(raaDataNode *pNode) = 0;

		virtual void updatedNodes(raaDataModel *pModel) = 0;

		virtual void newArc(raaDataArc *pArc)=0;
		virtual void updatedArc(raaDataArc *pArc)=0;
	};
}