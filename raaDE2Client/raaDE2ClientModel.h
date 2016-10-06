#pragma once

#include <QtCore/QObject>

#include <string>
#include <raaNetwork/raaTcpMsg.h>
#include <raaNetwork/raaTcpThread.h>


class raaDE2ClientInterface;

class raaDE2ClientModel: public QObject
{
	Q_OBJECT
public:

	raaDE2ClientModel(raaDE2ClientInterface *pInterface);
	~raaDE2ClientModel();

	void setThread(raaNet::raaTcpThread *pThread);

	void update(raaNet::raaTcpMsg *pMsg);

public slots:
	void solveCheck(int);

protected:
	raaDE2ClientInterface *m_pInterface;
	raaNet::raaTcpThread *m_pThread;
	std::string m_sName;
	bool m_bSolve;


	void updateAll(raaNet::raaTcpMsg *pMsg);
	void updateSolve(raaNet::raaTcpMsg *pMsg);
};

