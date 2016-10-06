#include "stdafx.h"



#include "raaDataEngineController.moc"
#include "raaDataEngineController.h"
#include <iostream>

raaDataEngineController::raaDataEngineController()
{
	m_pServer = new raaNetwork(601022, 601023, this); 

	connect(m_pServer, SIGNAL(read(raaTcpMsg*)), SLOT(readServer(raaTcpMsg*)));

}

raaDataEngineController::~raaDataEngineController()
{
}

void raaDataEngineController::readServer(raaTcpMsg* pMsg)
{
	std::cout << pMsg->data().toStdString() << std::endl;
}
