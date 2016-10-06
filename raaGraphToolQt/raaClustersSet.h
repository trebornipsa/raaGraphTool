#pragma once

#include <vector>
#include <map>

#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Material>
#include <osg/Geometry>
#include <osg/Switch>
#include <raaQTOSGWidget/raaOSGMouseOver.h>

#include <raaUtilities/raaVector.h>
#include <raaUtilities/raaMutex.h>

class raaDataModel;
class raaBound;
class raaOSGDataNode;

typedef std::vector<raaVector> raaVectors;
typedef std::vector<raaVectors> raaVectorSet;
typedef std::vector<raaOSGDataNode*> raaVNodes;
typedef std::vector<osg::Geometry*>raaGeometries;
typedef std::map<unsigned int, raaVNodes> raaClusters;
typedef std::map<bool, raaClusters> raaClustersBuffer;

class raaClustersSet: public raaOSGMouseOverPayload, public osg::Referenced
{
public:
	raaClustersSet(raaDataModel *pModel);
	virtual ~raaClustersSet();

	osg::Group *clusterGroup();
	void setModel(raaDataModel *pModel);

	void genClusterGeom();

	void drawCluster(bool bDraw);

	unsigned int numClusters();

	std::string getDescription(osg::Drawable *pDrawable);

protected:
	osg::Group *m_pBase;
	osg::Geode *m_pGeode;
	osg::Switch *m_pSwitch;
	osg::MatrixTransform *m_pMT;

	bool m_bDraw;
	unsigned int m_uiNumClusters;

	raaDataModel *m_pModel;

	static osg::Material *sm_pNormalMaterial;
	static osg::Material *sm_pHighlightMaterial;

	raaGeometries m_vGeoms;
	raaClustersBuffer m_mClusters;
	bool m_bClusterBuffer;
};

