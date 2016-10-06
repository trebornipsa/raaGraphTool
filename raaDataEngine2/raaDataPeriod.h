#pragma once

#include "raaDataObject.h"
#include "raaDataEngineTypes.h"
#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class raaDataModel;

	class RAADATAENGINE2_DLL_DEF raaDataPeriod: public raaDataObject
	{
		friend raaDataModel;
	public:
		void setTransitionState(unsigned int uiState, float fTransitionTime = 0.0f);
		float transitionTime();
		unsigned int transitionState();

		void addToGroup(std::string sGroup, raaDataNode *pNode);
		void removeFromGroup(std::string sGroup, raaDataNode *pNode);
		const raaDataNodeList& group(std::string sGroup);
		bool hasGroup(std::string sGroup);

		void normaliseArcs();

	protected:
		std::string m_sName;
		raaDataLayerList m_lLayers;
		raaDataLayerMap m_mLayers;

		unsigned int m_uiState;
		float m_fTransitionTime;

		raaDataPeriod(std::string sName);
		~raaDataPeriod();
		raaDataLayer* getOrCreateLayer(std::string sName);
		bool removeLayer(raaDataLayer *pLayer);
		virtual void aboutToDelete();
		virtual void activeChanged(std::string sName);
		virtual void attributeChanged(std::string sName);

		raaDataNodeListMap m_mGroups;
		raaDataNodeList m_lEmptyList;
	};
}
