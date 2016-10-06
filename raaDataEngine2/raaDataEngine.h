#pragma once

#include <QtCore/QString>

#include "raaDataEngine2Defs.h"
#include "raaDataEngineTypes.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaDataEngine
	{
	public:
		static void start();
		static void stop();  
		static raaDataEngine* instance();

		raaDataModel* addModel(std::string sName);
		bool removeModel(std::string sName);
		const raaStringList& models();
		raaDataModel* model(std::string sName);

		raaDataModel* loadModel(std::string sName, std::string sPath);

		void addListener(raaDataEngineListener *pListener);
		void removeListener(raaDataEngineListener *pListener);

	protected:
		raaDataEngine();
		virtual ~raaDataEngine();
		raaDataModelMap m_mModels;
		raaStringList m_lModels;

		void loadDTWekaLayer(raaDataModel *pModel, raaDataPeriod *pPeriod, raaDataLayer *pLayer, std::string sFile);
		QString refineNameString(QString s);
		std::string nodeNamesToString(raaStringList& nn);
	private:
		float m_fMaxRandPos;

		static unsigned int sm_uiInstance;
		static raaDataEngine* sm_pInstance;
		raaDataEngineListenersList m_lListeners;
	};
}

