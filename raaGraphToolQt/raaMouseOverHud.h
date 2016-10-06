#pragma once

#include <string>
#include <list>

#include <osg/Drawable>
#include <osgText/Text>
#include <osg/Material>

typedef std::list<std::string> raaOverNames;

//class raaMouseOverHud : public osg::Drawable::DrawCallback
class raaMouseOverHud
{
public:
	raaMouseOverHud();
	virtual ~raaMouseOverHud();

	virtual void drawImplementation(osg::RenderInfo&, const osg::Drawable*) const;
	void resize(int iX, int iY, int iWidth, int iHeight);

	void setPos(int iX, int iY);

	void setNames(std::string &sNames);
	void setCluster(std::string &sCluster);

	osg::Group* root();
	void setState(bool bOn);
	bool state();

	void setTextScale(float fScale);
protected:
	int m_iWidth;
	int m_iPanelHeight;
	int m_iHeight;
	osg::Switch *m_pSwitch;
	osg::Group *m_pGroup;
	osg::Geode *m_pGeode;
	osg::MatrixTransform *m_pTransform;
	osg::MatrixTransform *m_pTransform2;
	osg::MatrixTransform *m_pScale;
	osg::Projection *m_pProjection;
	osgText::Text *m_pText;
	static osg::Material *sm_pTextMat;
	bool m_bOn;
	raaOverNames m_lNames;
};

