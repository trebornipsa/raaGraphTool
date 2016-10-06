#pragma once

#include <QtWidgets/QMainWindow>

#include <raaNetwork/raaNetwork.h>
#include <raaNetwork/raaTcpMsg.h>
#include <raaNetwork/raaTcpThread.h>
#include <raaNetwork/raaUdpMsg.h>
#include <raaNetwork/raaUdpThread.h>
#include <raaNetwork/raaNetworkTypes.h>

#include "raaTestServerInterfaceQt.h"

using namespace raaNet;

class raaTestServerInterface : public QMainWindow, public Ui::raaTestServerInterfaceQt
{
	Q_OBJECT
public:
	raaTestServerInterface();
	virtual ~raaTestServerInterface();

public slots:
	void startServer(int);
	void tcpRead(raaTcpMsg*);
	void tcpState(raaTcpThread*, unsigned int);
	void udpState(raaUdpThread*, unsigned int);
	void send();

	void udpConnect();
	void udpStream(int);
	void udpRead(raaUdpMsg*);

protected:
	raaNet::raaNetwork *m_pNetwork;

	void timerEvent(QTimerEvent *pEvent);
	int m_iTimer;

	unsigned int m_uiTcpCounter;
};

