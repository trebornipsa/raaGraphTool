#include "stdafx.h"
#include "raaDataEngineLayoutManager/raaDataEngineLayout.h"
#include "raaLayoutButton.moc"
#include "raaLayoutButton.h"

raaLayoutButton* raaLayoutButton::sm_pActive = 0;
unsigned int raaLayoutButton::sm_uiCount=0;

raaLayoutButton::raaLayoutButton(QString sName, raaDataEngineLayout *pLayout, QWidget *pParent) : QPushButton(sName, pParent)
{
	m_sName = sName;
	m_pLayout = pLayout;

	connect(this, SIGNAL(pressed()), this, SLOT(enacted()));
}

raaLayoutButton::~raaLayoutButton()
{
}

void raaLayoutButton::tick()
{
	if(sm_uiCount && sm_pActive)
	{
		float fProg = ((float)(30 - (--sm_uiCount))) / 30.0f;
		sm_pActive->m_pLayout->apply(fProg);
		sm_pActive->setText(QString("%1::%2").arg(sm_pActive->m_sName).arg(sm_uiCount));
		if (!sm_uiCount)
		{
			sm_pActive->m_pLayout->finish();
			sm_pActive->setText(sm_pActive->m_sName);
		}
	}
}

void raaLayoutButton::enacted()
{
	if (sm_pActive) sm_pActive->m_pLayout->finish();
	sm_pActive = this;
	raaDataEngineLayout::raaParameters p;
	p["dist"] = "40.0";
	if (sm_pActive)
	{
		sm_pActive->m_pLayout->start(p);
		sm_uiCount = 30;
	}
}
