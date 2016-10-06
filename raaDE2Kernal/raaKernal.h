#pragma once
#include <iostream>

#include <raaNetwork/raaTcpMsg.h>

#include "raaDE2KernalTypes.h"
#include "raaDE2KernalDefs.h"
namespace raaDE2Kernal
{
	class RAADE2KERNAL_DLL_DEF raaKernal
	{
		public:
			raaKernal();
			virtual ~raaKernal();
/*
			static QByteArray& pack(unsigned short usMajorType, unsigned short usMinorType, QStringList& sl, QByteArray& data);
			static QStringList& unpack(unsigned short& usMajorType, unsigned short& usMinorType, QByteArray& data, QStringList& sl);
			static void printMsg(QByteArray& data);
*/
			static QString msgMajorTypeToString(unsigned short usMsg);
			static QString msgMinorTypeToString(unsigned short usMajorType, unsigned short usMinorType);
			static QString sepperator();



	};
}
