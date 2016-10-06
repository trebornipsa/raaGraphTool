#include "stdafx.h"

#include <raaDE2Kernal/raaKernal.h>
#include <raaDE2Kernal/raaDE2KernalTypes.h>

#include <raaNetwork/raaTcpMsg.h>
#include <raaNetwork/raaTcpThread.h>

#include <QtWidgets/QFileDialog>

#include "raaDE2ClientInterface.moc"
#include "raaDE2ClientInterface.h"
#include <iostream>


raaDE2ClientInterface::raaDE2ClientInterface() 
{
	m_bVerboseNetwork = true;
	m_pClientThread = 0; 

	setupUi(this);
	m_pModel = new raaDE2ClientModel(this);

	connection_ip_combo->addItem(QString("192.168.1.92"));

	m_pNetwork = new raaNetwork(0, this);

	connect(m_pNetwork, SIGNAL(tcpRead(raaTcpMsg*)), SLOT(tcpRead(raaTcpMsg*)));
	connect(m_pNetwork, SIGNAL(tcpState(raaTcpThread*, unsigned int)), SLOT(tcpState(raaTcpThread*, unsigned int)));
	connect(connection_connect_check, SIGNAL(stateChanged(int)), SLOT(connectToServer(int)));
	connect(connection_verbose_check, SIGNAL(stateChanged(int)), SLOT(verboseOutput(int)));
	connect(de_model_load_path_button, SIGNAL(pressed()), SLOT(modelLoadPath()));
	connect(de_model_load_button, SIGNAL(pressed()), SLOT(modelLoad()));
	connect(toolbox, SIGNAL(currentChanged(int)), SLOT(toolChanged(int)));
	connect(model_models_combo, SIGNAL(currentIndexChanged(int)), SLOT(modelChanged(int)));

	connection_verbose_check->setChecked(true);
}


raaDE2ClientInterface::~raaDE2ClientInterface()
{
	if (m_pModel) delete m_pModel;
	if (m_pNetwork) delete m_pNetwork;
	
}

void raaDE2ClientInterface::connectToServer(int iVal)
{
	if(m_pNetwork)
	{
		if (iVal == Qt::Checked)
			m_pNetwork->createTcpClient("clientInterface", connection_ip_combo->currentText(), connection_port_spin->value());
		else
			m_pNetwork->closeTcpConnection("clientInterface");

	}
}

void raaDE2ClientInterface::verboseOutput(int iVal)
{
}

void raaDE2ClientInterface::tcpRead(raaTcpMsg* pMsg)
{
	if (m_bVerboseNetwork)
		connection_text->appendPlainText(QString("<%1>(%2::%3)").arg(pMsg->tcpThread()->name()).arg(tcpMsgTypeToString(pMsg->msgType())).arg(pMsg->msgID()));

	if (pMsg->asUShort(2) == raaDE2Kernal::csm_usDE2Model) m_pModel->update(pMsg);
	else
	{
		switch (pMsg->msgType())
		{
		case raaNet::csm_usTcpMsgInfo:
			readTcpInfoMsg(pMsg);
			break;
		default:
			break;
		}
	}
}

void raaDE2ClientInterface::tcpState(raaTcpThread* pThread, unsigned int uiState)
{
	QString msg;
	msg += pThread->name();
	switch (uiState)
	{ 
	case csm_uiUnconnectedState:
		msg += " -> StateChanged::UnconnectedState";
		connection_connect_check->setText("Connect");
		break;
	case csm_uiHostLookupState:
		msg += " -> StateChanged::HostLookupState";
		break;
	case csm_uiConnectingState:
		msg += " -> StateChanged::ConnectingState";
		break;
	case csm_uiConnectedState:
		msg += " -> StateChanged::ConnectedState";
		connection_connect_check->setText("Connected");
		break;
	case csm_uiNameConnectedState:
		msg += " -> StateChanged::NameConnectedState";
		if (pThread->name() == "clientInterface")
		{
			m_pClientThread = pThread;
			m_pModel->setThread(pThread);
		}
		break;
	case csm_uiBoundState:
		msg += " -> StateChanged::BoundState";
		break;
	case csm_uiClosingState:
		msg += " -> StateChanged::ClosingState";
		if (pThread->name() == "clientInterface")
		{
			m_pClientThread = 0;
			m_pModel->setThread(0);
			connection_connect_check->setCheckState(Qt::Unchecked);
			connection_connect_check->setText("Closing");
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

void raaDE2ClientInterface::modelLoadPath()
{
	de_model_load_path_edit->setText(QFileDialog::getOpenFileName(this));
}

void raaDE2ClientInterface::modelLoad()
{
	if(m_pClientThread)
	{
		raaNet::raaTcpMsg *pMsg = new raaTcpMsg(raaNet::csm_usTcpMsgRequest);
		pMsg->add(raaDE2Kernal::csm_usDE2Engine);
		pMsg->add(raaDE2Kernal::csm_usDE2LoadModel);
		pMsg->add(de_model_load_path_edit->text().toStdString());
		pMsg->add(de_model_load_name_edit->text().toStdString());

		m_pNetwork->write(m_pClientThread, pMsg);
	}
}

void raaDE2ClientInterface::toolChanged(int iVal)
{
	if(toolbox->itemText(iVal)==QString("Model") && model_models_combo->currentText()!=QString("Model"))
	{
		raaNet::raaTcpMsg *pMsg = new raaTcpMsg(raaNet::csm_usTcpMsgRequest);
		pMsg->add(raaDE2Kernal::csm_usDE2Model);
		pMsg->add(raaDE2Kernal::csm_usDE2ModelStatus);
		pMsg->add(model_models_combo->currentText().toStdString());

		m_pNetwork->write(m_pClientThread, pMsg);

	}
}

void raaDE2ClientInterface::modelChanged(int)
{
	if (model_models_combo->currentText() != QString("Model"))
	{
		raaNet::raaTcpMsg *pMsg = new raaTcpMsg(raaNet::csm_usTcpMsgRequest);
		pMsg->add(raaDE2Kernal::csm_usDE2Model);
		pMsg->add(raaDE2Kernal::csm_usDE2ModelStatus);
		pMsg->add(model_models_combo->currentText().toStdString());

		m_pNetwork->write(m_pClientThread, pMsg);

	}
}

void raaDE2ClientInterface::readTcpInfoMsg(raaTcpMsg* pMsg)
{
	if(pMsg)
	{
		unsigned short usMajor = pMsg->asUShort(2);
		unsigned short usMinor = pMsg->asUShort(3);

		switch(usMajor)
		{
			case raaDE2Kernal::csm_usDE2Engine:
				switch(usMinor)
				{
					case raaDE2Kernal::csm_usDE2ModelAdded:
						model_models_combo->addItem(pMsg->asString(4).c_str());
						break;
					case raaDE2Kernal::csm_usDE2ModelRemoved:
						model_models_combo->removeItem(model_models_combo->findText(pMsg->asString(4).c_str()));
						break;
				}
				break;
			default:
				break;
		}
	}
}
