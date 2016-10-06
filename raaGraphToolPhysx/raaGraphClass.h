#pragma once

#include <list>

#include <QtWidgets/QTreeWidgetItem>

typedef std::list<class raaGraphClass*> raaGraphClasses;

class raaGraphClass: public QTreeWidgetItem
{
public:
	const static unsigned int csm_uiShapeRect=0;
	const static unsigned int csm_uiShapeElipse=1;

	raaGraphClass(QString sName, unsigned int uiShape, int iR, int iG, int iB);
	virtual ~raaGraphClass(void);

	virtual QString mime();
	virtual QString name();	
	void setName(QString sName);

	void addChild(raaGraphClass *pClass);

protected:
	QString m_sClassName;
	QString m_sClassMime;
	raaGraphClasses m_lClasses;
};

