#include "stdafx.h"

#include <windows.h>

#include <fstream>
#include <sstream>

#include <QtWidgets/QFileDialog>
#include <QtSQL/QSqlDatabase>
#include <QtSQL/QSqlQuery>
#include <QtSQL/QSqlError>

#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtXml/QDomElement>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QCoreApplication>
#include <QtCore/QAbstractItemModel>

#include <raaUtilities/raaUtilities.h>
#include <raaUtilities/raaMatrix.h>

#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaSpringSolver.h>
#include <raaDataEngine/raaDefaultCluster.h>
#include <raaDataEngine/raaDataArc.h>
#include <raaDataEngine/raaDataLayer.h>

#include <raaDataEngineLayoutManager/raaDataEngineLayoutManager.h>

#include "raaArcSet.h"
#include "raaClustersSet.h"
#include "raaOSGDataNode.h"
#include "raaOSGDataNodeHandler.h"
#include "raaGraphHud.h"
#include "raaGraphPlot.h"

//#include "raaHistory.h"
#include "raaWindowEventListener.h"
#include "raaLayoutButton.h"
#include "raaLayerModel.h"
#include "raaNodeInfoModel.h"
#include "raaNodeInfoModel.h"
#include "raaArcInfoModel.h"
#include "raaDataDic.h"
#include "raaGraphInterface.h"
#include "raaGraphInterface.moc"
#include <iostream>

raaGraphInterface::raaGraphInterface()
{
	m_bMouseOverActive = false;
	raaUtilities::init();
//	raaHistory::start(".bdHistory");
	m_fMaxRandPos = 100.0f;
	m_fPajekScale = 1.0f;
	m_pArcSet = new raaArcSet(0);
	m_pClustersSet = new raaClustersSet(0);
	m_bSolve = false;
	m_bCluster = false;
	m_fEPS = 2.0f;
	m_uiMinClusterSize = 4; 
	m_fSolveInterval = 0.03;
	m_fDamping = 0.97f;
	m_pLayerModel = 0;
	m_pNodeInfoModel = 0;
	m_pArcInfoModel = 0;
	m_uiArcWeightMap = csm_uiArcWeightsAsSpringStrength;
	m_bClusterSelected = false;
	m_bNewClusterSelected = false;

	raaDataEngine::instance()->addSolver("springs", new raaSpringSolver());
	raaDataEngine::instance()->addClusterer("default", new raaDefaultCluster());
	raaDataEngineLayoutManager::start();
	setupUi(this);

	m_pDataDic=new raaDataDic("C:\\robbie\\data\\DecisionTrees\\TotalDataDic-forRob.csv", "C:\\robbie\\data\\DecisionTrees\\raaCodes.txt");
	      
//	m_pOversDoc = new QTextDocument();
//	mouse_text->setDocument(m_pOversDoc);

	for (raaDataEngineLayouts::const_iterator it = raaDataEngineLayoutManager::instance()->layouts().begin(); it != raaDataEngineLayoutManager::instance()->layouts().end(); it++)
	{
		raaLayoutButton *pButton = new raaLayoutButton((*it).first.c_str(), (*it).second);
		layout_buttons_frame->layout()->addWidget(pButton);
	}
	((QBoxLayout*)layout_buttons_frame->layout())->addStretch();

	de_cluster_eps_spin->setValue(m_fEPS);
	de_cluster_min_spin->setValue(m_uiMinClusterSize);
	de_solve_interval_spin->setValue(m_fSolveInterval);
	de_solve_damping_spin->setValue((1.0f - m_fDamping)*100.0f);

	m_pGraphHud = new raaGraphHud();
	m_pEnergyPlot = new raaGraphPlot("Energy", raaVector(1.0f, 1.0f, 0.1f, 0.3f));
	m_pClusterPlot = new raaGraphPlot("Clusters", raaVector(1.0f, 0.3f,1.3f, 0.5f));
	m_pGraphHud->addPlot("Energy", m_pEnergyPlot);
	m_pGraphHud->addPlot("Clusters", m_pClusterPlot);

	m_pMouseOverHud = new raaMouseOverHud();

	m_pClusterModel = new QStandardItemModel(1, 10);
	m_pClusterSelectionModel = new QItemSelectionModel(m_pClusterModel);
	m_pClusteredModel = new QStandardItemModel(1, 10);
	info_cluster_column_view->setModel(m_pClusterModel);
	info_cluster_column_view->setSelectionModel(m_pClusterSelectionModel);
	info_cluster_node_view->setModel(m_pClusteredModel);

	m_iSelectedCluster = -1;

	connect(actionLoad_Pajek, SIGNAL(triggered()), SLOT(loadPajek()));
	connect(actionLoad_Mo_ARM, SIGNAL(triggered()), SLOT(loadMoArm()));
	connect(actionLoad_Raa_ARM, SIGNAL(triggered()), SLOT(loadRaaArm()));
	connect(actionLoad_Decision_Tree, SIGNAL(triggered()), SLOT(loadDecisionTree()));
	connect(actionLoad_Decision_Trees, SIGNAL(triggered()), SLOT(loadDecisionTrees()));
	connect(actionLoad_MultiYear_Decision_Trees, SIGNAL(triggered()), SLOT(loadMultiYearDecisionTrees()));
	connect(actionLoad_Ali_Malware, SIGNAL(triggered()), SLOT(loadAliMalware()));

	connect(actionLoad_Test, SIGNAL(triggered()), SLOT(loadTest()));
	connect(actionSave_Graph, SIGNAL(triggered()), SLOT(saveGraph()));
	connect(actionLoad_Graph, SIGNAL(triggered()), SLOT(loadGraph()));
	connect(&m_Timer, SIGNAL(timeout()), SLOT(solve()));
	connect(de_solve_check, SIGNAL(stateChanged(int)), SLOT(solveToggle(int)));
	connect(de_cluster_check, SIGNAL(stateChanged(int)), SLOT(clusterToggle(int)));
	connect(de_discard_check, SIGNAL(stateChanged(int)), SLOT(discardArc(int)));
	connect(de_solve_button, SIGNAL(pressed()), SLOT(solveOnce()));
	connect(de_reset_view_button, SIGNAL(pressed()), SLOT(resetView()));
	connect(de_cluster_eps_spin, SIGNAL(valueChanged(double)), SLOT(clusterEPSChanged(double)));
	connect(de_solve_interval_spin, SIGNAL(valueChanged(double)), SLOT(solveIntervalChanged(double)));
	connect(de_solve_damping_spin, SIGNAL(valueChanged(double)), SLOT(solveDampingChanged(double)));
	connect(de_cluster_min_spin, SIGNAL(valueChanged(int)), SLOT(clusterMinChanged(int)));
//	connect(gl_window, SIGNAL(resized(int,int)), SLOT(glResized(int,int)));
	connect(info_cluster_column_view, SIGNAL(clicked(const QModelIndex&)), SLOT(clusterClicked(const QModelIndex&)));
	connect(lo_aw_as_sw_radio, SIGNAL(toggled(bool)), SLOT(arcAsSpringStrength(bool)));
	connect(lo_aw_as_sl_radio, SIGNAL(toggled(bool)), SLOT(arcAsSpringLength(bool)));

	connect(de_arc_cen_sqt_check, SIGNAL(stateChanged(int)), SLOT(arcCentreSqrForce(int)));
	connect(de_arc_node_sqr_check, SIGNAL(stateChanged(int)), SLOT(arcNodeSqrForce(int)));
	connect(mouse_over_check, SIGNAL(stateChanged(int)), SLOT(mouseOver(int)));
	connect(mouse_screen_text_check, SIGNAL(stateChanged(int)), SLOT(mouseTextOn(int)));
	connect(de_show_inactive_check, SIGNAL(stateChanged(int)), SLOT(showInactive(int)));
	connect(de_node_size_slider, SIGNAL(valueChanged(int)), SLOT(nodeSize(int)));
	connect(de_text_size_slider, SIGNAL(valueChanged(int)), SLOT(textSize(int)));
	connect(de_arc_transp_slider, SIGNAL(valueChanged(int)), SLOT(arcTransp(int))); 

//	layer_tree_view->setModel(new raaLayerModel());
		
	m_pActiveNodesSwitch = new osg::Switch();
	m_pActiveNodesSwitch->setAllChildrenOn();
	m_pActiveNodesSwitch->ref();

	m_pInactiveNodesSwitch = new osg::Switch();
	m_pInactiveNodesSwitch->setAllChildrenOff();
	m_pInactiveNodesSwitch->ref();


	gl_window->addToTranspScene(0, m_pArcSet->arcGroup());
//	gl_window->addToScene(0, m_pArcSet->arcGroup());
	gl_window->addToTranspScene(0, m_pClustersSet->clusterGroup());
	gl_window->addHandler(0, new raaOSGDataNodeHandler());
	gl_window->addToScene(0, m_pGraphHud->root());
	gl_window->addToScene(0, m_pMouseOverHud->root());
	gl_window->addHandler(0, new raaWindowEventHandler(this));

	gl_window->addToScene(0, m_pActiveNodesSwitch);
	gl_window->addToScene(0, m_pInactiveNodesSwitch);

//	gl_window->addHandler(0, new raaWindowEventHandler(m_pClustersSet));
//	gl_window->addHandler(0, this);
	m_Timer.start(20);
}

