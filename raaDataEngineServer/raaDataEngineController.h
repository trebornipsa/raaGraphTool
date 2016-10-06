#pragma once

#include <QtCore/QObject>

#include <raaNetwork/raaTcpMsg.h>
#include <raaNetwork/raaNetwork.h>

using namespace raaNet;

class raaDataEngineController: public QObject
{
	Q_OBJECT
public:
	raaDataEngineController();
	virtual ~raaDataEngineController();

public slots:
	void readServer(raaTcpMsg* pMsg);

protected:
	raaNetwork *m_pServer;
};