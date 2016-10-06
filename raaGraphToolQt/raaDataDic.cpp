#include "stdafx.h"

#include <QtCore/QFile>
#include <QtCore/QRegularExpression>

#include "raaDataDic.h"
#include <iostream>


raaDataDic::raaDataDic(QString sDicFile, QString sCodeFile)
{
	QFile file(sDicFile);

	if(file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		while (!file.atEnd())
		{
			QString sLine = file.readLine(2048);
			QStringList ss = sLine.split(',');
			raaRow r;
			for (QStringList::iterator it = ss.begin(); it != ss.end(); it++) r.push_back((*it));

			if (r[0].isEmpty())
				m_mTable["headings"] = r;
			else
				m_mTable[r[0]] = r;
		}

		file.close();
	}

	QFile code(sCodeFile);

	if(code.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		while (!code.atEnd())
		{
			QString sLine = code.readLine(2048);

//			std::cout << sLine.toStdString() << std::endl;

			QStringList ss = sLine.split(QRegExp("([=\\->;:])"), QString::SplitBehavior::SkipEmptyParts);
			QStringList::iterator it = ss.begin();

			QString sName = (*it);
			it++;
//			std::cout << sName.toStdString() << std::endl;

			for(;it!=ss.end();it++)
			{
//				std::cout << (*it).toStdString() << std::endl;
				if ((*it).contains(QRegExp("([0-9])")))
				{
					int iCode = (*it).trimmed().toInt();
					it++;
					QString sCode = (*it);
//					std::cout << iCode << "   " << sCode.toStdString() << std::endl;
					if (sCode.length())
						m_mCodes[sName][iCode] = sCode;
				}
			}
		}
		code.close();
	}
}

raaDataDic::~raaDataDic()
{
}

QString raaDataDic::lookupAccro(QString s)
{
	QString sRet;
	sRet = s;
	QStringList ss = s.split(QRegularExpression("[<>=]"), QString::SplitBehavior::SkipEmptyParts);
	QStringList ssn = s.split(QRegularExpression("[^=<>]"), QString::SplitBehavior::SkipEmptyParts);

//	if (s.contains("sex"))
//		std::cout << s.toStdString() << std::endl;

	if (ss.size() > 1 && ssn.size())
	{
		QStringList::iterator it = ss.begin();
		QStringList::iterator nit = ssn.begin();

		QString sAccro = (*it);
		it++;
		QString sCode = (*it).trimmed();
		QString sOp = (*nit);

//		if (s.contains("sex"))
//			std::cout << "Code -> " << sAccro.toStdString() << "->" << sOp.toStdString() << "->" << sCode.toStdString() << std::endl;

		if (m_mCodes.find(sAccro) != m_mCodes.end()) sCode = m_mCodes[sAccro][sCode.toInt()];
		if (m_mTable.find(sAccro) != m_mTable.end()) sAccro = m_mTable[sAccro][1];
		std::cout << "\tCode -> " << sAccro.toStdString() << "->" << sOp.toStdString() << "->" << sCode.toStdString() << std::endl;

//		if (s.contains("sex"))
			sRet = QString("%1 %2 %3").arg(sAccro).arg(sOp).arg(sCode);
	}
	return sRet;
}

QString raaDataDic::lookupName(QString s)
{
	QString sRet = s;

	if(s.length()&&!s.contains("Result"))
	{
		QStringList ss = s.split(QRegularExpression("[<>=]"), QString::SplitBehavior::SkipEmptyParts);
		QStringList ssn = s.split(QRegularExpression("[^=<>]"), QString::SplitBehavior::SkipEmptyParts);

		QStringList::iterator ssit = ss.begin();
		QStringList::iterator ssnit = ssn.begin();

		QString sN = (*ssit);
		ssit++;
		QString sC = (*ssit);
		QString sO = (*ssnit);

		for(raaTable::iterator it=m_mTable.begin();it!=m_mTable.end();it++)
		{
			raaRow &row = it->second;

			for(int i=row.size()-1;i>1;i--)
			{
				if (sN == row[i])
				{
					sRet = QString("%0%1%2").arg(row[0]).arg(sO).arg(sC);
					return sRet;
				}
			}
		}
	}
	return s;
}

const raaTable& raaDataDic::table()
{
	return m_mTable;
}