raaGraphInterface::~raaGraphInterface()
{
	if (m_pActiveNodesSwitch) m_pActiveNodesSwitch->unref();
	if (m_pInactiveNodesSwitch) m_pInactiveNodesSwitch->unref();
}


void raaGraphInterface::loadPajek()
{
	QString sFile = QFileDialog::getOpenFileName(this, QString("Load Pajek File"), QString("C:/robbie/data/"));

	float fIdealLen = lo_ideal_arc_length_spin->value();

	if (sFile.length())
	{
		std::ifstream in(sFile.toStdString());
		std::string sLine;
		unsigned int iMode = 0;

		if (in.is_open())
		{
			m_mPajekMap.clear();
			raaDataEngine::instance()->addModel(sFile.toStdString());
			m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
			m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());
	
			unsigned int uiNumVerticies = 0;
			while(!in.eof())
			{
				std::getline(in, sLine);
				if (sLine.length() > 3)
				{
					if (sLine.find("*Vertices") != std::string::npos)
					{
						iMode = 1;
						char *pLine = (char*)_alloca(sizeof(char)*sLine.length() + 1);
						sprintf(pLine, "%s", sLine.c_str());

						char *pPos = strtok(pLine, " ");
						uiNumVerticies = (pPos = strtok(0, " ")) ? atoi(pPos) : 0;
					}
					else if (sLine.find("*Arcs") != std::string::npos)
					{
						iMode = 2;
						
					}
					else
					{
						switch (iMode)
						{
						case 1:
							addPajekVertex(sLine);
							break;
						case 2:
							addPajekArc(sLine);
							break;
						default:
							break;
						}
					}
				}
			}
			if(raaDataEngine::instance()->currentModel()->arcs().size()>5 && lo_normalise_arcs_check->isChecked())
				raaDataEngine::instance()->currentModel()->normaliseArcWeights();
		}
	}
}

void raaGraphInterface::loadMoArm()
{
	QString sFile = QFileDialog::getOpenFileName(this, QString("Load Mo ARM File"), QString("C:/robbie/data/"));
	float fIdealLen = lo_ideal_arc_length_spin->value();
	m_fMaxRandPos = lo_max_rand_pos_spin->value();

	if (sFile.length())
	{
		raaDataEngine::instance()->addModel(sFile.toStdString());
		m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
		m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());

		std::ifstream in(sFile.toStdString());
		std::string sLine;
		unsigned int iMode = 0;

		raaNodeMap mNodes;

		//		std::string sRelations, sEC, sC, sSup, sLift, sTCount, sRule, sLHS, sRHS, sRI1, sRI2, sRI3, sRIndex, sTrans;

		if (in.is_open())
		{
			while (!in.eof())
			{
				in >> sLine;

				if (sLine.length())
				{
					QString s(sLine.c_str());
					QStringList sv = s.split(QString(","));

//					std::cout << sv.size() << std::endl;

					QString sN1, sN2;
					float fW;

					unsigned int uiIndex=0;
					for (QStringList::iterator it = sv.begin(); it != sv.end(); it++, uiIndex++)
					{
//						std::cout << (*it).toStdString() << std::endl;
						switch(uiIndex)
						{
						case 7:
							sN1 = (*it);
							break;
						case 8:
							sN2 = (*it);
							break;
						case 2:
							fW = (*it).toFloat();
							break;
						}
					}

					raaOSGDataNode *pDN1 = 0, *pDN2 = 0;

					if (sN2.length() && sN1.length())
					{
						std::cout << sN2.toStdString() << " -> " << sN1.toStdString() << std::endl;


						if (mNodes.find(sN1.toStdString()) == mNodes.end())
						{
							//						std::cout << "Add Node -> " << sN1.toStdString() << std::endl;
							pDN1 = new raaOSGDataNode(sN1.toStdString(), this);
							pDN1->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
							raaDataEngine::instance()->currentModel()->addNode(pDN1);
							mNodes[sN1.toStdString()] = pDN1;
							m_pActiveNodesSwitch->addChild(pDN1->node());
						}
						else
						{
							pDN1 = mNodes[sN1.toStdString()];

						}

						if (mNodes.find(sN2.toStdString()) == mNodes.end())
						{
							pDN2 = new raaOSGDataNode(sN2.toStdString(), this);
							//						std::cout << "Add Node -> " << sN2.toStdString() << std::endl;
							pDN2->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
							raaDataEngine::instance()->currentModel()->addNode(pDN2);
							mNodes[sN2.toStdString()] = pDN2;
							m_pActiveNodesSwitch->addChild(pDN2->node());
						}
						else
						{
							pDN2 = mNodes[sN2.toStdString()];
						}

//						if (pDN1 && pDN2 && pDN1 != pDN2 && !raaDataEngine::instance()->currentModel()->arcExisits(pDN1, pDN2))
							if (pDN1 && pDN2 && pDN1 != pDN2)
							{
							raaDataArc *pArc = new raaDataArc("");
							pArc->addNode(pDN1);
							pArc->addNode(pDN2);
							pArc->setWeight(fW / 100.0f);
							pArc->setIdealLength(fIdealLen);

							raaDataEngine::instance()->currentModel()->addArc(pArc);
						}
					}
				}
			}

			in.close();
			if (lo_normalise_arcs_check->isChecked())
				raaDataEngine::instance()->currentModel()->normaliseArcWeights();

		}
	}
}

void raaGraphInterface::loadRaaArm()
{
	QString sFile = QFileDialog::getOpenFileName(this, QString("Load RAA ARM File"), QString("C:/robbie/data/"));
	float fIdealLen = lo_ideal_arc_length_spin->value();
	m_fMaxRandPos = lo_max_rand_pos_spin->value();

	if (sFile.length())
	{
		raaDataEngine::instance()->addModel(sFile.toStdString());
		m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
		m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());

		std::ifstream in(sFile.toStdString());
		std::string sLine;
		unsigned int iMode = 0;

		raaNodeMap mNodes;

		if (in.is_open())
		{
			while (!in.eof())
			{
				in >> sLine;

				if (sLine.length())
				{
					QString s(sLine.c_str());
					QStringList sv = s.split(QString(","));

					raaNodeList lNodes1, lNodes2;
//					float fW1, fW2;

					QString sN1, sN2;
					float fW;

					unsigned int uiIndex = 0;
					unsigned int iMode=0;
					for (QStringList::iterator it = sv.begin(); it != sv.end(); it++, uiIndex++)
					{

						switch (uiIndex)
						{
						case 7:
							sN1 = (*it);
							break;
						case 8:
							sN2 = (*it);
							break;
						case 2:
							fW = (*it).toFloat();
							break;
						}
					}

					raaOSGDataNode *pDN1 = 0, *pDN2 = 0;

					if (sN2.length() && sN1.length())
					{
						std::cout << sN2.toStdString() << " -> " << sN1.toStdString() << std::endl;


						if (mNodes.find(sN1.toStdString()) == mNodes.end())
						{
							//						std::cout << "Add Node -> " << sN1.toStdString() << std::endl;
							pDN1 = new raaOSGDataNode(sN1.toStdString(), this);
							pDN1->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
							raaDataEngine::instance()->currentModel()->addNode(pDN1);
							mNodes[sN1.toStdString()] = pDN1;
							m_pActiveNodesSwitch->addChild(pDN1->node());
						}
						else
						{
							pDN1 = mNodes[sN1.toStdString()];

						}

						if (mNodes.find(sN2.toStdString()) == mNodes.end())
						{
							pDN2 = new raaOSGDataNode(sN2.toStdString(), this);
							//						std::cout << "Add Node -> " << sN2.toStdString() << std::endl;
							pDN2->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
							raaDataEngine::instance()->currentModel()->addNode(pDN2);
							mNodes[sN2.toStdString()] = pDN2;
							m_pActiveNodesSwitch->addChild(pDN2->node());
						}
						else
						{
							pDN2 = mNodes[sN2.toStdString()];
						}

						//						if (pDN1 && pDN2 && pDN1 != pDN2 && !raaDataEngine::instance()->currentModel()->arcExisits(pDN1, pDN2))
						if (pDN1 && pDN2 && pDN1 != pDN2)
						{
							raaDataArc *pArc = new raaDataArc("");
							pArc->addNode(pDN1);
							pArc->addNode(pDN2);
							pArc->setWeight(fW / 100.0f);
							pArc->setIdealLength(fIdealLen);

							raaDataEngine::instance()->currentModel()->addArc(pArc);
						}
					}
				}
			}

			in.close();
			if (lo_normalise_arcs_check->isChecked())
				raaDataEngine::instance()->currentModel()->normaliseArcWeights();

		}
	}
}

void raaGraphInterface::loadDecisionTree()
{
	QString sFile = QFileDialog::getOpenFileName(this, QString("Load RAA ARM File"), QString("C:/robbie/data/"));

	m_fMaxRandPos = lo_max_rand_pos_spin->value();

	m_vRes1Pos.set(2.0f*m_fMaxRandPos, 0.0f, 0.0f);
	m_vRes2Pos.set(-2.0f*m_fMaxRandPos, 0.0f, 0.0f);
	m_vResPos.set(0.0f, 0.0f, -m_fMaxRandPos, 0.0f);

	m_vRes1Step.set(0.0f, 0.0f, 3.0f, 0.0f);
	m_vRes2Step.set(0.0f, 0.0f, 3.0f, 0.0f);
	m_vResStep.set(0.0f, 3.0f, 0.0f, 0.0f);

	raaDataEngine::instance()->addModel(sFile.toStdString());
	m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
	m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());

	loadDecisonTreeFile(sFile);
}

