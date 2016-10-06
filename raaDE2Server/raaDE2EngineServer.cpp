#include "stdafx.h"

#include <iostream>

#include <raaDE2Kernal/raaKernal.h>
//#include <raaDE2Kernal/raaDE2KernalTypes.h>
//#include <raaDataEngine2/raaDataEngineTypes.h>
#include <raaNetwork/raaTcpMsg.h>
#include <raaNetwork/raaTcpThread.h>

#include "raaDE2EngineServer.moc"
#include "raaDE2EngineServer.h"


#include <raaDataEngine2/raaDataEngine.h>
#include <raaDataEngine2/raaDataModel.h>

#include "raaConnectionRecord.h"

raaDE2EngineServer::raaDE2EngineServer(QObject *pParent) : QObject (pParent)
{
	raaDE2::raaDataEngine::start();
	raaDE2::raaDataEngine::instance()->addListener(this);

	m_bVerbose = true;

	m_pNetwork = new raaNet::raaNetwork(65204, this);

	connect(m_pNetwork, SIGNAL(tcpRead(raaTcpMsg*)), SLOT(tcpRead(raaTcpMsg*)));
	connect(m_pNetwork, SIGNAL(tcpState(raaTcpThread*, unsigned int)), SLOT(tcpState(raaTcpThread*, unsigned int)));

//	m_pNetwork->createUdpServer(QString("updator"), QString("localhost"), 65205);
}

raaDE2EngineServer::~raaDE2EngineServer()
{
	raaDE2::raaDataEngine::instance()->removeListener(this);
	if (m_pNetwork) delete m_pNetwork;
	raaDE2::raaDataEngine::stop();
}

void raaDE2EngineServer::tcpRead(raaTcpMsg* pMsg)
{

	if (m_bVerbose)
	{
		std::cout << "<" << pMsg->tcpThread()->name().toStdString() << ">(" << tcpMsgTypeToString(pMsg->msgType()).toStdString() << "::" << pMsg->msgID() << ")" << std::endl;


//		raaDE2Kernal::raaKernal::printMsg(pMsg->data());

	}

	switch (pMsg->msgType())
	{
		case raaNet::csm_usTcpMsgRequest:
			tcpRequest(pMsg);
			break;
		default:
			break;
	}
}
void raaDE2EngineServer::tcpState(raaTcpThread* pThread, unsigned int uiState)
{
	QString msg;
	msg += pThread->name();
	switch (uiState)
	{
	case csm_uiUnconnectedState:
		{
			msg += " -> StateChanged::UnconnectedState";

			if(m_mConnections.find(pThread)!=m_mConnections.end())
			{
				if(m_mConnections[pThread]->model())
				{
					m_mConnections[pThread]->model()->removeListener(m_mConnections[pThread]);
				}
				delete m_mConnections[pThread];
				m_mConnections.erase(pThread);
			}
		}
		break;
	case csm_uiHostLookupState:
		msg += " -> StateChanged::HostLookupState";
		break;
	case csm_uiConnectingState:
		msg += " -> StateChanged::ConnectingState";
		break;
	case csm_uiConnectedState:
		{
			msg += " -> StateChanged::ConnectedState";
		}
		break;
	case csm_uiNameConnectedState:
		{
			msg += " -> StateChanged::NameConnectedState";

			m_mConnections[pThread]=new raaConnectionRecord(pThread->name().toStdString());
			m_mConnections[pThread]->setTcpThread(pThread);
		}
		break;
	case csm_uiBoundState:
		msg += " -> StateChanged::BoundState";
		break;
	case csm_uiClosingState:
		msg += " -> StateChanged::ClosingState";
		break;
	case csm_uiListeningState:
		msg += " -> StateChanged::ListeningState";
		break;
	default:
		msg += " -> StateChanged::UnknownState";
		break;
	}
	std::cout << msg.toStdString() << std::endl;

}

