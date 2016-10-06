#include "stdafx.h"

#include <raaDE2Kernal/raade2kernaltypes.h>

#include "raaDE2ClientInterface.h"

#include "raaDE2ClientModel.moc"
#include "raaDE2ClientModel.h"


raaDE2ClientModel::raaDE2ClientModel(raaDE2ClientInterface *pInterface)
{
	m_pInterface = pInterface;
	m_pThread = 0;

	connect(pInterface->model_solve_check, SIGNAL(stateChanged(int)), SLOT(solveCheck(int)));
}

raaDE2ClientModel::~raaDE2ClientModel()
{
}

void raaDE2ClientModel::setThread(raaNet::raaTcpThread* pThread)
{
	m_pThread = pThread;
}

void raaDE2ClientModel::update(raaNet::raaTcpMsg* pMsg)
{
	if (pMsg)
	{
		unsigned short usType = pMsg->asUShort(0);
		unsigned short usMajor = pMsg->asUShort(2);
		unsigned short usMinor = pMsg->asUShort(3);

		if (usMajor == raaDE2Kernal::csm_usDE2Model)
		{
			switch (usType)
			{
			case raaNet::csm_usTcpMsgReply:
				switch (usMinor)
				{
					case raaDE2Kernal::csm_usDE2ModelStatus:
						updateAll(pMsg);
						break;
				}
				break;
			case raaNet::csm_usTcpMsgInfo:
				switch(usMinor)
				{
					case raaDE2Kernal::csm_usDE2Solve:
						updateSolve(pMsg);
						break;

				}
				break;
			}
		}
	}
}

void raaDE2ClientModel::solveCheck(int iVal)
{
	bool bSolve = (iVal == Qt::Checked) ? true : false;

	if(bSolve!=m_bSolve && m_pThread)
	{
		raaNet::raaTcpMsg *pMsg = new raaTcpMsg(raaNet::csm_usTcpMsgRequest);
		pMsg->add(raaDE2Kernal::csm_usDE2Model);
		pMsg->add(raaDE2Kernal::csm_usDE2Solve);
		pMsg->add(m_sName);
		pMsg->add(bSolve);

		m_pThread->write(pMsg);
	}
}

void raaDE2ClientModel::updateAll(raaNet::raaTcpMsg* pMsg)
{
	if(pMsg)
	{
		m_sName = pMsg->asString(4);
		m_bSolve = pMsg->asBool(5);

		if (m_pInterface)
		{
			if (m_bSolve)
				m_pInterface->model_solve_check->setCheckState(Qt::Checked);
			else
				m_pInterface->model_solve_check->setCheckState(Qt::Unchecked);
		}
	}
}

void raaDE2ClientModel::updateSolve(raaNet::raaTcpMsg* pMsg)
{
	if(pMsg)
	{
		m_bSolve = pMsg->asBool(5);

		if (m_pInterface)
		{
			if (m_bSolve)
				m_pInterface->model_solve_check->setCheckState(Qt::Checked);
			else
				m_pInterface->model_solve_check->setCheckState(Qt::Unchecked);
		}
	}
}