void raaGraphInterface::loadDecisionTrees()
{
	QString sDir = QFileDialog::getExistingDirectory(this, QString("Load Decision Tree Dir"), QString("C:/robbie/data/"));

	m_fMaxRandPos = lo_max_rand_pos_spin->value();

	m_vRes1Pos.set(2.0f*m_fMaxRandPos, 0.0f, 0.0f);
	m_vRes2Pos.set(-2.0f*m_fMaxRandPos, 0.0f, 0.0f);
	m_vResPos.set(0.0f, 0.0f, -m_fMaxRandPos, 0.0f);

	m_vRes1Step.set(0.0f, 0.0f, 3.0f, 0.0f);
	m_vRes2Step.set(0.0f, 0.0f, 3.0f, 0.0f);
	m_vResStep.set(0.0f, 3.0f, 0.0f, 0.0f);

	QDir d(sDir);
	QStringList sNameFilters;
	sNameFilters.push_back("*.txt");
	QFileInfoList il = d.entryInfoList(sNameFilters, QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

	raaDataEngine::instance()->addModel(sDir.toStdString());
	m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
	m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());

	if (m_pDataDic)
	{
		for (raaTable::const_iterator cit = m_pDataDic->table().begin(); cit != m_pDataDic->table().end(); cit++)
		{
			raaOSGDataNode *pNode = addNode(cit->first.toStdString(), "placeholder");
			pNode->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
			raaDataEngine::instance()->currentModel()->addNode(pNode);
//			m_pInactiveNodesSwitch->addChild(pNode->node());
			raaDataEngine::instance()->currentModel()->addGroupNode(cit->first.toLower().toStdString(), pNode);
			pNode->activityUnref();
		}
	}

	for (QFileInfoList::iterator it = il.begin(); it!=il.end();it++)
	{
		loadDecisonTreeFile(it->absoluteFilePath());
	}

	if (!m_pLayerModel)
	{
		layer_tree_view->setModel(m_pLayerModel=new raaLayerModel());
		layer_tree_view->setRootIsDecorated(true);
		layer_tree_view->setAllColumnsShowFocus(true);
		connect(layer_tree_view, SIGNAL(clicked(const QModelIndex&)), SLOT(itemClicked(const QModelIndex&)));
	}


	if (!m_pNodeInfoModel) info_node_table_view->setModel(m_pNodeInfoModel = new raaNodeInfoModel());
	if (!m_pArcInfoModel) info_arc_table_view->setModel(m_pArcInfoModel = new raaArcInfoModel());
}

void raaGraphInterface::loadMultiYearDecisionTrees()
{
	QString sFile = QFileDialog::getOpenFileName(this, QString("Load RAA ARM Dir"), QString("C:/robbie/data/"));

	QDir dTopDir(sFile);

	std::ifstream fMeta(sFile.toStdString());

	m_fMaxRandPos = lo_max_rand_pos_spin->value();

	m_vRes1Pos.set(2.0f*m_fMaxRandPos, 0.0f, 0.0f);
	m_vRes2Pos.set(-2.0f*m_fMaxRandPos, 0.0f, 0.0f);
	m_vResPos.set(0.0f, 0.0f, -m_fMaxRandPos, 0.0f);

	m_vRes1Step.set(0.0f, 0.0f, 3.0f, 0.0f);
	m_vRes2Step.set(0.0f, 0.0f, 3.0f, 0.0f);
	m_vResStep.set(0.0f, 3.0f, 0.0f, 0.0f);

	raaDataModel *pStartModel = 0;

	if(fMeta.is_open())
	{
		while (!fMeta.eof())
		{
			std::string sName, sPath;
			float fTransition = 10.0f;
			fMeta >> sName >> sPath >> fTransition;
		
			if(sName.length() && sPath.length())
			{
				std::cout << "Year -> " << sName << "   " << sPath << "   " << fTransition << std::endl;

				QDir d(QString("%1/%2").arg(dTopDir.absolutePath()).arg(sPath.c_str()));
				QStringList sNameFilters;
				sNameFilters.push_back("*.txt");
				QFileInfoList il = d.entryInfoList(sNameFilters, QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

				raaDataEngine::instance()->addModel(sName, fTransition);
				if (!pStartModel) pStartModel = raaDataEngine::instance()->currentModel();

				m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
				m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());

				for (QFileInfoList::iterator it = il.begin(); it != il.end(); it++)
				{
					loadDecisonTreeFile(it->absoluteFilePath());
				}
			}
		}
		std::cout << "End Meta" << std::endl;
		fMeta.close();


		raaDataEngine::instance()->makeModelCurrent(pStartModel->name());

		if (!m_pLayerModel)
		{
			layer_tree_view->setModel(m_pLayerModel = new raaLayerModel());
			layer_tree_view->setRootIsDecorated(true);
			layer_tree_view->setAllColumnsShowFocus(true);
			connect(layer_tree_view, SIGNAL(clicked(const QModelIndex&)), SLOT(itemClicked(const QModelIndex&)));
		}

		if (!m_pNodeInfoModel) info_node_table_view->setModel(m_pNodeInfoModel = new raaNodeInfoModel());
		if (!m_pArcInfoModel) info_arc_table_view->setModel(m_pArcInfoModel = new raaArcInfoModel());

	}
	return;
/*

	QDir d(sDir);
	QStringList sNameFilters;
	sNameFilters.push_back("*.txt");
	QFileInfoList il = d.entryInfoList(sNameFilters, QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

	raaDataEngine::instance()->addModel(sDir.toStdString());
	m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
	m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());


	for (QFileInfoList::iterator it = il.begin(); it != il.end(); it++)
	{
		loadDecisonTreeFile(it->absoluteFilePath());
	}

	if (!m_pLayerModel)
	{
		layer_tree_view->setModel(m_pLayerModel = new raaLayerModel());
		layer_tree_view->setRootIsDecorated(true);
		layer_tree_view->setAllColumnsShowFocus(true);
		connect(layer_tree_view, SIGNAL(clicked(const QModelIndex&)), SLOT(itemClicked(const QModelIndex&)));
	}

	if (!m_pNodeInfoModel) info_node_table_view->setModel(m_pNodeInfoModel = new raaNodeInfoModel());
	if (!m_pArcInfoModel) info_arc_table_view->setModel(m_pArcInfoModel = new raaArcInfoModel());
*/
}

void raaGraphInterface::loadAliMalware()
{
	QString sFile = QFileDialog::getOpenFileName(this, QString("Load Ali Malware File"), QString("C:/robbie/data/"));

	m_fMaxRandPos = lo_max_rand_pos_spin->value();

	m_vRes1Pos.set(2.0f*m_fMaxRandPos, 0.0f, 0.0f);
	m_vRes2Pos.set(-2.0f*m_fMaxRandPos, 0.0f, 0.0f);
	m_vResPos.set(0.0f, 0.0f, -m_fMaxRandPos, 0.0f);

	m_vRes1Step.set(0.0f, 0.0f, 3.0f, 0.0f);
	m_vRes2Step.set(0.0f, 0.0f, 3.0f, 0.0f);
	m_vResStep.set(0.0f, 3.0f, 0.0f, 0.0f);

	raaDataEngine::instance()->addModel(sFile.toStdString());
	m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
	m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());

	if (sFile.length())
	{
		QFileInfo f(sFile);
		float fIdealLen = lo_ideal_arc_length_spin->value();

		std::string sGroup = f.baseName().toStdString();

		raaOSGDataNode *pNode0 = new raaOSGDataNode("Distribution Site", this, sGroup);
		pNode0->setPosition(m_vRes1Pos);
		pNode0->addToGroup("Result::1");
		pNode0->pin(true);
		m_vRes1Pos += m_vRes1Step;
		raaDataEngine::instance()->currentModel()->addNode(pNode0);
		m_pActiveNodesSwitch->addChild(pNode0->node());


		raaOSGDataNode *pNode1 = new raaOSGDataNode("Payment Site", this, sGroup);
		pNode1->setPosition(m_vRes2Pos);
		pNode1->addToGroup("Result::2");
		pNode1->pin(true);
		m_vRes2Pos += m_vRes2Step;
		raaDataEngine::instance()->currentModel()->addNode(pNode1);
		m_pActiveNodesSwitch->addChild(pNode1->node());


		std::ifstream in(sFile.toStdString());
		std::string sLine;

//		raaArcVector vArcs;
//		unsigned int uiDepth;
//		raaNodeNames lNames, lNodes;
		if (in.is_open())
		{
			while (!in.eof())
			{
				std::getline(in, sLine);
				QString s(sLine.c_str());
				if (sLine.length() && s.contains(','))
				{
					if (s.length())
					{

						QStringList ss = s.split(",");
						QStringList::iterator it = ss.begin();

						for (QStringList::iterator i = ss.begin(); i !=ss.end(); i++) (*i).remove("\"");

						// process time
						QString sDateTime = (*it); it++;

						// process source
						raaOSGDataNode *pSourceNode = addNode((*it).toStdString(), sGroup); it++;

						//process malware
						QString sMalware = (*it);
						it++;

						// process domain
						raaOSGDataNode *pDomainNode = addNode((*it).toStdString(), sGroup); it++;

						// process page
						QString sPage = (*it); it++;

						// process status
						QString sStatus = (*it); it++;

						//process company
						raaOSGDataNode *pCompanyNode = addNode((*it).toStdString(), sGroup); it++;
						std::cout << "Company -> " << pCompanyNode->name() << std::endl;


						// process ip
						raaOSGDataNode *pIPNode = addNode((*it).toStdString(), sGroup); it++;

						// process port
						raaOSGDataNode *pPortNode = addNode((*it).toStdString(), sGroup);
						it++;

						// process country
						raaOSGDataNode *pCountryNode = addNode((*it).toStdString(), sGroup);
						it++;

						raaDataLayer *pLayer = 0;

						if (raaDataEngine::instance()->currentModel()->hasLayer(sMalware.toStdString()))
						{
							pLayer = raaDataEngine::instance()->currentModel()->layer(sMalware.toStdString());
						}
						else
						{
							pLayer = new raaDataLayer(sMalware.toStdString());
							pLayer->refActive();
							raaDataEngine::instance()->currentModel()->addLayer(pLayer);
						}

						raaNodeNames lNames;
						lNames.push_back(sDateTime.toStdString());
						lNames.push_back(pSourceNode->name());
						lNames.push_back(sMalware.toStdString());
						lNames.push_back(pDomainNode->name());
						lNames.push_back(pCompanyNode->name());
						lNames.push_back(pCountryNode->name());

						raaDataArc *pArc = new raaDataArc(nodeNamesToString(lNames));
						raaDataEngine::instance()->currentModel()->addArc(pArc, pLayer);
						pArc->addNode(pSourceNode);
						pArc->addNode(pDomainNode);
						pArc->addNode(pCompanyNode);
						pArc->addNode(pIPNode);
						pArc->addNode(pPortNode);
						pArc->addNode(pCountryNode);
						pArc->setIdealLength(10.0f);
						pArc->setWeight(1.0);


					}
				}
			}
		}
		in.close();
/*
		if (lo_normalise_arcs_check->isChecked())
		{

			switch (m_uiArcWeightMap)
			{
			case csm_uiArcWeightsAsSpringStrength:
				pLayer->normaliseArcWeights();
				break;
			case csm_uiArcWeightsAsSpringLength:
				pLayer->normaliseArcLengths(fIdealLen, fIdealLen*2.0f);
				break;
			}
		}
*/
	}
}

