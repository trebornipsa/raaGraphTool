#pragma once

#include <QtWidgets/QMainWindow>

#include <raaNetwork/raaNetwork.h>

#include "raaDE2ClientModel.h"
#include "raaDE2ClientInterfaceQt.h"

using namespace raaNet;

class raaDE2ClientInterface : public QMainWindow, public Ui::raaDE2ClientInterfaceQt
{
	Q_OBJECT
public:
	raaDE2ClientInterface();
	virtual ~raaDE2ClientInterface();

public slots:
	void connectToServer(int);
	void verboseOutput(int);
	void tcpRead(raaTcpMsg*);
	void tcpState(raaTcpThread*, unsigned int);

	void modelLoadPath();
	void modelLoad();

	void toolChanged(int);
	void modelChanged(int);


protected:
	raaNetwork *m_pNetwork;
	raaTcpThread *m_pClientThread;

	raaDE2ClientModel *m_pModel;

	bool m_bVerboseNetwork;

	void readTcpInfoMsg(raaTcpMsg *pMsg);


};

