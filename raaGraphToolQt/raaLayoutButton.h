#pragma once

#include <QtWidgets/QPushButton>

class raaDataEngineLayout;

class raaLayoutButton: public QPushButton
{
	Q_OBJECT
public:
	raaLayoutButton(QString sName, raaDataEngineLayout *pLayout, QWidget *pParent=0);
	virtual ~raaLayoutButton();
	static void tick();

public slots:
	void enacted();

protected:
	raaDataEngineLayout *m_pLayout;
	QString m_sName;

	static raaLayoutButton* sm_pActive;
	static unsigned int sm_uiCount;
};