void raaGraphInterface::saveGraph()
{
	QString sFile = QFileDialog::getSaveFileName(this);

	if(sFile.length() && raaDataEngine::instance()->currentModel())
	{
		QDomDocument  doc("raaDataEngine");


		QDomElement dModel = doc.createElement("raaDataModel");
		dModel.setAttribute("name", raaDataEngine::instance()->currentModel()->name().c_str());
		doc.appendChild(dModel);

		QDomElement dNodes = doc.createElement("raaDataNodes");
		dModel.appendChild(dNodes);

		QDomElement dLayers = doc.createElement("raaDataLayers");
		dModel.appendChild(dLayers);

		QDomElement dArcs = doc.createElement("raaDataArcs");
		dModel.appendChild(dArcs);

		for (raaDataNodeMap::const_iterator it = raaDataEngine::instance()->currentModel()->nodes().begin(); it != raaDataEngine::instance()->currentModel()->nodes().end();it++)
		{
			QDomElement dNode = doc.createElement("raaNode");

			raaDataNode *pNode = it->second;

			dNode.setAttribute(QString("name"), QString(pNode->name().c_str()));
			dNode.setAttribute(QString("mass"), pNode->mass());
			dNode.setAttribute(QString("pinned"), ((raaOSGDataNode*)pNode)->pinned());

			QDomElement dPos = doc.createElement("position");
			dPos.setAttribute("x", pNode->position()[0]);
			dPos.setAttribute("y", pNode->position()[1]);
			dPos.setAttribute("z", pNode->position()[2]);

			dNode.appendChild(dPos);
			dNodes.appendChild(dNode);
		}

		for (raaDataLayerMap::iterator it = raaDataEngine::instance()->currentModel()->layers().begin(); it != raaDataEngine::instance()->currentModel()->layers().end(); it++)
		{
			raaDataLayer *pLayer = it->second;

			QDomElement dLayer = doc.createElement("raaDataLayer");

			dLayer.setAttribute(QString("name"), pLayer->name().c_str());
			dLayer.setAttribute(QString("active"), pLayer->active());

			QDomElement dLayerColour = doc.createElement("colour");
			dLayerColour.setAttribute("r", pLayer->colour()[0]);
			dLayerColour.setAttribute("g", pLayer->colour()[1]);
			dLayerColour.setAttribute("b", pLayer->colour()[2]);
			dLayerColour.setAttribute("a", pLayer->colour()[3]);
			dLayer.appendChild(dLayerColour);

			dLayers.appendChild(dLayer);
			
			for (unsigned int i = 0; i < pLayer->arcs().size();i++)
			{
				raaDataArc *pArc = pLayer->arcs()[i];
				QDomElement dArc = doc.createElement("raaDataArc");
				dArc.setAttribute("name", pArc->name().c_str());
				dArc.setAttribute("weight", pArc->weight());
				dArc.setAttribute("ideal", pArc->idealLength());
				dArc.setAttribute("layer", pLayer->name().c_str());

				for (int j = 0; j < pArc->nodes().size();j++)
				{
					raaDataNode *pArcNode = pArc->nodes()[j];
					QDomElement dArcNode = doc.createElement("raaArcNode");
					dArcNode.setAttribute(QString("name"), pArcNode->name().c_str());
					dArc.appendChild(dArcNode);
				}
				dArcs.appendChild(dArc);
			}
		}



		QFile file(sFile);
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		QString sDoc = doc.toString();

		QTextStream textStream(&file);
		textStream << sDoc;
//		doc.save(textStream, 0);
		file.close();

	}

}

