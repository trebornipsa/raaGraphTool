#pragma once
#include <ctime>
#include <string>

#include "raaDataEngine2Defs.h"
//#include "raaDataEngineTypes.h"

namespace raaDE2
{
	typedef struct raaUID {
		unsigned int m_uiInstance;
		unsigned int m_uiTime;
		unsigned int m_uiRand;
	} raaUID;

	class RAADATAENGINE2_DLL_DEF raaDataUID
	{
	public:
		raaDataUID();
		raaDataUID(const raaDataUID& uid);
		raaDataUID(const raaUID &uid);
		virtual ~raaDataUID();

		bool operator==(const raaDataUID& uid) const;
		bool operator<(const raaDataUID &uid) const; 
		const raaDataUID& operator=(const raaDataUID& uid);

		unsigned int instance();
		unsigned int time();
		unsigned int rand();
		std::string uid();
		std::string serialUid();



		void print();

		const char* serialize();
		void unserialize(const char *pcData);

	private:
		raaUID m_Data;

		std::string m_sUID;
		std::string m_sSerialUID;

		static unsigned int sm_uiInstance;
		static bool sm_bInit;

		static void init();
		static time_t sm_Timer;

	};
}
