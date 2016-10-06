#include "stdafx.h"
#include <iostream>
#include "raaWindowEventListener.h"


raaWindowEventListener::raaWindowEventListener(bool bActive)
{
	m_bActive = bActive;
}

raaWindowEventListener::~raaWindowEventListener()
{
}

void raaWindowEventListener::active(bool bActive)
{
	m_bActive = bActive;
}

bool raaWindowEventListener::isActive()
{
	return m_bActive;
}

bool raaWindowEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (m_pListener && m_pListener->isActive())
	{
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::RESIZE:
			m_pListener->resize(ea.getWindowWidth(), ea.getWindowHeight());
			break;
		case osgGA::GUIEventAdapter::MOVE:
			m_pListener->move(ea.getX(), ea.getY());
			break;
		case osgGA::GUIEventAdapter::FRAME:
			m_pListener->frame(ea, aa);
			break;
		}
	}
	return false;
}

raaWindowEventHandler::raaWindowEventHandler(raaWindowEventListener *pListener)
{
	m_pListener = pListener;
}


raaWindowEventHandler::~raaWindowEventHandler()
{
}
