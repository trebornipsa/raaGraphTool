#pragma once

#include <map>
#include <windows.h>

#include <QtWidgets\QMainWindow>
#include <QtWidgets\QSplitter>
#include <QtGui/QStandardItemModel>

#include <raaQTOSGWidget/raaOSGMouseOver.h>

#include "raaWindowEventListener.h"
#include "raaGraphInterfaceQt.h"
#include "raaMouseOverHud.h"

class raaOSGDataNode;
class raaArcSet;
class raaClustersSet;
class raaDataArc;
class raaLayerModel;
class raaNodeInfoModel;
class raaArcInfoModel;
class raaGraphHud;
class raaGraphPlot;

typedef std::map<int, raaOSGDataNode*> raaPajekNodeMap;
typedef std::map<std::string, raaOSGDataNode*> raaNodeMap;
typedef std::list<raaOSGDataNode*> raaNodeList;
typedef std::vector<std::string> raaStringVector;
typedef std::vector<raaDataArc*>raaArcVector;
typedef std::list < std::string> raaNodeNames;
typedef std::list<osg::Referenced*>raaOvers;

class raaDataDic;

//class raaGraphInterface : public QMainWindow, public Ui::raaGraphInterfaceQt, public raaOSGMouseOver, public raaWindowEventListener
class raaGraphInterface : public QMainWindow, public Ui::raaGraphInterfaceQt, public raaWindowEventListener
{
	Q_OBJECT
public:
	const static unsigned int csm_uiArcWeightsAsSpringStrength = 0;
	const static unsigned int csm_uiArcWeightsAsSpringLength = 1;

	raaGraphInterface();
	virtual ~raaGraphInterface();

public slots:
	void loadPajek();
	void loadMoArm();
	void loadRaaArm();
	void loadDecisionTree();
	void loadDecisionTrees();
	void loadMultiYearDecisionTrees();
	void loadAliMalware();
	void saveGraph();
	void loadGraph();

	void loadTest();
	void solve();
	void resetView();
	void solveToggle(int);
	void clusterToggle(int);
	void discardArc(int);
	void solveOnce();
	void clusterEPSChanged(double);
	void solveIntervalChanged(double);
	void solveDampingChanged(double);
	void clusterMinChanged(int);
	void itemClicked(const QModelIndex&);
	void glResized(int,int);
	void clusterClicked(const QModelIndex&);
	void arcAsSpringStrength(bool);
	void arcAsSpringLength(bool);
	void arcNodeSqrForce(int);
	void arcCentreSqrForce(int);
	void mouseOver(int);
	void mouseTextOn(int);
	void showInactive(int);
	void nodeSize(int);
	void textSize(int);
	void arcTransp(int);

	void moveToActiveDisplay(raaOSGDataNode *pNode);
	void moveToInactiveDisplay(raaOSGDataNode *pNode);
protected:
	raaOSGDataNode *addNode(std::string sName, std::string sGroup);

	virtual void resize(int iWidth, int iHeight);
	virtual void move(int iX, int iY);
	virtual void frame(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&);


	std::string nameToGroup(std::string sName);
	    
	std::string nodeNamesToString(raaNodeNames &nn);

	void loadDecisonTreeFile(QString sFile);
	void loadNewDecisonTreeFile(QString sFile);
	void loadDecisonTreeYearFile(QString sFile);
	void updateInfo(bool bForce = false);
	void populateClusterInfo();

	int m_iSelectedCluster;

	raaPajekNodeMap m_mPajekMap;
	void addPajekVertex(std::string sString);
	void addPajekArc(std::string sString);

	QString refineNameString(QString s);

	float m_fPajekScale;
	raaArcSet *m_pArcSet;
	raaClustersSet *m_pClustersSet;

	bool m_bSolve;
	bool m_bCluster;

	float m_fEPS;
	unsigned int m_uiMinClusterSize;

	QTimer m_Timer;
	float m_fSolveInterval;
	float m_fDamping;

	raaVector m_vRes2Pos;
	raaVector m_vRes1Pos;
	raaVector m_vResPos;

	raaVector m_vRes2Step;
	raaVector m_vRes1Step;
	raaVector m_vResStep;

	float m_fMaxRandPos;
	raaLayerModel *m_pLayerModel;
	raaNodeInfoModel *m_pNodeInfoModel;
	raaArcInfoModel *m_pArcInfoModel;
	raaGraphHud *m_pGraphHud;
	raaMouseOverHud *m_pMouseOverHud;
	raaGraphPlot *m_pEnergyPlot;
	raaGraphPlot *m_pClusterPlot;

	QStandardItemModel *m_pClusterModel;
	QItemSelectionModel *m_pClusterSelectionModel;
	QStandardItemModel *m_pClusteredModel;

	raaVector m_vSelectedCentre;
	raaVector m_vSelectedSize;
	bool m_bNewClusterSelected;
	bool m_bClusterSelected;

	unsigned int m_uiArcWeightMap;
	int m_aiMousePos[2];
	bool m_bMouseOverActive;

	raaDataDic *m_pDataDic;

	osg::Switch *m_pActiveNodesSwitch;
	osg::Switch *m_pInactiveNodesSwitch;
};

