#include "stdafx.h"


#include "raaHistory.h"

unsigned int raaHistory::sm_uiInstance = 0;
raaHistory* raaHistory::sm_pInstance = 0;

void raaHistory::start(std::string sName)
{
	if (!sm_pInstance && !sm_uiInstance++) new raaHistory(sName);
}

void raaHistory::end()
{
	if (sm_pInstance && !--sm_pInstance) delete sm_pInstance;
}

raaHistory* raaHistory::instance()
{
	return sm_pInstance;
}

void raaHistory::setFrame(unsigned uiFrame)
{
	m_uiFrame = uiFrame;
//	QSqlQuery q;
//	q.exec(QString("insert into events values(%1, %2, %3, %4, %5)").arg(m_uiEventCount++).arg(raaHistory::csm_uiTypeFrame).arg(0).arg(0).arg(m_uiFrame));
}

void raaHistory::addFrame()
{
//	QSqlQuery q;
//	q.exec(QString("insert into events values(%1, %2, %3, %4, %5)").arg(m_uiEventCount++).arg(raaHistory::csm_uiTypeFrame).arg(0).arg(0).arg(++m_uiFrame));
}

void raaHistory::setNodePosition(unsigned uiUid, float fX, float fY, float fZ)
{
	if(m_bPrepareNodePos)
	{
		m_vlEventPrimKey << m_uiEventCount++;
		m_vlRef << m_uiPositionCount;
		m_vlPosPrimKey << m_uiPositionCount++;
		m_vlUid << uiUid;
		m_vlX << fX;
		m_vlY << fY;
		m_vlZ << fZ;
		m_vlFrame << m_uiFrame;
		m_vlType << raaHistory::csm_uiTypeNodePosition;
	}
	else
	{
//		QSqlQuery q;
//		q.exec(QString("insert into positions values(%1, %2, %3, %4)").arg(m_uiPositionCount++).arg(fX).arg(fY).arg(fZ));
//		q.exec(QString("insert into events values(%1, %2, %3, %4, %5)").arg(m_uiEventCount++).arg(raaHistory::csm_uiTypeNodePosition).arg(uiUid).arg(m_uiPositionCount).arg(m_uiFrame));
	}
}

void raaHistory::setEnableLayer(unsigned uiUid)
{
//	QSqlQuery q;
//	q.exec(QString("insert into events values(%1, %2, %3, %4, %5)").arg(m_uiEventCount++).arg(raaHistory::csm_uiLayerEnable).arg(uiUid).arg(0).arg(m_uiFrame));
}

void raaHistory::setDisableLayer(unsigned uiUid)
{
//	QSqlQuery q;
//	q.exec(QString("insert into events values(%1, %2, %3, %4, %5)").arg(m_uiEventCount++).arg(raaHistory::csm_uiLayerDisable).arg(uiUid).arg(0).arg(m_uiFrame));
}

void raaHistory::setNodePin(unsigned uiUid)
{
//	QSqlQuery q;
//	q.exec(QString("insert into events values(%1, %2, %3, %4, %5)").arg(m_uiEventCount++).arg(raaHistory::csm_uiNodePin).arg(uiUid).arg(0).arg(m_uiFrame));
}

void raaHistory::setNodeUnpin(unsigned uiUid)
{
//	QSqlQuery q;
//	q.exec(QString("insert into events values(%1, %2, %3, %4, %5)").arg(m_uiEventCount++).arg(raaHistory::csm_uiNodeUnpin).arg(uiUid).arg(0).arg(m_uiFrame));
}

void raaHistory::prepareNodePositionsUpdate()
{
	m_bPrepareNodePos = true;

	m_PosQ.prepare("insert into positions values (?, ?, ?, ?)");
	m_EventQ.prepare("insert into events values (?, ?, ?, ?, ?)");

	m_vlPosPrimKey.clear();
	m_vlEventPrimKey.clear();
	m_vlX.clear();
	m_vlY.clear();
	m_vlZ.clear();
	m_vlFrame.clear();
	m_vlUid.clear();
	m_vlType.clear();
	m_vlRef.clear();

}

void raaHistory::commitNodePositionsUpdate()
{
	m_bPrepareNodePos = false;

	m_PosQ.addBindValue(m_vlPosPrimKey);
	m_PosQ.addBindValue(m_vlX);
	m_PosQ.addBindValue(m_vlY);
	m_PosQ.addBindValue(m_vlZ);
	m_PosQ.execBatch();

	m_EventQ.addBindValue(m_vlEventPrimKey);
	m_EventQ.addBindValue(m_vlType);
	m_EventQ.addBindValue(m_vlRef);
	m_EventQ.addBindValue(m_vlEventPrimKey);
	m_EventQ.addBindValue(m_vlFrame);
	m_EventQ.execBatch();
}

raaHistory::raaHistory(std::string sName)
{
	m_bPrepareNodePos = false;
	m_uiFrame = 0;
	m_uiEventCount = 0;
	m_uiPositionCount = 0;
	m_DB = QSqlDatabase::addDatabase("QSQLITE");
	m_DB.setDatabaseName(sName.c_str());
	m_DB.open();

//	QSqlQuery q;
//	q.exec(QString("DROP DATAbase %1").arg(sName.c_str()));
//	q.exec("create table positions (id int primary key, x real, y real, z real)");
//	q.exec("create table events (id int primary key, type int, uid int, ref int, frame int)");

	if (!sm_pInstance) sm_pInstance = this;
}


raaHistory::~raaHistory()
{
	if (sm_pInstance == this) sm_pInstance = 0;
}
