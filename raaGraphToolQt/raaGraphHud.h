#pragma once
#include <map>
#include <string>

#include <osg/Drawable>

class raaGraphPlot;

typedef std::map<std::string, raaGraphPlot*> raaPlots;

class raaGraphHud : public osg::Drawable::DrawCallback
{
public:
	raaGraphHud();
	virtual ~raaGraphHud();
	virtual void drawImplementation(osg::RenderInfo &, const osg::Drawable *) const;

	osg::Group* root();

	void resize(int iX, int iY, int iWidth, int iHeight);

	unsigned int toPanelX(float fX) const;
	unsigned int toGraphX(float fX) const;
	unsigned int toPanelY(float fY) const;
	unsigned int toGraphY(float fY) const;

	float fromPanelX(unsigned int uiX);
	float fromPanelY(unsigned int uiY);
	float fromGraphX(unsigned int uiX);
	float fromGraphY(unsigned int uiY);

	bool addPlot(std::string sName, raaGraphPlot *pPlot);
	void removePlot(std::string sName);

protected:
	int m_iWidth;
	int m_iPanelHeight;
	int m_iHeight;
	osg::Group *m_pGroup;
	osg::Geode *m_pGeode;
	osg::MatrixTransform *m_pTransform;
	osg::Projection *m_pProjection;
	raaPlots m_mPlots;
};

