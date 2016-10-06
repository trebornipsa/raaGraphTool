#pragma once

#include <string>

#include "raaReferenced.h"
#include "raaDataEngineTypes.h"
#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaDataObject: public raaReferenced
	{
	public:
		raaDataObject(std::string sName);
		raaDataObject(std::string sName, bool bDeletable);
		raaDataObject(bool bDeletable);
		raaDataObject();
		virtual ~raaDataObject();

		std::string name();

		void refActivityCounter(std::string sName);
		unsigned int unrefActivityCounter(std::string sName);
		unsigned int activityCount(std::string sName);
		void setActivityCount(std::string sName, unsigned int uiCount);
		void setActivityCount(std::string sName, bool bState);
		bool isActive(std::string sName);
		bool isActive(raaStringList& lNames);
		bool isActive();
		bool wasActive();
		bool wasActive(std::string sName);
		bool wasActive(raaStringList& lNames);

		void setAttribute(std::string sName, float fAttrib);
		float attribute(std::string sName);

	protected:
		std::string m_sName;
		raaUIMap m_mActivityCounters;
		raaUIMap m_mLastActivityCounters;
		bool m_bIsActive;
		bool m_bWasActive;

		bool _isActive();
		bool _wasActive();

		void initCounter(std::string sName);

		raaFloatMap m_mAttributes;

		virtual void activeChanged(std::string sName) = 0;
		virtual void attributeChanged(std::string sName) = 0;
	};
}
