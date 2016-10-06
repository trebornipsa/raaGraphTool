// raaGraphTool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <QtWidgets/QApplication>

#include "raaGraphToolInterface.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	raaGraphToolInterface *pInterface=new raaGraphToolInterface();

	pInterface->addClass("Person", 0, 80, 60, 200);
	pInterface->addClass("Building", 0, 120, 180, 120);
	pInterface->addClass("Computer", 0, 160, 55, 70);

	pInterface->show();

	a.exec();

	return 0;
}

