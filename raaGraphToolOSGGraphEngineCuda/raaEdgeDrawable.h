#pragma once

#include <osg/Drawable>

class raaCudaGraph;


class raaEdgeDrawable: public osg::Drawable
{
public:
	raaEdgeDrawable(raaCudaGraph *pGraph);

	void draw(osg::RenderInfo &renderInfo) const;

	virtual osg::Object *cloneType() const;
	virtual osg::Object *clone(const osg::CopyOp&) const;
	virtual void drawImplementation(osg::RenderInfo&) const;

protected:
	virtual ~raaEdgeDrawable(void);

	raaCudaGraph *m_pGraph;

};