void raaGraphInterface::loadGraph()
{
	QString sFile = QFileDialog::getOpenFileName(this);

	if(sFile.length())
	{
		QDomDocument doc("raaDataEngine");

		QFile file(sFile);

		if(file.open(QIODevice::ReadOnly))
		{
			doc.setContent(&file);
			file.close();

			QDomElement dModel = doc.documentElement();
	
			if(!dModel.isNull())
			{
				std::cout << "Model -> " << dModel.nodeName().toStdString() << std::endl;

				if(dModel.hasAttribute("name"))
				{
					std::string sModelName = dModel.attribute("name").toStdString();
					raaDataEngine::instance()->addModel(sModelName);
					m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
					m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());

					for (QDomNode dChildNode = dModel.firstChild(); !dChildNode.isNull();dChildNode=dChildNode.nextSibling())
					{
						QDomElement dChildElement = dChildNode.toElement();

						if(dChildNode.nodeName()=="raaDataNodes")
						{
							for (QDomNode dNodeNode = dChildNode.firstChild(); !dNodeNode.isNull();dNodeNode=dNodeNode.nextSibling())
							{
								QDomElement dNode = dNodeNode.toElement();

								if(dNode.hasAttribute("name"))
								{
									std::string sNodeName = dNode.attribute("name").toStdString();
									raaOSGDataNode *pNode = new raaOSGDataNode(sNodeName, this);

									if (dNode.hasAttribute("pinned")) pNode->pin(dNode.attribute("pinned").toInt());
									if (dNode.hasAttribute("mass")) pNode->setMass(dNode.attribute("mass").toFloat());

									float fX = 0.0f, fY = 0.0f, fZ = 0.0f;

									if(dNode.hasChildNodes())
									{
										for (QDomNode dPosNode = dNode.firstChild(); !dPosNode.isNull();dPosNode=dPosNode.nextSibling())
										{
											QDomElement dPos = dPosNode.toElement();

											if(dPos.nodeName()=="position")
											{
												if (dPos.hasAttribute("x")) fX = dPos.attribute("x").toFloat();
												if (dPos.hasAttribute("y")) fY = dPos.attribute("y").toFloat();
												if (dPos.hasAttribute("z")) fZ = dPos.attribute("z").toFloat();
											}
										}
									}

									pNode->setPosition(raaVector(fX, fY, fZ, 1.0f));
									raaDataEngine::instance()->currentModel()->addNode(pNode);
									m_pActiveNodesSwitch->addChild(pNode->node());
								}
							}
						}
						else if(dChildNode.nodeName()=="raaDataLayers")
						{
							for (QDomElement dLayer = dChildNode.firstChild().toElement(); !dLayer.isNull();dLayer=dLayer.nextSibling().toElement())
							{
								if(dLayer.hasAttribute("name"))
								{
									raaDataLayer *pLayer = new raaDataLayer(dLayer.attribute("name").toStdString());
									if (dLayer.hasAttribute("active") && dLayer.attribute("active").toInt()) pLayer->refActive();  

									QDomElement dColour = dLayer.firstChildElement("colour");
									float r=0.8f, g=0.0f, b=0.0f, a=0.1f;

									if (dColour.hasAttribute("r")) r = dColour.attribute("r").toFloat();
									if (dColour.hasAttribute("g")) g = dColour.attribute("g").toFloat();
									if (dColour.hasAttribute("b")) b = dColour.attribute("b").toFloat();
									if (dColour.hasAttribute("a")) a = dColour.attribute("a").toFloat();

									pLayer->setColour(raaVector(r, g, b, a));

									raaDataEngine::instance()->currentModel()->addLayer(pLayer);
								}
							}
/*
							QDomElement dLayer = dChildNode.toElement();

							if(dLayer.hasAttribute("name"))
							{
								std::string sLayer = dLayer.attribute("name").toStdString();

								if(sLayer=="default")
								{
									for (QDomElement dArc = dLayer.firstChild().toElement(); !dArc.isNull(); dArc = dArc.nextSibling().toElement())
									{
										if (dArc.hasAttribute("name"))
										{

											raaDataArc *pArc = new raaDataArc(dArc.attribute("name").toStdString());
											if (dArc.hasAttribute("ideal")) pArc->setIdealLength(dArc.attribute("ideal").toFloat());
											if (dArc.hasAttribute("weight")) pArc->setWeight(dArc.attribute("weight").toFloat());
											raaDataEngine::instance()->currentModel()->addArc(pArc);

											for (QDomElement dArcNode = dArc.firstChild().toElement(); !dArcNode.isNull(); dArcNode = dArcNode.nextSibling().toElement()) if (dArcNode.hasAttribute("name")) pArc->addNode(raaDataEngine::instance()->currentModel()->node(dArcNode.attribute("name").toStdString()));


										}
									}

								}
								else
								{
									raaDataLayer *pLayer = new raaDataLayer(sLayer);
									bool bActive = true;
									if (dLayer.hasAttribute("active")) bActive = dLayer.attribute("active").toInt();
									if (bActive) pLayer->makeActive(); else pLayer->makeInactive();

									raaDataEngine::instance()->currentModel()->addLayer(pLayer);

									for (QDomElement dArc = dLayer.firstChild().toElement(); !dArc.isNull();dArc=dArc.nextSibling().toElement())
									{
										if (dArc.hasAttribute("name"))
										{

											raaDataArc *pArc = new raaDataArc(dArc.attribute("name").toStdString());
											if (dArc.hasAttribute("ideal")) pArc->setIdealLength(dArc.attribute("ideal").toFloat());
											if (dArc.hasAttribute("weight")) pArc->setWeight(dArc.attribute("weight").toFloat());
											raaDataEngine::instance()->currentModel()->addArc(pArc, pLayer);

											for (QDomElement dArcNode = dArc.firstChild().toElement(); !dArcNode.isNull(); dArcNode = dArcNode.nextSibling().toElement()) if (dArcNode.hasAttribute("name")) pArc->addNode(raaDataEngine::instance()->currentModel()->node(dArcNode.attribute("name").toStdString()));

										}
									}
								}
								
							}*/
						}
						else if(dChildNode.nodeName()=="raaDataArcs")
						{
							for (QDomElement dArc = dChildNode.firstChild().toElement(); !dArc.isNull(); dArc = dArc.nextSibling().toElement())
							{
								if (dArc.hasAttribute("name") && dArc.hasAttribute("layer"))
								{
									raaDataArc *pArc = new raaDataArc(dArc.attribute("name").toStdString());

									if (dArc.hasAttribute("weight")) pArc->setWeight(dArc.attribute("weight").toFloat());
									if (dArc.hasAttribute("ideal")) pArc->setIdealLength(dArc.attribute("ideal").toFloat());

									for (QDomElement dArcNode = dArc.firstChild().toElement(); !dArcNode.isNull();dArcNode=dArcNode.nextSibling().toElement())
									{
										if(dArcNode.hasAttribute("name"))
											pArc->addNode(raaDataEngine::instance()->currentModel()->getNode(dArcNode.attribute("name").toStdString()));
									}

									raaDataEngine::instance()->currentModel()->addArc(pArc, dArc.attribute("layer").toStdString());
								}
							}
						}
					}
				}
			}
		}
	}
}

void raaGraphInterface::loadTest()
{
	raaDataEngine::instance()->addModel("Test");
	m_pArcSet->setModel(raaDataEngine::instance()->currentModel());
	m_pClustersSet->setModel(raaDataEngine::instance()->currentModel());
	float fIdealLen = lo_ideal_arc_length_spin->value();



	raaOSGDataNode *pN1 = new raaOSGDataNode("N1", this);
	raaOSGDataNode *pN2 = new raaOSGDataNode("N2", this);
	raaOSGDataNode *pN3 = new raaOSGDataNode("N3", this);
	raaOSGDataNode *pN4 = new raaOSGDataNode("N4", this);

	pN1->setPosition(raaVector(-5.0f, 0.0f, 5.0f, 1.0f));
	pN2->setPosition(raaVector(5.0f, 0.0f, 5.0f, 1.0f));
	pN3->setPosition(raaVector(0.0f, 0.0f, -5.0f, 1.0f));
	pN3->setPosition(raaVector(0.0f, 5.0f, 0.0f, 1.0f));

	raaDataEngine::instance()->currentModel()->addNode(pN1);
	raaDataEngine::instance()->currentModel()->addNode(pN2);
	raaDataEngine::instance()->currentModel()->addNode(pN3);
	raaDataEngine::instance()->currentModel()->addNode(pN4);

	m_pActiveNodesSwitch->addChild(pN1->node());
	m_pActiveNodesSwitch->addChild(pN2->node());
	m_pActiveNodesSwitch->addChild(pN3->node());
	m_pActiveNodesSwitch->addChild(pN4->node());

	raaDataArc *pArc1 = new raaDataArc("tesArc1");
	pArc1->addNode(pN1);
	pArc1->addNode(pN2);
	pArc1->addNode(pN3);
	pArc1->setWeight(logf(1.0f));
	pArc1->setIdealLength(fIdealLen);

	raaDataEngine::instance()->currentModel()->addArc(pArc1);

	raaDataArc *pArc2 = new raaDataArc("tesArc2");
	pArc2->addNode(pN4);
	pArc2->addNode(pN2);
	pArc2->addNode(pN3);
	pArc2->setWeight(logf(20000.0f));
	pArc2->setIdealLength(fIdealLen);
	raaDataEngine::instance()->currentModel()->addArc(pArc2);

	raaDataArc *pArc3 = new raaDataArc("tesArc3");
	pArc3->addNode(pN1);
	pArc3->addNode(pN2);
	pArc3->addNode(pN4);
	pArc3->setWeight(logf(1000.0f));
	pArc3->setIdealLength(fIdealLen);
	raaDataEngine::instance()->currentModel()->addArc(pArc3);

	if (lo_normalise_arcs_check->isChecked())
		raaDataEngine::instance()->currentModel()->normaliseArcWeights();

}

void raaGraphInterface::solve()
{
	raaLayoutButton::tick();
	if (m_bSolve)
	{
//		raaHistory::instance()->addFrame();
//		raaHistory::instance()->prepareNodePositionsUpdate();
		raaDataEngine::instance()->solve(m_fSolveInterval, m_fDamping);
//		raaHistory::instance()->commitNodePositionsUpdate();
		if (m_pArcSet) m_pArcSet->updateBound();



		de_solve_energy_label->setText(QString("Energy: %1").arg((double)raaDataEngine::instance()->currentModel()->energy(), 8));
		if (m_pEnergyPlot) m_pEnergyPlot->addPoint(raaDataEngine::instance()->currentModel()->energy());
		updateInfo();
	}

	if(m_bCluster)
	{
		raaDataEngine::instance()->cluster(m_fEPS, m_uiMinClusterSize);
		m_pClustersSet->genClusterGeom();
		populateClusterInfo();
	}

	if (m_pClusterPlot) m_pClusterPlot->addPoint((int)m_pClustersSet->numClusters());
}

void raaGraphInterface::resetView()
{
	gl_window->resetView(0);
}

void raaGraphInterface::solveToggle(int iState)
{
	if (iState != Qt::Unchecked) m_bSolve = true;
	else m_bSolve = false;
}

void raaGraphInterface::clusterToggle(int iState)
{
	if (iState != Qt::Unchecked) m_bCluster = true;
	else m_bCluster = false;

	if (m_pClustersSet) m_pClustersSet->drawCluster(m_bCluster);
}

void raaGraphInterface::discardArc(int iState)
{
	if (iState != Qt::Unchecked) de_discard_spin->setEnabled(true);
	else de_discard_spin->setEnabled(false);
}

void raaGraphInterface::solveOnce()
{
	raaDataEngine::instance()->solve(m_fSolveInterval, m_fDamping);
	if (m_pArcSet) m_pArcSet->updateBound();

	if (m_bCluster)
	{
		raaDataEngine::instance()->cluster(m_fEPS, m_uiMinClusterSize);
		m_pClustersSet->genClusterGeom();
	}

	de_solve_energy_label->setText(QString("Energy: %1").arg((double)raaDataEngine::instance()->currentModel()->energy(), 8));
}

void raaGraphInterface::clusterEPSChanged(double d)
{
	m_fEPS = d;
}

void raaGraphInterface::solveIntervalChanged(double f)
{
	m_fSolveInterval = f;

	m_Timer.setInterval(1000.0f*m_fSolveInterval);
}

