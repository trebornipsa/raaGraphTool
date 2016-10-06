// raaTestServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <raaDataEngine2/raaDataEngine.h>

#include <QtWidgets\QApplication>
#include "raaTestServerInterface.h"

int main(int argc, char* argv[])
{
	raaDE2::raaDataEngine::start();
	QApplication a(argc, argv);

	raaTestServerInterface *pInterface = new raaTestServerInterface();
	pInterface->show();

	a.exec();
	raaDE2::raaDataEngine::stop();

	return 0;
}


