#pragma once

#include <QtCore/QString>
#include <vector>
#include <map>

typedef std::vector<QString> raaRow;
typedef std::map<QString, raaRow> raaTable;
typedef std::map<int, QString> raaCode;
typedef std::map<QString, raaCode> raaCodes;
typedef std::vector<QString> raaQStringVector;

class raaDataDic
{
public:
	raaDataDic(QString sDicFile, QString sCodeFile);
	~raaDataDic();

	QString lookupAccro(QString s);
	QString lookupName(QString s);

	const raaTable& table();

protected:
	raaTable m_mTable;
	raaCodes m_mCodes;

};

