// raaGraphToolQt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <raaUtilities/raaVector.h>

#include <QtWidgets\QApplication>
#include <QtWidgets\QSplitter>

#include <raaDataEngine/raaDataEngine.h>

//#include <windows.h>

#include "raaGraphInterface.h"

int main(int argc, char* argv[])
{
	raaVector v;

	raaDataEngine::start();

	QApplication a(argc, argv);

	raaGraphInterface *pInterface = new raaGraphInterface();

	pInterface->show(); 

	a.exec();
	raaDataEngine::end();
    return 0;
}

