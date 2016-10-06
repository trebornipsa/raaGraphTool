#include "stdafx.h"

#include <windows.h>
#include <gl/gl.h>

#include <osg/Material>

#include "raaArcSet.h"


raaArcSet::raaArcSet(raaDataModel *pModel)
{
	m_pModel = pModel;
	m_bShowInactive = false;
	m_fTransp = 0.5f;

	m_pBound = new raaBound();

	m_pBase = new osg::Group();
	m_pBase->ref();
	m_pBase->setName("raaArcSet");

	m_pMT = new osg::MatrixTransform();
	m_pGeode = new osg::Geode();
	m_pSD =new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), 1.0f));

	osg::Material *pMat = new osg::Material();
	pMat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.3f, 0.3f, 0.3f, 1.0f));
	pMat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.8f, 0.8f, 0.8f, 1.0f));
	pMat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.9f, 0.9f, 0.9f, 1.0f));
	pMat->setAlpha(osg::Material::FRONT_AND_BACK, 0.3f);

	m_pBase->addChild(m_pMT);
	m_pMT->addChild(m_pGeode);
	m_pGeode->addDrawable(m_pSD);
	m_pSD->setDrawCallback(this);
	m_pSD->setCullCallback(new raaCull());
	m_pSD->setUseDisplayList(false);
	m_pSD->setDataVariance(osg::Object::DYNAMIC);
	m_pSD->setComputeBoundingBoxCallback(m_pBound);
	m_pGeode->getOrCreateStateSet()->setAttributeAndModes(pMat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
}

raaArcSet::~raaArcSet()
{
	if (m_pBase) m_pBase->unref();
	if (m_pBound) delete m_pBound;

}

osg::Group* raaArcSet::arcGroup()
{
	return m_pBase;
}

void raaArcSet::setModel(raaDataModel* pModel)
{
	m_pModel = pModel;
}

void raaArcSet::drawImplementation(osg::RenderInfo&, const osg::Drawable*) const
{
	if(m_pModel)
	{
		const raaDataArcMap arcs = m_pModel->arcs();

		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBegin(GL_LINES);

		for (raaDataArcMap::const_iterator cit = arcs.begin(); cit != arcs.end();cit++)
		{
			raaDataArc *pArc = cit->second;
			raaVector vCentre = pArc->centre();

			if (pArc->active()) glColor4f(pArc->colour()[0], pArc->colour()[1], pArc->colour()[2], m_fTransp);
			else if(m_bShowInactive) glColor4f(0.8f, 0.8f, 0.8f, m_fTransp*0.3f);

			for (raaDataNodes::const_iterator ait = pArc->nodes().begin(); ait != pArc->nodes().end(); ait++)
			{
				if (pArc->active() || m_bShowInactive)
				{
					glVertex3fv(vCentre.get());
					glVertex3fv((*ait)->position().get());
				}
			}
		}

		glEnd();

		glPopAttrib();
	}
}

void raaArcSet::updateBound()
{
	if(m_pModel && m_pSD)
	{
		osg::Vec3f vCen(m_pModel->centre()[0], m_pModel->centre()[1], m_pModel->centre()[2]);


		static_cast<osg::Sphere*>(m_pSD->getShape())->setCenter(vCen);
		static_cast<osg::Sphere*>(m_pSD->getShape())->setRadius(m_pModel->boundRadius());

		if(m_pBound)
		{
			m_pBound->m_vCentre = m_pModel->centre();
			m_pBound->m_fRadius = m_pModel->boundRadius();
		}

	}
}

void raaArcSet::arcTransp(float fVal)
{
	m_fTransp = fVal;
}

void raaArcSet::showInactive(bool bShow)
{
	m_bShowInactive = bShow;
}
