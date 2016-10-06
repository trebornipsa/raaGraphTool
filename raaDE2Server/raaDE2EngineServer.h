#pragma once

#include <map>

#include <QtCore/QObject>

#include <raaNetwork/raaNetwork.h>

using namespace raaNet;

class raaConnectionRecord;

#include <raaDataEngine2/raaDataEngineListener.h>


typedef std::map<raaTcpThread*, raaConnectionRecord*> raaConnectionRecordMap;

class raaDE2EngineServer : public QObject, public raaDE2::raaDataEngineListener
{
	Q_OBJECT
public:
	raaDE2EngineServer(QObject *pParent=0);
	virtual ~raaDE2EngineServer();

	virtual void modelAdded(std::string sName);
	virtual void modelRemoved(std::string sName);


public slots:
	void tcpRead(raaTcpMsg*);
	void tcpState(raaTcpThread*, unsigned int);

protected:
	raaNetwork *m_pNetwork;

	bool m_bVerbose;

	void tcpRequest(raaTcpMsg *pMsg);

	raaConnectionRecordMap m_mConnections;
};

