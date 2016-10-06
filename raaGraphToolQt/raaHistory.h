#pragma once
#include <QtCore/QVariantList>
#include <QtSql/QSqlDatabase>
#include  <QtSql/QSqlQuery>

#include <string>

class raaHistory
{
public:
	const static unsigned int csm_uiTypeFrame = 0;
	const static unsigned int csm_uiTypeNodePosition = 1;
	const static unsigned int csm_uiLayerEnable = 2;
	const static unsigned int csm_uiLayerDisable = 3;
	const static unsigned int csm_uiNodePin = 4;
	const static unsigned int csm_uiNodeUnpin = 5;

	static void start(std::string sName);
	static void end();
	static raaHistory* instance();

	void setFrame(unsigned int uiFrame);
	void addFrame();
	void setNodePosition(unsigned int uiUid, float fX, float fY, float fZ);
	void setEnableLayer(unsigned int uiUid);
	void setDisableLayer(unsigned int uiUid);
	void setNodePin(unsigned int uiUid);
	void setNodeUnpin(unsigned int uiUid);

	void prepareNodePositionsUpdate();
	void commitNodePositionsUpdate();

protected:
	static unsigned int sm_uiInstance;
	static raaHistory *sm_pInstance;

	raaHistory(std::string sName);
	virtual ~raaHistory();

	QSqlDatabase m_DB;
	unsigned int m_uiFrame;
	unsigned int m_uiEventCount;
	unsigned int m_uiPositionCount;

	bool m_bPrepareNodePos;
	QVariantList m_vlPosPrimKey;
	QVariantList m_vlEventPrimKey;
	QVariantList m_vlX;
	QVariantList m_vlY;
	QVariantList m_vlZ;
	QVariantList m_vlFrame;
	QVariantList m_vlUid;
	QVariantList m_vlType;
	QVariantList m_vlRef;
	QSqlQuery m_EventQ;
	QSqlQuery m_PosQ;



};

