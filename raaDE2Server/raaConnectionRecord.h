#pragma once

#include <string>

#include <raaNetwork/raaTcpThread.h>
#include <raaNetwork/raaUdpThread.h>

#include <raaDataEngine2/raaDataModel.h>
#include <raaDataEngine2/raaDataModelListener.h>

class raaConnectionRecord : public raaDE2::raaDataModelListener
{
public:
	raaConnectionRecord(std::string sName);
	virtual ~raaConnectionRecord();

	std::string name();

	raaNet::raaTcpThread *tcpThread();
	raaNet::raaUdpThread *udpThread();

	void setTcpThread(raaNet::raaTcpThread *pThread);
	void setUdpThread(raaNet::raaUdpThread *pThread);

	void setModel(raaDE2::raaDataModel *pModel);
	raaDE2::raaDataModel* model();

	virtual void updatedNode(raaDE2::raaDataNode* pNode);
	virtual void newNode(raaDE2::raaDataNode* pNode);
	virtual void updatedArc(raaDE2::raaDataArc* pArc);
	virtual void newArc(raaDE2::raaDataArc* pArc);

	virtual void updatedNodes(raaDE2::raaDataModel* pModel);


protected:
	std::string m_sName;
	raaNet::raaTcpThread *m_pTcpThread;
	raaNet::raaUdpThread *m_pUdpThread;
	raaDE2::raaDataModel *m_pModel;
	
};

