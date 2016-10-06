#pragma once
#include <windows.h>
#include <osgGA/GUIEventHandler>

class raaWindowEventListener
{
	friend class raaWindowEventHandler;
public:
	raaWindowEventListener(bool bActive=true);
	virtual ~raaWindowEventListener();
	void active(bool bActive);
	bool isActive();
protected:
	virtual void resize(int iWidth, int iHeight)=0;
	virtual void move(int iX, int iY) = 0;
	virtual void frame(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&) = 0;
	bool m_bActive;
};


class raaWindowEventHandler : public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&);
	raaWindowEventHandler(raaWindowEventListener *pListener);
	virtual ~raaWindowEventHandler();
protected:
	raaWindowEventListener *m_pListener;

};

