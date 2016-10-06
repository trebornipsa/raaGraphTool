// raaExcelTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <atlstr.h>
#include <afxdb.h>
#include <iostream>



int main()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	db.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + QString("C:\\robbie\\data\\DecisionTrees\\test.xlsx"));

	//	if(db.)


	if (db.open())
	{
		QSqlQuery query("select''' from [" + QString("Sheet1") + "$]"); // Select range, place A1:B5 after $
		while (query.next())
		{
			//			QString column1 = query.value(0).toString();

			std::cout << "Data -> " << query.value(0).toString().toStdString() << std::endl;
		}
	}
	else
	{
		std::cout << "Error -> " << db.lastError().text().toStdString() << std::endl;
	}
	
	return 0;
}

