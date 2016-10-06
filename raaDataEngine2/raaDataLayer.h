#pragma once

#include "raaDataObject.h"
#include "raaDataEngineTypes.h"
#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaDataLayer: public raaDataObject
	{
		friend raaDataModel;
		friend raaDataPeriod;
	public:
		
		raaDataArc* getOrCreateArc(std::string sName);
		void removeArc(raaDataArc *pArc);
		bool hasArc(raaDataArc *pArc);

		const raaDataArcList& arcs();

	protected:
		raaDataArcList m_lArcs;
		raaDataArcMap m_mArcs;
		raaDataLayer(std::string sName);
		virtual ~raaDataLayer();

		virtual void aboutToDelete();
		virtual void activeChanged(std::string sName);
		virtual void attributeChanged(std::string sName);	
	};
}
