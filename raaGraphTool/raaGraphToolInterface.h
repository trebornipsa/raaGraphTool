#pragma once

#include <QtGui/QMainWindow>

#include "raaGraphModel.h"

#include "raaGraphToolInterfaceQt.h"

class raaGraphToolInterface: public QMainWindow, public Ui::raaGraphToolInterfaceQt
{
	Q_OBJECT
public:
	raaGraphToolInterface(void);
	virtual ~raaGraphToolInterface(void);

	void addClass(QString sName, unsigned int uiShape, int iR, int iG, int iB);

public slots:
	void startClassDrag(QTreeWidgetItem*, int);
	void zoomIn();
	void zoomOut();
	void createItems();
	void loadPajek(bool);

protected:
	raaGraphModel *m_pModel;

	float m_fScale;
};

