#include "stdafx.h"

#include "raaTestServerInterface.moc"
#include "raaTestServerInterface.h"
#include <iostream>


raaTestServerInterface::raaTestServerInterface()
{
	srand(0);
	m_iTimer = 0;
	m_pNetwork = 0;
	m_uiTcpCounter = 0;

	setupUi(this);

	connect(connection_check, SIGNAL(stateChanged(int)), this, SLOT(startServer(int)));
	connect(input_send_button, SIGNAL(pressed()), this, SLOT(send()));

	connect(udp_connect_button, SIGNAL(pressed()), SLOT(udpConnect()));
	connect(udp_stream_check, SIGNAL(stateChanged(int)), SLOT(udpStream(int)));

	udp_port_spin->setValue(65203);
	udp_name_edit->setText("raaTest");
}

raaTestServerInterface::~raaTestServerInterface()
{
	if (m_pNetwork) delete m_pNetwork;
}

void raaTestServerInterface::startServer(int i) 
{
	if(i==Qt::Checked)
	{
		if (!m_pNetwork)
		{
			m_pNetwork = new raaNet::raaNetwork(connection_port_spin->value(), this);

			connect(m_pNetwork, SIGNAL(tcpRead(raaTcpMsg *)), SLOT(tcpRead(raaTcpMsg *)));
			connect(m_pNetwork, SIGNAL(tcpState(raaTcpThread*, unsigned int)), this, SLOT(tcpState(raaTcpThread*, unsigned int)));
			connect(m_pNetwork, SIGNAL(udpRead(raaUdpMsg *)), SLOT(udpRead(raaUdpMsg *)));
			connect(m_pNetwork, SIGNAL(udpState(raaUdpThread*, unsigned int)), this, SLOT(udpState(raaUdpThread*, unsigned int)));

		}
	}
}

void raaTestServerInterface::tcpRead(raaNet::raaTcpMsg* pMsg)
{
	output_text->append(QString("%1 (%2::%3) -> %4")
		.arg(pMsg->tcpThread()->name())
		.arg(raaNet::tcpMsgTypeToString(pMsg->msgType()))
		.arg(pMsg->msgID()).
		arg(QString(pMsg->data())));
}

void raaTestServerInterface::tcpState(raaTcpThread* pThread, unsigned int uiState)
{
	QString msg;
	msg += pThread->name();
	switch (uiState)
	{
	case csm_uiUnconnectedState:
		msg += " -> StateChanged::UnconnectedState";
		break;
	case csm_uiHostLookupState:
		msg += " -> StateChanged::HostLookupState";
		break;
	case csm_uiConnectingState:
		msg += " -> StateChanged::ConnectingState";
		break;
	case csm_uiConnectedState:
		msg += " -> StateChanged::ConnectedState";
		break;
	case csm_uiNameConnectedState:
		msg += " -> StateChanged::NameConnectedState";
		input_to_combo->addItem(pThread->name());
		break;
	case csm_uiBoundState:
		msg += " -> StateChanged::BoundState";
		break;
	case csm_uiClosingState:
		{
			msg += " -> StateChanged::ClosingState";
			int iIndex=input_to_combo->findText(pThread->name());
			input_to_combo->removeItem(iIndex);
		}
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

void raaTestServerInterface::udpState(raaUdpThread* pThread, unsigned int uiState)
{
	QString msg;
	msg += pThread->name();
	switch (uiState)
	{
	case csm_uiUnconnectedState:
		msg += " -> udpStateChanged::UnconnectedState";
		break;
	case csm_uiHostLookupState:
		msg += " -> udpStateChanged::HostLookupState";
		break;
	case csm_uiConnectingState:
		msg += " -> udpStateChanged::ConnectingState";
		break;
	case csm_uiConnectedState:
		msg += " -> udpStateChanged::ConnectedState";
		break;
	case csm_uiNameConnectedState:
		msg += " -> udpStateChanged::NameConnectedState";
		break;
	case csm_uiBoundState:
		msg += " -> udpStateChanged::BoundState";
		break;
	case csm_uiClosingState:
		msg += " ->udp StateChanged::ClosingState";
	break;
	case csm_uiListeningState:
		msg += " -> udpStateChanged::ListeningState";
		break;
	default:
		msg += " -> udpStateChanged::UnknownState";
		break;
	}

	std::cout << msg.toStdString() << std::endl;
}

void raaTestServerInterface::send()
{
	QString sSocket = input_to_combo->currentText();
	QString sMsg = input_msg_edit->text();

	m_pNetwork->writeTcp(raaNet::csm_usTcpMsgInfo, m_uiTcpCounter++, sSocket, sMsg.toLocal8Bit());
}

void raaTestServerInterface::udpConnect()
{
	if (m_pNetwork)
	{
		m_pNetwork->createUdpServer(udp_name_edit->text(), QString("localhost"), udp_port_spin->value());
	}
}

void raaTestServerInterface::udpStream(int iState)
{
	if(iState==Qt::Checked)
	{
		m_iTimer=startTimer(10);
	}
	else if (m_iTimer)
	{
		killTimer(m_iTimer);
		m_iTimer = 0;
	}
}

void raaTestServerInterface::udpRead(raaUdpMsg* pMsg)
{
	udp_text->appendPlainText(QString("%1 -> %2").arg(pMsg->thread()->name()).arg(QString(pMsg->data())));
}

void raaTestServerInterface::timerEvent(QTimerEvent* pEvent)
{
	if(m_pNetwork)
	{
		QByteArray data;
		int i = rand();
		data.append((const char*)&i, sizeof(int));

		m_pNetwork->writeUdp(udp_name_edit->text(), data);
	}
}
