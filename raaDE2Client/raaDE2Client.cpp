// raaDE2Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <QtWidgets\QApplication>
#include "raaDE2ClientInterface.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	raaDE2ClientInterface *pInterface = new raaDE2ClientInterface();
	pInterface->show();

	a.exec();

	return 0;
}