void raaGraphInterface::solveDampingChanged(double f)
{
	m_fDamping = (1.0f - (f / 100.0f));
}

void raaGraphInterface::clusterMinChanged(int i)
{
	m_uiMinClusterSize = i;
}

void raaGraphInterface::itemClicked(const QModelIndex& index)
{
	if(m_pLayerModel)
	{
		m_pLayerModel->itemClicked(index);
		layer_tree_view->update(index);
//		info_node_table_view->update();
		updateInfo(true);
	}
}

void raaGraphInterface::glResized(int iWidth, int iHeight)
{
	if (m_pGraphHud) m_pGraphHud->resize(0, 0, gl_window->width(), gl_window->height());
	if (m_pMouseOverHud) m_pMouseOverHud->resize(0, 0, gl_window->width(), gl_window->height());
}

void raaGraphInterface::clusterClicked(const QModelIndex& index)
{
	if (index.isValid())
	{
		if (m_iSelectedCluster == index.row()) m_iSelectedCluster = -1;
		else	m_iSelectedCluster = index.row();
	}
	else m_iSelectedCluster = -1;

//	m_pClustersSet->highlight(m_iSelectedCluster);
	m_bNewClusterSelected = true;
}

void raaGraphInterface::arcAsSpringStrength(bool bState)
{
	if (bState) m_uiArcWeightMap = csm_uiArcWeightsAsSpringStrength;
}

void raaGraphInterface::arcAsSpringLength(bool bState)
{
	if (bState) m_uiArcWeightMap = csm_uiArcWeightsAsSpringLength;
}

void raaGraphInterface::arcNodeSqrForce(int iState)
{
	if (iState != Qt::Unchecked) raaSpringSolver::useSqrForce(true);
	else raaSpringSolver::useSqrForce(false);
}

void raaGraphInterface::arcCentreSqrForce(int iState)
{
	if (iState != Qt::Unchecked) raaDataArc::useArcCenreSqrForce(true);
	else raaDataArc::useArcCenreSqrForce(false);
}

void raaGraphInterface::mouseOver(int iVal)
{
	if (iVal == Qt::Checked) m_bMouseOverActive = true;
	else m_bMouseOverActive = false;
}

void raaGraphInterface::mouseTextOn(int iVal)
{
	if(iVal==Qt::Checked)
	{
		for(raaDataNodeMap::const_iterator it=raaDataEngine::instance()->currentModel()->nodes().begin(); it!=raaDataEngine::instance()->currentModel()->nodes().end();it++)
		{
			((raaOSGDataNode*)(it->second))->setTextOn(true);
		}
	}
	else
	{
		for (raaDataNodeMap::const_iterator it = raaDataEngine::instance()->currentModel()->nodes().begin(); it != raaDataEngine::instance()->currentModel()->nodes().end(); it++)
		{
			((raaOSGDataNode*)(it->second))->setTextOn(false);
		}
	}
}

void raaGraphInterface::showInactive(int iVal)
{
	if(iVal==Qt::Checked)
	{
		if (m_pInactiveNodesSwitch) m_pInactiveNodesSwitch->setAllChildrenOn();
		if (m_pArcSet) m_pArcSet->showInactive(true);
	}
	else
	{
		if (m_pArcSet) m_pArcSet->showInactive(false);
		if(m_pInactiveNodesSwitch) m_pInactiveNodesSwitch->setAllChildrenOff();
	}
}

void raaGraphInterface::nodeSize(int iVal)
{
	float fVal = ((float)iVal) / 1000.0f;

	raaOSGDataNode::setRadius(fVal);
}

void raaGraphInterface::textSize(int iVal)
{
	float fVal = ((float)iVal) / 500.0f;

	if (m_pMouseOverHud) m_pMouseOverHud->setTextScale(fVal);
}

void raaGraphInterface::arcTransp(int iVal)
{
	float fVal = ((float)iVal) / 1000.0f;
	if (m_pArcSet) m_pArcSet->arcTransp(fVal);
}

void raaGraphInterface::moveToActiveDisplay(raaOSGDataNode* pNode)
{
	if(pNode && m_pInactiveNodesSwitch->containsNode(pNode->node()))
	{
		if(!m_pActiveNodesSwitch->containsNode(pNode->node()))
		{
			m_pActiveNodesSwitch->addChild(pNode->node());
			m_pInactiveNodesSwitch->removeChild(pNode->node());
		}
	}
}

void raaGraphInterface::moveToInactiveDisplay(raaOSGDataNode* pNode)
{
	if (pNode && m_pActiveNodesSwitch->containsNode(pNode->node()))
	{
		if (!m_pInactiveNodesSwitch->containsNode(pNode->node()))
		{
			m_pInactiveNodesSwitch->addChild(pNode->node());
			m_pActiveNodesSwitch->removeChild(pNode->node());
		}
	}
}

raaOSGDataNode* raaGraphInterface::addNode(std::string sName, std::string sGroup)
{
	raaOSGDataNode *pNode = 0;

	if (!raaDataEngine::instance()->currentModel()->hasNode(sName))
	{

		pNode = new raaOSGDataNode(sName, this, sGroup);

		pNode->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
		raaDataEngine::instance()->currentModel()->addNode(pNode);
		m_pInactiveNodesSwitch->addChild(pNode->node());
	}
	else
	{
		pNode = dynamic_cast<raaOSGDataNode*>(raaDataEngine::instance()->currentModel()->getNode(sName));
		pNode->addToGroup(sGroup);
	}
	return pNode;
}

void raaGraphInterface::resize(int iWidth, int iHeight)
{
	if (m_pGraphHud) m_pGraphHud->resize(0, 0, iWidth, iHeight);
	if (m_pMouseOverHud) m_pMouseOverHud->resize(0, 0, iWidth, iHeight);
}

void raaGraphInterface::move(int iX, int iY)
{
	m_aiMousePos[0] = iX;
	m_aiMousePos[1] = iY;
//	updateOvers();
}

void raaGraphInterface::frame(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if(m_bMouseOverActive)
	{
		osgUtil::LineSegmentIntersector::Intersections isecs;
		aa.computeIntersections(ea, isecs);
		raaOvers lCurrent;
		std::string sNames, sCluster;

		for (osgUtil::LineSegmentIntersector::Intersections::iterator it = isecs.begin(); it != isecs.end(); it++)
			if (it->drawable && it->drawable->getUserData() && std::find(lCurrent.begin(), lCurrent.end(), it->drawable->getUserData()) == lCurrent.end())
			{
				lCurrent.push_back(it->drawable->getUserData());
				if (raaOSGDataNode *pNode = dynamic_cast<raaOSGDataNode*>(it->drawable->getUserData()))
				{
					sNames += pNode->description();
					sNames += "\n";
				}
				
				if(raaClustersSet *pClusters=dynamic_cast<raaClustersSet*>(it->drawable->getUserData()))
				{
					sCluster += pClusters->getDescription(it->drawable);
					sCluster += "\n";
				}
			}

		m_pMouseOverHud->setNames(sNames);
		m_pMouseOverHud->setCluster(sCluster);

		if (sNames.size() || sCluster.size()) 
		{
			m_pMouseOverHud->setPos(m_aiMousePos[0], m_aiMousePos[1]);
			m_pMouseOverHud->setState(true);
		}
		else
			m_pMouseOverHud->setState(false);
	}
}

std::string raaGraphInterface::nameToGroup(std::string sName)
{
	// if result
		// or
	// find first symbol (<>=)
	std::string sRes;

	if (sName.length())
	{
		QString s=sName.c_str();
	

		if(s.contains("Result::"))
		{
			s=s.remove("Result::");

			QStringList sl = s.split(QRegExp("[=]"), QString::SkipEmptyParts);
			QStringList::iterator slit = sl.begin();
			slit++;
			int iRes = slit->toInt();
			
			switch(iRes)
			{
				case 1:
					return "Result::1";
				case 2:
					return "Result::2";
				default:
					return "Result::Undef";
			}
		}
		else
		{
			QStringList sl = s.split(QRegExp("[<>=]"), QString::SkipEmptyParts);

			if (sl.length() >= 1) return sl.first().toLower().toStdString();
		}
	}
	return sRes;
}

std::string raaGraphInterface::nodeNamesToString(raaNodeNames& nn)
{
	std::string s;

	raaNodeNames::iterator it = nn.begin();
	do
	{
		s += *it;
		it++;
		if (it != nn.end())
			s += "::";
	} while (it != nn.end());

	return s;
}

