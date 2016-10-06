#include "raaKernal.h"



raaDE2Kernal::raaKernal::raaKernal()
{
}


raaDE2Kernal::raaKernal::~raaKernal()
{
}
/*
QByteArray& raaDE2Kernal::raaKernal::pack(unsigned short usMajorType, unsigned short usMinorType, QStringList& sl, QByteArray& data)
{
	data.clear();
	data.append((const char*)&usMajorType, sizeof(unsigned short));
	data.append((const char*)&usMinorType, sizeof(unsigned short));

	for (QStringList::iterator it = sl.begin(); it != sl.end(); it++)
	{
		data.append(it->toUtf8());
		QStringList::iterator it2 = it;
		it2++;
		if (it2 != sl.end()) data.append(sepperator().toUtf8());
	}
	return data;
}

QStringList& raaDE2Kernal::raaKernal::unpack(unsigned short& usMajorType, unsigned short& usMinorType, QByteArray& data, QStringList& sl)
{
	sl.clear();

	usMajorType = (unsigned short)(*(data.data()));
	usMinorType = (unsigned short)(*(data.data() + sizeof(unsigned short)));

	QString s(data.mid(sizeof(unsigned short) << 1));
	sl = s.split(sepperator(), QString::SkipEmptyParts);

	return sl;
}


void raaDE2Kernal::raaKernal::printMsg(QByteArray& data)
{
	unsigned short usMajor, usMinor;
	QStringList sl;
	sl = unpack(usMajor, usMinor, data, sl);

	std::cout << "DE2 Msg ->" << msgMajorTypeToString(usMajor).toStdString() << "("<< usMajor << ")::" << msgMinorTypeToString(usMajor, usMinor).toStdString() << "(" << usMinor << ") -> " << sl.length() << std::endl;

	unsigned int uiCount = 0;
	for (QStringList::iterator it = sl.begin(); it != sl.end(); it++)
		std::cout << "\t" << uiCount++ << " <" << it->toStdString() << ">" << std::endl;
}
*/

QString raaDE2Kernal::raaKernal::msgMajorTypeToString(unsigned short usMsg)
{
	switch (usMsg)
	{
	case csm_usDE2Engine:
		return QString("DE2Engine");
	case csm_usDE2Model:
		return QString("DE2Model");
	case csm_usDE2Period:
		return QString("DE2Period");
	case csm_usDE2Layer:
		return QString("DE2Layer");
	case csm_usDE2Arc:
		return QString("DE2Arc");
	case csm_usDE2Node:
		return QString("DE2Node");
	default:
		return QString("DE2UnknownMajorType");
	}
}

QString raaDE2Kernal::raaKernal::msgMinorTypeToString(unsigned short usMajorType, unsigned short usMinorType)
{
	switch (usMajorType)
	{
	case csm_usDE2Engine:
		switch (usMinorType)
		{
		case csm_usDE2LoadModel:
			return QString("DE2LoadModel");
		case csm_usDE2UnloadModel:
			return QString("DE2UnloadModel");
		default:
			return QString("DE2UnknownMinorType-Engine");
		}
		break;
	case csm_usDE2Model:
		switch (usMinorType)
		{
		case csm_usDE2StopSim:
			return QString("DE2StopSim");
		case csm_usDE2StartSim:
			return QString("DE2StartSim");
		case csm_usDE2Energy:
			return QString("DE2Energy");
		case csm_usDE2TimeStep:
			return QString("DE2TimeStep");
		case csm_usDE2PeriodTransitionOn:
			return QString("DE2PeriodTransitionOn");
		case csm_usDE2PeriodTransitionOff:
			return QString("DE2PeriodTransitionOff");
		case csm_usDE2PeriodTransitionStart:
			return QString("DE2PeriodTransitionStart");
		case csm_usDE2PeriodTransitionEnd:
			return QString("DE2PeriodTransitionEnd");
		case csm_usDE2ModelName:
			return QString("DE2ModelName");
		case csm_usDE2RequestModelData:
			return QString("DE2RequestModelData");
		default:
			return QString("DE2UnknownMinorType-Model");
		}
		break;
	case csm_usDE2Period:
		switch (usMinorType)
		{
		case csm_usDE2PeriodInactive:
			return QString("DE2PeriodInactive");
		case csm_usDE2PeriodActive:
			return QString("DE2PeriodActive");
		default:
			return QString("DE2UnknownMinorType-Model");
		}
		break;
	case csm_usDE2Layer:
		switch (usMinorType)
		{
		default:
			return QString("DE2UnknownMinorType-Layer");
		}
		break;
	case csm_usDE2Arc:
		switch (usMinorType)
		{
		default:
			return QString("DE2UnknownMinorType-Arc");
		}
		break;
	case csm_usDE2Node:
		switch (usMinorType)
		{
		default:
			return QString("DE2UnknownMinorType-Node");
		}
		break;
	default:
		return QString("DE2UnknownMinorType");
	}
}

QString raaDE2Kernal::raaKernal::sepperator()
{
	return QString(csm_Sepperator);
}
