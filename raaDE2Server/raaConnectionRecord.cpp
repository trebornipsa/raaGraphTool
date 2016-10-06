#include "stdafx.h"

#include <raaDataEngine2/raaDataEngine.h>
#include <raaDataEngine2/raaDataNode.h>
#include <raaDataEngine2/raaDataArc.h>

#include <raaDE2Kernal/raaKernal.h>
#include <raaDE2Kernal/raade2kernaltypes.h>

#include <raaNetwork/raaTcpMsg.h>
#include <raaNetwork/raaTcpThread.h>

#include "raaConnectionRecord.h"


raaConnectionRecord::raaConnectionRecord(std::string sName)
{
	m_sName = sName;
	m_pTcpThread = 0;
	m_pUdpThread = 0;
}

raaConnectionRecord::~raaConnectionRecord()
{
	if (m_pTcpThread) m_pTcpThread->close();
	if (m_pUdpThread) m_pUdpThread->close();
}

std::string raaConnectionRecord::name()
{
	return m_sName;
}

raaNet::raaTcpThread* raaConnectionRecord::tcpThread()
{
	return m_pTcpThread;
}

raaNet::raaUdpThread* raaConnectionRecord::udpThread()
{
	return m_pUdpThread;
}

void raaConnectionRecord::setTcpThread(raaNet::raaTcpThread* pThread)
{
	m_pTcpThread = pThread;
}

void raaConnectionRecord::setUdpThread(raaNet::raaUdpThread* pThread)
{
	m_pUdpThread = pThread;
}

void raaConnectionRecord::setModel(raaDE2::raaDataModel* pModel)
{
	m_pModel = pModel;
}

raaDE2::raaDataModel* raaConnectionRecord::model()
{
	return m_pModel;
}

void raaConnectionRecord::updatedNode(raaDE2::raaDataNode* pNode)
{
}

void raaConnectionRecord::newNode(raaDE2::raaDataNode* pNode)
{
	raaDE2Kernal::raaVec v;
	v.x = pNode->position()[0];
	v.y = pNode->position()[1];
	v.z = pNode->position()[2];

	//std::cout << "Sent Node -> " << pNode->name() << std::endl;
 
	raaNet::raaTcpMsg *pMsg = new raaNet::raaTcpMsg(raaNet::csm_usTcpMsgReply);
	pMsg->add(raaDE2Kernal::csm_usDE2Node);
	pMsg->add(raaDE2Kernal::csm_usDE2NewNode);
	pMsg->add(pNode->name());
	pMsg->add(pNode->uid().serialize(), sizeof(raaDE2::raaUID));
	pMsg->add((const char*)&v, sizeof(raaDE2Kernal::raaVec));

	m_pTcpThread->write(pMsg);
}

void raaConnectionRecord::updatedArc(raaDE2::raaDataArc* pArc)
{
}

void raaConnectionRecord::newArc(raaDE2::raaDataArc* pArc)
{	
	raaNet::raaTcpMsg *pMsg = new raaNet::raaTcpMsg(raaNet::csm_usTcpMsgReply);
	pMsg->add(raaDE2Kernal::csm_usDE2Arc);
	pMsg->add(raaDE2Kernal::csm_usDE2NewArc);
	pMsg->add(pArc->name());
	pMsg->add(pArc->uid().serialize(), sizeof(raaDE2::raaUID));
	for (raaDE2::raaDataNodeList::const_iterator it = pArc->nodes().begin(); it != pArc->nodes().end(); it++) pMsg->add((const char*)(*it)->uid().serialize(), sizeof(raaDE2::raaUID));

	m_pTcpThread->write(pMsg);
}

void raaConnectionRecord::updatedNodes(raaDE2::raaDataModel* pModel)
{
	if(pModel && m_pUdpThread)
	{
		raaNet::raaUdpMsg *pMsg = 0;
		unsigned int uiCount = 0;
		for(raaDE2::raaDataNodeList::const_iterator cit=pModel->nodes().begin();cit!=pModel->nodes().end();cit++)
		{
			if (!pMsg)
			{
				pMsg = new raaNet::raaUdpMsg(raaNet::csm_usUdpMsgInfo);
				pMsg->add(raaDE2Kernal::csm_usDE2Node);
				pMsg->add(raaDE2Kernal::csm_usDE2UpdateNodePositions);
			}

			pMsg->add((*cit)->uid().serialize(), sizeof(raaDE2::raaUID));
			pMsg->add((*cit)->position().get(), 3);
			uiCount++;

			if(uiCount>10)
			{
				m_pUdpThread->write(pMsg);
				pMsg = 0;
				uiCount = 0;
			}
		}
	}
}

