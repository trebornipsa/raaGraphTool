#include "stdafx.h"
#include <windows.h>
#include <gl/gl.h>
#include <osg/Projection>
#include <osg/Switch>
#include <osg/MatrixTransform>

#include "raaMouseOverHud.h"
#include <iostream>

osg::Material *raaMouseOverHud::sm_pTextMat=0;

raaMouseOverHud::raaMouseOverHud()
{
	m_iWidth = 1024;
	m_iHeight = 768;
	m_iPanelHeight = m_iWidth >> 2;
	m_pSwitch = new osg::Switch();


	m_pGroup = new osg::Group();
	m_pGroup->ref();
	m_pGroup->setName("MouseHud");


	m_pGeode = new osg::Geode();
//	m_pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

	if(!sm_pTextMat)
	{
		sm_pTextMat = new osg::Material();
		sm_pTextMat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.3f, 0.3f, 0.0f, 1.0f));
		sm_pTextMat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.8f, 0.8f, 0.0f, 1.0f));
		sm_pTextMat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
	}

	m_pGeode->getOrCreateStateSet()->setAttributeAndModes(sm_pTextMat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	m_pText = new osgText::Text();
	m_pText->setText("");

	m_pProjection = new osg::Projection();
	m_pProjection->setMatrix(osg::Matrix::ortho2D(0, 1024, 0, 768));

	m_pTransform = new osg::MatrixTransform();
	m_pTransform->setMatrix(osg::Matrix::identity());
	m_pTransform->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	m_pTransform2 = new osg::MatrixTransform();


	osg::Matrixf m;
	m.makeTranslate(10.0f, 20.0f, 0.0f);
	m_pTransform2->setMatrix(m);

	m_pScale = new osg::MatrixTransform();
	osg::Matrixf mScale;
	mScale.makeScale(osg::Vec3f(1.0f, 1.0f, 1.0f));
	m_pScale->setMatrix(mScale);

	m_pSwitch->addChild(m_pProjection);
	m_pProjection->addChild(m_pTransform);
	m_pTransform->addChild(m_pTransform2);
	m_pTransform2->addChild(m_pScale);
	m_pScale->addChild(m_pGeode);

/*
	osg::Drawable *pDrawable = new osg::Drawable();
	pDrawable->setDrawCallback(this);

	pDrawable->setSupportsDisplayList(false);

	m_pGeode->addDrawable(pDrawable);
*/

	m_pGeode->addDrawable(m_pText);

	m_pGroup->addChild(m_pSwitch);
}


raaMouseOverHud::~raaMouseOverHud()
{
	m_pGroup->unref();
}

void raaMouseOverHud::drawImplementation(osg::RenderInfo&, const osg::Drawable*) const
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
/*
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(100.0f, 0.0f);
	glVertex2f(100.0f, 200.0f);
	glVertex2f(0.0f, 200.0f);
	glEnd();
*/

	glPopAttrib();
}

void raaMouseOverHud::resize(int iX, int iY, int iWidth, int iHeight)
{
	std::cout << "Dim -> " << iX << "   " << iY << "   " << iWidth << "   " << iHeight << std::endl;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
//	m_iPanelHeight = m_iWidth >> 2;
	m_pProjection->setMatrix(osg::Matrix::ortho2D(0, iWidth, 0, iHeight));
}

void raaMouseOverHud::setPos(int iX, int iY)
{
//	std::cout << "\tPos -> " << iX << "   " << iY << std::endl;

	osg::Matrixf m;
	m.makeTranslate(iX, iY, 0.0f);
	m_pTransform2->setMatrix(m);
}

void raaMouseOverHud::setNames(std::string &sNames)
{
	if(m_pText)
	{
		m_pText->setText(sNames);
	}
}

void raaMouseOverHud::setCluster(std::string& sCluster)
{
	if(m_pText)
	{
		std::string sNames = m_pText->getText().createUTF8EncodedString();
		sNames += sCluster;
		m_pText->setText(sNames);
	}
}

osg::Group* raaMouseOverHud::root()
{
	return m_pGroup;
}

void raaMouseOverHud::setState(bool bOn)
{
	m_bOn = bOn;

	if (m_bOn) m_pSwitch->setAllChildrenOn();
	else m_pSwitch->setAllChildrenOff();
}

bool raaMouseOverHud::state()
{
	return m_bOn;
}

void raaMouseOverHud::setTextScale(float fScale)
{
	if(m_pScale)
	{
		osg::Matrixf m;
		m.makeScale(osg::Vec3f(fScale, fScale, fScale));
		m_pScale->setMatrix(m);
	}
}