void raaGraphInterface::loadDecisonTreeFile(QString sFile)
{
	if (sFile.length())
	{
		QFileInfo f(sFile);
		float fIdealLen = lo_ideal_arc_length_spin->value();

		std::string sGroup = f.baseName().toStdString();
		raaDataLayer *pLayer = new raaDataLayer(sGroup);
		pLayer->refActive();
		raaDataEngine::instance()->currentModel()->addLayer(pLayer);
	

		std::ifstream in(sFile.toStdString());
		std::string sLine;

		raaArcVector vArcs;
		unsigned int uiDepth;
		raaNodeNames lNames, lNodes;

		while (!in.eof())
		{
			std::getline(in, sLine);
			QString s(sLine.c_str());
			if (sLine.length() && (s.contains('=')||s.contains('>')||s.contains('<')))
			{
				s = s.replace("\t", " ");
				s = s.remove("|");
				s = s.remove(" ");
				s = s.replace("?", "=");

				if (s.length())
				{
					if (s.contains(":"))
					{
						QStringList ss = s.split(":");
						QStringList::iterator it = ss.begin();

						lNames.push_back(refineNameString((*it).remove(":")).toStdString());

						it++;

						QString sw = (*it);
						sw = sw.replace("(", " ");
						sw = sw.replace("/", " ");
						sw = sw.replace(")", " ");
						QStringList sss = sw.split(" ", QString::SkipEmptyParts);
						QStringList::iterator it2 = sss.begin();
						int iResult = (*it2).toInt();
						QString sR = QString("Result::%1=%2").arg(f.baseName()).arg((*it2));
						it2++;
						float fW = (*it2).toFloat();
						float fAB = fW;

						it2++;
						if(it2!=sss.end())
						{
							if(de_combine_result_strengths_check->isChecked())  fW-= (*it2).toFloat();
							fAB+= (*it2).toFloat();
						}

						bool bCreate = true;
						if (iResult == -1 && lo_discard_undef_check->isChecked()) bCreate = false;
						if (de_discard_check->isChecked() &&  fAB < de_discard_spin->value()) bCreate = false;

						if (bCreate)
						{
							bool bNewLast = false;
							lNames.push_back(sR.toStdString());

							raaDataArc *pArc = new raaDataArc(nodeNamesToString(lNames));
							raaDataEngine::instance()->currentModel()->addArc(pArc, pLayer);

							if (m_uiArcWeightMap == csm_uiArcWeightsAsSpringStrength)
							{
								pArc->setWeight(fW);
								pArc->setIdealLength(fIdealLen);
							}
							else if(m_uiArcWeightMap== csm_uiArcWeightsAsSpringLength)
							{
								pArc->setWeight(1.0f);
								pArc->setIdealLength(fW);
							}

							raaOSGDataNode *pLast = 0;

							for (raaNodeNames::iterator iN = lNames.begin(); iN != lNames.end(); iN++)
							{
								raaOSGDataNode *pNode = 0;
								std::string sName = (*iN);

			//					std::cout << "sName -> " << sName << std::endl;

								QString sN = sName.c_str();

//								if(sN.contains("wheadec"))
									if (m_pDataDic) sName = m_pDataDic->lookupName(sName.c_str()).toStdString();

								if (!raaDataEngine::instance()->currentModel()->hasNode(sName))
								{

									pNode = new raaOSGDataNode(sName, this, sGroup);
									
									if(m_pDataDic)
									{
										pNode->setDescription(m_pDataDic->lookupAccro(QString(sName.c_str())).toStdString());
									}

									pNode->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
									raaDataEngine::instance()->currentModel()->addNode(pNode);
									m_pInactiveNodesSwitch->addChild(pNode->node());
									bNewLast = true;

								}
								else
								{
									pNode = dynamic_cast<raaOSGDataNode*>(raaDataEngine::instance()->currentModel()->getNode(sName));
									pNode->addToGroup(sGroup);
									bNewLast = false;
								}

								if (pNode)
								{
									// add grouping here

									raaDataEngine::instance()->currentModel()->addGroupNode(nameToGroup(pNode->name()), pNode);

									pArc->addNode(pNode);
									pLast = pNode;
								}
							}

							lNames.pop_back();
							lNames.pop_back();

							if (pLast)
							{
								pLast->pin(true);

								if (lo_position_results_check->isChecked() && bNewLast)
								{
									switch (iResult)
									{
									case 2:
										pLast->setPosition(m_vRes2Pos);
										pLast->addToGroup("Result::2");
										m_vRes2Pos += m_vRes2Step;
										break;
									case 1:
										pLast->setPosition(m_vRes1Pos);
										pLast->addToGroup("Result::1");
										m_vRes1Pos += m_vRes1Step;
										break;
									default:
										pLast->setPosition(m_vResPos);
										pLast->addToGroup("Result::UnDef");
										m_vResPos += m_vResStep;
										break;
									}
								}
							}
						}
					}
					else
					{
						lNames.push_back(refineNameString(s).toStdString());
					}
				}
			}
		}
		
		in.close();

		if (lo_normalise_arcs_check->isChecked())
		{
			switch (m_uiArcWeightMap)
			{
			case csm_uiArcWeightsAsSpringStrength:
				pLayer->normaliseArcWeights();
				break;
			case csm_uiArcWeightsAsSpringLength:
				pLayer->normaliseArcLengths(fIdealLen, fIdealLen*2.0f);
				break;
			}
		}

		for (raaDataNodeGroups::const_iterator cit = raaDataEngine::instance()->currentModel()->nodeGroups().begin(); cit != raaDataEngine::instance()->currentModel()->nodeGroups().end(); cit++)
		{
			osg::Vec3f v(raaUtilities::randfloat(0.0f, 1.0f), raaUtilities::randfloat(0.0f, 1.0f), raaUtilities::randfloat(0.0f, 1.0f));
			for (raaDataNodeGroup::const_iterator it = cit->second.begin(); it != cit->second.end(); it++)
			{
				((raaOSGDataNode*)(*it))->setMaterial(v);
			}
		}

	}

}

void raaGraphInterface::loadNewDecisonTreeFile(QString sFile)
{
	if (sFile.length())
	{
		QFileInfo f(sFile);
		float fIdealLen = lo_ideal_arc_length_spin->value();

		std::string sGroup = f.baseName().toStdString();
		raaDataLayer *pLayer = new raaDataLayer(sGroup);
		pLayer->refActive();
		raaDataEngine::instance()->currentModel()->addLayer(pLayer);

		std::ifstream in(sFile.toStdString());
		std::string sLine;

		raaArcVector vArcs;
		unsigned int uiDepth;
		raaNodeNames lNames, lNodes;

		while (!in.eof())
		{
			std::getline(in, sLine);
			if (sLine.length())
			{
				QString s(sLine.c_str());
				s = s.replace("\t", " ");
				s = s.remove("|");
				s = s.remove(" ");
				s = s.replace("?", "=");

				if (s.length())
				{
					if (s.contains(":"))
					{
						QStringList ss = s.split(":");
						QStringList::iterator it = ss.begin();

						lNames.push_back(refineNameString((*it).remove(":")).toStdString());

						it++;

						QString sw = (*it);
						sw = sw.replace("(", " ");
						sw = sw.replace("/", " ");
						sw = sw.replace(")", " ");
						QStringList sss = sw.split(" ", QString::SkipEmptyParts);
						QStringList::iterator it2 = sss.begin();
						int iResult = (*it2).toInt();
						QString sR = QString("Result::%1=%2").arg(f.baseName()).arg((*it2));
						it2++;
						float fW = (*it2).toFloat();
						float fAB = fW;

						it2++;
						if (it2 != sss.end())
						{
							if (de_combine_result_strengths_check->isChecked())  fW -= (*it2).toFloat();
							fAB += (*it2).toFloat();
						}

						bool bCreate = true;
						if (iResult == -1 && lo_discard_undef_check->isChecked()) bCreate = false;
						if (de_discard_check->isChecked() && fAB < de_discard_spin->value()) bCreate = false;

						if (bCreate)
						{
							bool bNewLast = false;
							lNames.push_back(sR.toStdString());

							raaDataArc *pArc = new raaDataArc(nodeNamesToString(lNames));
							raaDataEngine::instance()->currentModel()->addArc(pArc, pLayer);

							if (m_uiArcWeightMap == csm_uiArcWeightsAsSpringStrength)
							{
								pArc->setWeight(fW);
								pArc->setIdealLength(fIdealLen);
							}
							else if (m_uiArcWeightMap == csm_uiArcWeightsAsSpringLength)
							{
								pArc->setWeight(1.0f);
								pArc->setIdealLength(fW);
							}

							raaOSGDataNode *pLast = 0;

							for (raaNodeNames::iterator iN = lNames.begin(); iN != lNames.end(); iN++)
							{
								raaOSGDataNode *pNode = 0;
								std::string sName = (*iN);

								if (!raaDataEngine::instance()->currentModel()->hasNode(sName))
								{

									pNode = new raaOSGDataNode(sName, this, sGroup);

									pNode->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
									raaDataEngine::instance()->currentModel()->addNode(pNode);
									m_pActiveNodesSwitch->addChild(pNode->node());
									bNewLast = true;

								}
								else
								{
									pNode = dynamic_cast<raaOSGDataNode*>(raaDataEngine::instance()->currentModel()->getNode(sName));
									pNode->addToGroup(sGroup);
									bNewLast = false;
								}

								if (pNode)
								{
									// add grouping here

									raaDataEngine::instance()->currentModel()->addGroupNode(nameToGroup(pNode->name()), pNode);

									pArc->addNode(pNode);
									pLast = pNode;
								}
							}

							lNames.pop_back();
							lNames.pop_back();

							if (pLast)
							{
								pLast->pin(true);

								if (lo_position_results_check->isChecked() && bNewLast)
								{
									switch (iResult)
									{
									case 2:
										pLast->setPosition(m_vRes2Pos);
										pLast->addToGroup("Result::2");
										m_vRes2Pos += m_vRes2Step;
										break;
									case 1:
										pLast->setPosition(m_vRes1Pos);
										pLast->addToGroup("Result::1");
										m_vRes1Pos += m_vRes1Step;
										break;
									default:
										pLast->setPosition(m_vResPos);
										pLast->addToGroup("Result::UnDef");
										m_vResPos += m_vResStep;
										break;
									}
								}
							}
						}
					}
					else
					{
						lNames.push_back(refineNameString(s).toStdString());
					}
				}
			}
		}

		in.close();

		if (lo_normalise_arcs_check->isChecked())
		{
			switch (m_uiArcWeightMap)
			{
			case csm_uiArcWeightsAsSpringStrength:
				pLayer->normaliseArcWeights();
				break;
			case csm_uiArcWeightsAsSpringLength:
				pLayer->normaliseArcLengths(fIdealLen, fIdealLen*2.0f);
				break;
			}
		}
	}

}

