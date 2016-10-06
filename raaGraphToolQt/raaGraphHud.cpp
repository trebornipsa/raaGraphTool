#include "stdafx.h"

#include <iostream>

#include <windows.h>
#include <GL/gl.h>


#include <osg/Group>
#include <osg/Geode>
#include <osg/Projection>
#include <osgText/Text>
#include <osg/MatrixTransform>

#include "raaGraphPlot.h"

#include "raaGraphHud.h"


raaGraphHud::raaGraphHud()
{
	m_iWidth = 1024;
	m_iHeight = 768;
	m_iPanelHeight = m_iWidth >> 2;
	m_pGroup = new osg::Group();
	m_pGroup->ref();
	m_pGroup->setName("Hud");

	m_pGeode = new osg::Geode();

	osgText::Text *pText = new osgText::Text();

	m_pProjection = new osg::Projection();
	m_pProjection->setMatrix(osg::Matrix::ortho2D(0, 1024, 0, 768));

	m_pTransform = new osg::MatrixTransform();
	m_pTransform->setMatrix(osg::Matrix::identity());
	m_pTransform->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	m_pGroup->addChild(m_pProjection);
	m_pProjection->addChild(m_pTransform);
	m_pTransform->addChild(m_pGeode);

	osg::Drawable *pDrawable = new osg::Drawable();
	pDrawable->setDrawCallback(this);

	pDrawable->setSupportsDisplayList(false);

	m_pGeode->addDrawable(pDrawable);
}

raaGraphHud::~raaGraphHud()
{
	if (m_pGroup) m_pGroup->unref();
}

void raaGraphHud::drawImplementation(osg::RenderInfo&, const osg::Drawable*) const
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	
	glColor4f(1.0f, 1.0f, 0.9f, 0.8f);
	glBegin(GL_LINES);
	glVertex3i(toGraphX(0.0f), toGraphY(0.0f), 0.0f);
	glVertex3i(toGraphX(0.0f), toGraphY(1.0f), 0.0f);
	glVertex3i(toGraphX(0.0f), toGraphY(0.0f), 0.0f);
	glVertex3i(toGraphX(1.0f), toGraphY(0.0f), 0.0f);
	glEnd();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor4f(1.0f, 1.0f, 0.9f, 0.6f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 129024);
	glBegin(GL_LINES);
	glVertex3i(toGraphX(0.2f), toGraphY(0.0f), 0.0f);
	glVertex3i(toGraphX(0.2f), toGraphY(1.0f), 0.0f);
	glVertex3i(toGraphX(0.4f), toGraphY(0.0f), 0.0f);
	glVertex3i(toGraphX(0.4f), toGraphY(1.0f), 0.0f);
	glVertex3i(toGraphX(0.6f), toGraphY(0.0f), 0.0f);
	glVertex3i(toGraphX(0.6f), toGraphY(1.0f), 0.0f);
	glVertex3i(toGraphX(0.8f), toGraphY(0.0f), 0.0f);
	glVertex3i(toGraphX(0.8f), toGraphY(1.0f), 0.0f);
	glVertex3i(toGraphX(1.0f), toGraphY(0.0f), 0.0f);
	glVertex3i(toGraphX(1.0f), toGraphY(1.0f), 0.0f);

	glVertex3i(toGraphX(0.0f), toGraphY(0.25f), 0.0f);
	glVertex3i(toGraphX(1.0f), toGraphY(0.25f), 0.0f);
	glVertex3i(toGraphX(0.0f), toGraphY(0.5f), 0.0f);
	glVertex3i(toGraphX(1.0f), toGraphY(0.5f), 0.0f);
	glVertex3i(toGraphX(0.0f), toGraphY(0.75f), 0.0f);
	glVertex3i(toGraphX(1.0f), toGraphY(0.75f), 0.0f);
	glEnd();
	glPopAttrib();

	for (raaPlots::const_iterator it = m_mPlots.begin(); it != m_mPlots.end();it++)
	{
		raaGraphPlot *pGP = it->second;

		if (pGP)
		{
			float fSep = 1.0f / (float)pGP->maxPoints();
			float fPos = 0.0f;

			glColor4fv(pGP->colour().get());


			glBegin(GL_LINE_STRIP);
			for (raaPlotData::const_iterator cit = pGP->normData().begin(); cit != pGP->normData().end(); cit++, fPos += fSep)
				glVertex3f(toGraphX(fPos), toGraphY((*cit)), 0.0f);

			glEnd();
		}
	}


	glPopAttrib();
}

osg::Group* raaGraphHud::root()
{
	return m_pGroup;
}

void raaGraphHud::resize(int iX, int iY, int iWidth, int iHeight)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iPanelHeight = m_iWidth >> 2;
	m_pProjection->setMatrix(osg::Matrix::ortho2D(0, iWidth, 0, iHeight));
}

unsigned raaGraphHud::toPanelX(float fX) const
{
	return (unsigned)(fX*m_iWidth);
}

unsigned raaGraphHud::toGraphX(float fX) const
{
	return ((unsigned)(fX*(m_iWidth-20)))+10;
}

unsigned raaGraphHud::toPanelY(float fY) const
{
	return (unsigned)(fY*m_iPanelHeight);
}

unsigned raaGraphHud::toGraphY(float fY) const
{
	return ((unsigned)(fY*(m_iPanelHeight - 20))) + 10;
}

float raaGraphHud::fromPanelX(unsigned uiX)
{
	return (float)(((float)uiX) / ((float)m_iWidth));
}

float raaGraphHud::fromPanelY(unsigned uiY)
{
	return (float)(((float)uiY) / ((float)m_iPanelHeight));
}

float raaGraphHud::fromGraphX(unsigned uiX)
{
	return (float)(((float)uiX-10) / ((float)m_iWidth-20));
}

float raaGraphHud::fromGraphY(unsigned uiY)
{
	return (float)(((float)uiY) / ((float)m_iPanelHeight-20));
}

bool raaGraphHud::addPlot(std::string sName, raaGraphPlot *pPlot)
{
	if(sName.length() && pPlot)
	{
		if(m_mPlots.find(sName)==m_mPlots.end())
		{
			m_mPlots[sName] = pPlot;
			return true;
		}
	}
	return false;
}

void raaGraphHud::removePlot(std::string sName)
{
	if (sName.length() && m_mPlots.find(sName) != m_mPlots.end())
	{
		m_mPlots.erase(sName);
	}
}
