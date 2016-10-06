// raaDE2Server.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QByteArray>

#include "raaDE2EngineServer.h"

#include <QtCore/QString>

#include <raaDataEngine2/raaDataUID.h>
#include <raaDE2Kernal/raade2kernaltypes.h>
#include <iostream>

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);

	raaDE2Kernal::raaVec v, *pV;
	v.x = 0.0f;
	v.y = -3.5f;
	v.z = 2.72734f;

	QString s(QByteArray((const char*)&v, sizeof(raaDE2Kernal::raaVec)));

	std::cout << "v -> " << v.x << "   " << v.y << "   " << v.z << std::endl;
	std::cout << "Str -> " << s.toStdString() << std::endl;

	pV = (raaDE2Kernal::raaVec*)s.toLocal8Bit().data();

	std::cout << "pV -> " << pV->x << "   " << pV->y << "   " << pV->z << std::endl;



	raaDE2EngineServer *pServer = new raaDE2EngineServer();

	a.exec();


    return 0;
}