void raaGraphInterface::loadDecisonTreeYearFile(QString sFile)
{
}

QString raaGraphInterface::refineNameString(QString s)
{
	if (lo_round_float_check->isChecked())
	{
		if (s.contains('<') || s.contains('>'))
		{
			std::string sSymbol;
			if (s.contains('<'))sSymbol += '<';
			if (s.contains('>'))sSymbol += '>';
			if (s.contains('='))sSymbol += '=';


			QStringList ss = s.split(sSymbol.c_str());
			QStringList::iterator it = ss.begin();
			std::string sName = (*it).toStdString();
			it++;
			int iValue = round((*it).toFloat());

			//								lNames.push_back((*it).remove(":").toStdString());
			//								s.clear();

			std::cout << "S -> " << s.toStdString() << " -> ";

			s = QString("%1 %2 %3").arg(sName.c_str()).arg(sSymbol.c_str()).arg(iValue);
//			std::cout << s.toStdString() << std::endl;


		}
//		else
//			std::cout << "S -> " << s.toStdString() << std::endl;

	}

	return  s.remove(" ");

}

void raaGraphInterface::updateInfo(bool bForce)
{
/*
	if(bForce || info_track_updates_check->isChecked())
	{
		switch (info_tab->currentIndex())
		{
		case 0:
			info_node_table_view->update();
			info_node_table_view->model()->resetInternalData();
			QCoreApplication::processEvents();
			break;
		case 1:
			info_arc_table_view->update();
			QCoreApplication::processEvents();
			break;
		case 2:
			info_layer_table_view->update();
			QCoreApplication::processEvents();
			break;
		case 3:
			info_cluster_table_view->update();
			QCoreApplication::processEvents();
			break;
		case 5:
			info_model_table_view->update();
			QCoreApplication::processEvents();
			break;
		default:
			break;
		}
	}
*/
}

void raaGraphInterface::populateClusterInfo()
{
	if (m_pClusterModel)
	{
		m_pClusterModel->clear();
		m_pClusteredModel->clear();

		QStandardItem *pSelected = 0;
		if (raaDataEngine::instance()->currentModel() && info_cluster_show_check->checkState() == Qt::Checked)
		{
			QStandardItem *pParentItem = m_pClusterModel->invisibleRootItem();

			QStandardItem *pClusteredParentItem = m_pClusteredModel->invisibleRootItem();
			m_pClusteredModel->setColumnCount(raaDataEngine::instance()->currentModel()->clusterSet().size());

			int i = 0;
			for (raaClusterSet::const_iterator it = raaDataEngine::instance()->currentModel()->clusterSet().begin(); it != raaDataEngine::instance()->currentModel()->clusterSet().end(); it++, i++)
			{
				raaVector vPos, vMin, vMax, vRange, vSize;
				unsigned int uiNum = it->size();

				raaCluster::const_iterator cit = it->begin();

				vMin = (*cit)->position();
				vMax = (*cit)->position();

				if (i == 0)
				{
					QStandardItem *pCItem = new QStandardItem(QString("Node -> %1").arg((*cit)->name().c_str()));
					pClusteredParentItem->appendRow(pCItem);
				}

				for (cit++; cit != it->end();cit++)
				{
					raaVector p = (*cit)-> position();

					vMin[0] = (p[0] < vMin[0]) ? p[0] : vMin[0];
					vMin[1] = (p[1] < vMin[1]) ? p[1] : vMin[1];
					vMin[2] = (p[2] < vMin[2]) ? p[2] : vMin[2];
					vMax[0] = (p[0] > vMax[0]) ? p[0] : vMax[0];
					vMax[1] = (p[1] > vMax[1]) ? p[1] : vMax[1];
					vMax[2] = (p[2] > vMax[2]) ? p[2] : vMax[2];

					if (i == 0)
					{
						QStandardItem *pCItem = new QStandardItem(QString("Node -> %1").arg((*cit)->name().c_str()));
						pClusteredParentItem->appendRow(pCItem);
					}
				}

				vRange = (vMax - vMin);
				vSize = vRange;
				vPos = vRange*0.5f;
				vPos +=vMin;

				QStandardItem *pItem = new QStandardItem(QString("%1 :: %2, %3, %4").arg(uiNum).arg(vPos[0]).arg(vPos[1]).arg(vPos[2]));
				pParentItem->appendRow(pItem);

				if (i == m_iSelectedCluster)
				{
					if(m_bNewClusterSelected)
					{
						m_vSelectedCentre = vPos;
						m_vSelectedSize = vSize;

						m_bNewClusterSelected = false;
					}
					// how do we track the existing cluster -  eg search based on size and centre.
					// in this case the centre is the most important and size should only be considered if there is more than one potential candidate.
					// also need to consider the metrics of the cluster - is it growing or srinking. Possibly also show migration path.  

					pSelected = pItem;
					pItem->setBackground(QBrush(Qt::yellow));

					info_cluster_count_label->setText(QString("%1 -> %2").arg("nodes").arg(it->size()));
					info_cluster_pos_label->setText(QString("%1 -> %2, %3, %4").arg("Pos").arg(vPos[0]).arg(vPos[1]).arg(vPos[2]));
					info_cluster_size_label->setText(QString("%1 -> %2, %3, %4").arg("Size").arg(vSize[0]).arg(vSize[1]).arg(vSize[2]));

				}
				else
				{
					pItem->setBackground(QBrush(Qt::white));
				}
			}
		}
		
		if(pSelected)
		{
			info_cluster_column_view->setCurrentIndex(pSelected->index());
//			m_pClusterSelectionModel->select(pSelected->index(), QItemSelectionModel::Select| QItemSelectionModel::Rows);
		}
		else
		{
			info_cluster_column_view->setCurrentIndex(QModelIndex());
			//			m_pClusterSelectionModel->clearSelection();
		}
		
	}
}

void raaGraphInterface::addPajekVertex(std::string sString)
{
	std::string sColour;
	std::string sBColour;
//	std::string sID;

	if (sString.length())
	{
		char *pStr = (char*)_alloca(sizeof(char)*sString.length() + 1);
		sprintf(pStr, "%s", sString.c_str());
		char *pPos = 0;

		int iIndex= (pPos = strtok(pStr, "\"")) ? atoi(pPos) : -1;
		std::string sName = (pPos = strtok(0, "\"")) ? pPos : "";
		float x = (pPos = strtok(0, " ")) ? atof(pPos)*m_fPajekScale : 0.0f;
		float y = (pPos = strtok(0, " ")) ? atof(pPos)*m_fPajekScale : 0.0f;
		float z = (pPos = strtok(0, " ")) ? atof(pPos)*m_fPajekScale : 0.0f;
//		osg::Vec3f vPos(x, y, z);
		pPos = strtok(0, " ");
		std::string sColour = (pPos = strtok(0, " ")) ? pPos : "default";
		pPos = strtok(0, " ");
		std::string sBColour = (pPos = strtok(0, " ")) ? pPos : "default";

		if (iIndex != -1)
		{
			raaOSGDataNode *pNode = new raaOSGDataNode(sName, this);

			pNode->setPosition(raaVector(x, z, y, 1.0f));


			raaDataEngine::instance()->currentModel()->addNode(pNode);

			m_mPajekMap[iIndex] = pNode;
			m_pActiveNodesSwitch->addChild(pNode->node());
//			gl_window->scenes()[0]->addChild(pNode->node());
		}
	}
}

void raaGraphInterface::addPajekArc(std::string sString)
{
	if (sString.length())
	{
		float fIdealLen = lo_ideal_arc_length_spin->value();

		char *pStr = (char*)_alloca(sizeof(char)*sString.length() + 1);
		sprintf(pStr, "%s", sString.c_str());

		std::string sStart, sEnd;
		float fWeight = 1.0f;

		char *pPos = strtok(pStr, " ");
		sStart = pPos ? pPos : "";
		sEnd = (pPos = strtok(0, " ")) ? pPos : "";
		fWeight = (pPos = strtok(0, " ")) ? atof(pPos) : 0.0f;

		int iStart, iEnd;

		std::istringstream(sStart) >> iStart;
		std::istringstream(sEnd) >> iEnd;

		raaDataArc *pArc = new raaDataArc("");
		pArc->addNode(m_mPajekMap[iStart]);
		pArc->addNode(m_mPajekMap[iEnd]);
		pArc->setIdealLength(fIdealLen);
		pArc->setWeight(fWeight);

		raaDataEngine::instance()->currentModel()->addArc(pArc);
	}

}

