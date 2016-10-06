#pragma once

#include <string>

#include <windows.h>

#include <raaUtilities/raaThreadLoop.h>

#include "raaDataEngineTypes.h"
#include "raaDataEngine2Defs.h"



namespace raaDE2
{
	class raaSolverInterface;

	class RAADATAENGINE2_DLL_DEF raaDataModel: public raaThreadLoop
	{
	public:
		raaDataModel(std::string sName);
		virtual ~raaDataModel();

		raaDataPeriod* getOrCreatePeriod(std::string sName);
		raaDataLayer* getOrCreateLayer(std::string sName, raaDataPeriod *pPeriod);
		raaDataArc* getOrCreateArc(std::string sName, raaDataLayer *pLayer);
		raaDataNode* getOrCreateNode(std::string sName);

		bool addNodeToArc(raaDataArc *pArc, raaDataNode *pNode);
		bool removeNodeFromArc(raaDataArc *pArc, raaDataNode *pNode);

		bool hasNode(raaDataNode *pNode);
		bool hasNode(std::string sName);
		bool hasArc(raaDataArc *pArc);

		float transitionTime();
		void setTransitionTime(float fTransTime);

		void setCurrentPeriod(raaDataPeriod *pPeriod);
		void setTransitionPeriod(raaDataPeriod *pPeriod);

		void tick(float fTime);

		void setDamping(float fDamping);
		float damping();

		const raaDataNodeList& nodes();
		const raaDataArcList& arcs();

		void addListener(raaDataModelListener *pListener);
		void removeListener(raaDataModelListener *pListener);

		void solve(bool bSolve);
		bool isSolving();

	protected:
		std::string m_sName;
		raaDataPeriodMap m_mPeriods;
		raaDataPeriodList m_lPeriods;
		raaDataLayerList m_lLayers;
		raaDataNodeList m_lNodes;
		raaDataNodeMap m_mNodes;
		raaDataArcList m_lArcs;
		raaDataNodeListMap m_lNodeGroups;
		float m_fTransitionTime;
		float m_fCurrentTransitionTime;
		float m_fCurrentTransitionalProportion;
		float m_fDamping;

		raaDataPeriod* m_pCurrentPeriod;
		raaDataPeriod* m_pTransitionalPeriod;
		raaDataModelListenersList m_lListeners;

		bool m_bSolving;

		raaSolverInterface *m_pSolver;

		unsigned int m_uiTimer;

		virtual void startLoop();
		virtual void loop();
		virtual void endLoop();

	};
}