void raaDE2EngineServer::tcpRequest(raaTcpMsg* pMsg)
{
	if(pMsg && pMsg->length()>=4)
	{
		unsigned short usMajor = pMsg->asUShort(2);
		unsigned short usMinor = pMsg->asUShort(3);
		switch(usMajor)
		{
			case raaDE2Kernal::csm_usDE2Engine:
				switch(usMinor)
				{
					case raaDE2Kernal::csm_usDE2LoadModel:
					{
						if(pMsg->length()>=6) raaDE2::raaDataModel *pModel = raaDE2::raaDataEngine::instance()->loadModel(pMsg->asString(5), pMsg->asString(4));
					}
					break;
					case raaDE2Kernal::csm_usDE2TrackModel:
					{
						if (pMsg->length() >= 5)
						{
							if (m_mConnections[pMsg->tcpThread()]->model()) m_mConnections[pMsg->tcpThread()]->model()->removeListener(m_mConnections[pMsg->tcpThread()]);
							raaDE2::raaDataModel *pModel = raaDE2::raaDataEngine::instance()->model(pMsg->asString(4));
							if (pModel) pModel->addListener(m_mConnections[pMsg->tcpThread()]);

							if (m_pNetwork->createUdpServer(m_mConnections[pMsg->tcpThread()]->name().c_str(), "localhost", (quint16)65021))
							{
								m_mConnections[pMsg->tcpThread()]->setUdpThread(m_pNetwork->udpThread(m_mConnections[pMsg->tcpThread()]->name().c_str()));
								
								raaNet::raaTcpMsg *pMsgR = new raaNet::raaTcpMsg(raaNet::csm_usTcpMsgReply);
								pMsgR->add(raaDE2Kernal::csm_usDE2Model);
								pMsgR->add(raaDE2Kernal::csm_usDE2UdpConnection);
								pMsgR->add((unsigned short)65021);

								pMsg->tcpThread()->write(pMsgR);
							}

						}
					}
					break;
				case raaDE2Kernal::csm_usDE2RequestModels:
					{
						raaNet::raaTcpMsg *pMsgR = new raaTcpMsg(raaNet::csm_usTcpMsgReply);
						pMsgR->add(raaDE2Kernal::csm_usDE2Engine);
						pMsgR->add(raaDE2Kernal::csm_usDE2ModelsList);

						for (raaDE2::raaStringList::const_iterator it = raaDE2::raaDataEngine::instance()->models().begin(); it != raaDE2::raaDataEngine::instance()->models().end(); it++)
						{
							pMsgR->add((*it));
						}

						pMsg->tcpThread()->write(pMsgR);
					}
						break;
					default:
						break;
				}
				break;
			case raaDE2Kernal::csm_usDE2Model:
			{
				switch(usMinor)
				{
				case raaDE2Kernal::csm_usDE2ModelStatus:
				{
					std::string sName = pMsg->asString(4);

					raaDE2::raaDataModel *pModel= raaDE2::raaDataEngine::instance()->model(sName);

					if (pModel)
					{
						raaNet::raaTcpMsg *pMsgR = new raaTcpMsg(raaNet::csm_usTcpMsgReply);
						pMsgR->add(raaDE2Kernal::csm_usDE2Model);
						pMsgR->add(raaDE2Kernal::csm_usDE2ModelStatus);
						pMsgR->add(sName);
						pMsgR->add(pModel->isSolving());
						pMsgR->add(pModel->damping());


						pMsg->tcpThread()->write(pMsgR);
					}
				}
				break;
				case raaDE2Kernal::csm_usDE2Solve:
				{
					std::string sName = pMsg->asString(4);

					raaDE2::raaDataModel *pModel = raaDE2::raaDataEngine::instance()->model(sName);

					if (pModel)
					{
						bool bSolve = pMsg->asBool(5);

						pModel->solve(bSolve);

						raaNet::raaTcpMsg *pMsgR = new raaTcpMsg(raaNet::csm_usTcpMsgInfo);
						pMsgR->add(raaDE2Kernal::csm_usDE2Model);
						pMsgR->add(raaDE2Kernal::csm_usDE2Solve);
						pMsgR->add(sName);
						pMsgR->add(pModel->isSolving());

						m_pNetwork->write(pMsgR);
					}
				}
					break;
				default:
					break;
				}
			}
			default:
				break;
		}
	}
}

void raaDE2EngineServer::modelAdded(std::string sName)
{
	raaNet::raaTcpMsg *pMsg = new raaNet::raaTcpMsg(raaNet::csm_usTcpMsgInfo);
	pMsg->add(raaDE2Kernal::csm_usDE2Engine);
	pMsg->add(raaDE2Kernal::csm_usDE2ModelAdded);
	pMsg->add(sName);
	m_pNetwork->write(pMsg);
}

void raaDE2EngineServer::modelRemoved(std::string sName)
{
	raaNet::raaTcpMsg *pMsg = new raaNet::raaTcpMsg(raaNet::csm_usTcpMsgInfo);
	pMsg->add(raaDE2Kernal::csm_usDE2Engine);
	pMsg->add(raaDE2Kernal::csm_usDE2ModelRemoved);
	pMsg->add(sName);
	m_pNetwork->write(pMsg);
}