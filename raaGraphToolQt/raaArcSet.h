#pragma once

#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/Drawable>

#include <raaDataEngine/raaDataModel.h>

class raaCull : public osg::Drawable::CullCallback
{
public:
	virtual bool cull(osg::NodeVisitor *nv, osg::Drawable *drawable, osg::RenderInfo *renderInfor) const
	{
		return false;
	}
};

class raaBound : public osg::Drawable::ComputeBoundingBoxCallback
{
public:
	raaBound()
	{
		m_vCentre.set(0.0f, 0.0f, 0.0f, 0.0f);
		m_fRadius = 3.0f;
	}

	virtual osg::BoundingBox computeBound(const osg::Drawable&) const
	{
		osg::BoundingBox b;
		b.set(m_vCentre[0] - m_fRadius, m_vCentre[1] - m_fRadius, m_vCentre[2] - m_fRadius, m_vCentre[0] + m_fRadius, m_vCentre[1] + m_fRadius, m_vCentre[2] + m_fRadius);
		return b;
	}

	raaVector m_vCentre;
	float m_fRadius;
};

class raaArcSet : public osg::Drawable::DrawCallback
{
public:
	raaArcSet(raaDataModel *pModel);
	virtual ~raaArcSet();

	osg::Group *arcGroup();

	void setModel(raaDataModel *pModel);

	virtual void drawImplementation(osg::RenderInfo &, const osg::Drawable *) const;

	void updateBound();

	void showInactive(bool bShow);
	void arcTransp(float fVal);

protected:
	osg::Group *m_pBase;
	osg::Geode *m_pGeode;
	osg::MatrixTransform *m_pMT;
	osg::ShapeDrawable *m_pSD;
	bool m_bShowInactive;

	raaDataModel *m_pModel;
	raaBound *m_pBound;
	float m_fTransp;
};

