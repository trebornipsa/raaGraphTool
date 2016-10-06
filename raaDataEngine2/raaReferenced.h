#pragma once

#include "raaDataEngineTypes.h"
#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaReferenced
	{
	public:
		raaReferenced(bool bDeletable=true);

		void ref();
		void unref(bool bDelete = true);
		unsigned int refCount();

		raaDataUID& uid();

	protected:
		virtual void aboutToDelete() = 0;
		virtual ~raaReferenced();

		class RAADATAENGINE2_DLL_DEF raaReferencedManager
		{
		public:
			static void start();
			static void stop();
			static raaReferencedManager* instance();

			void add(raaReferenced *pRef);
			void toGarbage(raaReferenced *pRef);
			void removeTrash();

			raaReferenced* find(raaDataUID uid);

		protected:
			static unsigned int sm_uiInstance;
			static raaReferencedManager* sm_pInstance;
			raaUIDReferencedMap m_mObjects;
			raaReferencedList m_lGarbage;

			raaReferencedManager();
			virtual ~raaReferencedManager();

		};

	private:
		unsigned int m_uiRefCount;

		bool m_bDeletable;

		raaDataUID m_uid;

	};


}
