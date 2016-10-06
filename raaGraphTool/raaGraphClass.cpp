#include "StdAfx.h"
#include "raaGraphClass.h"


raaGraphClass::raaGraphClass(QString sName, unsigned int uiShape, int iR, int iG, int iB)
{
	setName(sName);
	m_sClassMime=QString("::")+QString::number(uiShape)+QString("::")+QString::number(iR)+QString("::")+QString::number(iG)+QString("::")+QString::number(iB);
}


raaGraphClass::~raaGraphClass(void)
{
}

QString raaGraphClass::name()
{
	return m_sClassName;
}

void raaGraphClass::setName( QString sName )
{
	m_sClassName=sName;
	setText(0, m_sClassName);
}

void raaGraphClass::addChild( raaGraphClass *pClass )
{
	m_lClasses.push_back(pClass);
}

QString raaGraphClass::mime()
{
	return m_sClassName+m_sClassMime;
}
