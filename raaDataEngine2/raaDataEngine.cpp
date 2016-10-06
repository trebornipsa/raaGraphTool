#include <iostream>
#include <fstream>

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtXml/QDomDocument>

#include "raaDataModel.h"
#include "raaDataPeriod.h"
#include "raaDataLayer.h"
#include "raaDataArc.h"
#include "raaDataNode.h"
#include "raaDataEngine.h"
#include "raaDataEngineListener.h"
#include <raaUtilities/raaUtilities.h>


unsigned int raaDE2::raaDataEngine::sm_uiInstance=0;
raaDE2::raaDataEngine* raaDE2::raaDataEngine::sm_pInstance = 0;;

raaDE2::raaDataEngine::raaDataEngine()
{
	m_fMaxRandPos = 30.0f;
	if (!sm_pInstance) sm_pInstance = this;
}

raaDE2::raaDataEngine::~raaDataEngine()
{
	if (sm_pInstance == this) sm_pInstance = 0;
}

QString raaDE2::raaDataEngine::refineNameString(QString s)
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

		std::cout << "S -> " << s.toStdString() << " -> ";

		s = QString("%1 %2 %3").arg(sName.c_str()).arg(sSymbol.c_str()).arg(iValue);
	}
	return  s.remove(" ");
}

std::string raaDE2::raaDataEngine::nodeNamesToString(raaStringList& nn)
{
	std::string s;

	raaStringList::iterator it = nn.begin();
	do
	{
		s += *it;
		it++;
		if (it != nn.end())
			s += "::";
	} while (it != nn.end());

	return s;
}


void raaDE2::raaDataEngine::loadDTWekaLayer(raaDataModel* pModel, raaDataPeriod* pPeriod, raaDataLayer* pLayer, std::string sFile)
{
	if (pModel && pPeriod && pLayer && sFile.length())
	{
		std::cout << "Load Layer -> " << pLayer->name() << " -> " << sFile << std::endl;

		std::ifstream inFile(sFile);

		if(inFile.is_open())
		{
			std::string sLine;
			raaStringList lNames, lNodes;
			while (!inFile.eof())
			{
				std::getline(inFile, sLine);
				QString s(sLine.c_str());
				if (sLine.length() && (s.contains('=') || s.contains('>') || s.contains('<')))
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
							QString sR = QString("Result::%1=%2").arg(pLayer->name().c_str()).arg((*it2));
							it2++;
							float fW = (*it2).toFloat();
							float fAB = fW;

							it2++;
							if (it2 != sss.end())
							{
//								if (de_combine_result_strengths_check->isChecked())  fW -= (*it2).toFloat();
								fW -= (*it2).toFloat();
								fAB += (*it2).toFloat();
							}

							bool bCreate = true;
//							if (iResult == -1 && lo_discard_undef_check->isChecked()) bCreate = false;
							if (iResult == -1) bCreate = false;
//							if (de_discard_check->isChecked() && fAB < de_discard_spin->value()) bCreate = false;

							if (bCreate)
							{
								bool bNewLast = false;
								lNames.push_back(sR.toStdString());


								raaDataArc *pArc=pModel->getOrCreateArc(nodeNamesToString(lNames), pLayer);

								pArc->setAttribute("spring_coef", fW);
								pArc->setAttribute("weight", 1.0f);
								pArc->setAttribute("ideal_len", 10.0f);

								pArc->useAttributeAsIdealLength("ideal_len");
								pArc->useAttributeAsSpringCoef("spring_coef");

								raaDataNode *pLast = 0;

								for (raaStringList::iterator iN = lNames.begin(); iN != lNames.end(); iN++)
								{
									raaDataNode *pNode = 0;
									std::string sName = (*iN);

									if(!pModel->hasNode(sName))
									{
	//									std::cout << "New Node -> " << sName << std::endl;
										pNode = pModel->getOrCreateNode(sName);
										pPeriod->addToGroup(pLayer->name(), pNode);
										pNode->setPosition(raaVector(raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), raaUtilities::randfloat(-m_fMaxRandPos, m_fMaxRandPos), 1.0f));
										bNewLast = true;

									}
									else
									{
//										std::cout << "Existing Node -> " << sName << std::endl;
										pNode = pModel->getOrCreateNode(sName);
										pPeriod->addToGroup(pLayer->name(), pNode);
										bNewLast = false;
									}

									if (pNode)
									{
//										raaDataEngine::instance()->currentModel()->addGroupNode(nameToGroup(pNode->name()), pNode);
										pModel->addNodeToArc(pArc, pNode);
										pLast = pNode;
									}
								}

								lNames.pop_back();
								lNames.pop_back();
/*
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
								*/
							}
						}
						else
						{
							lNames.push_back(refineNameString(s).toStdString());
						}
					}
				}
			}

			inFile.close();
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
			}models
*/
		}

	}
}

void raaDE2::raaDataEngine::start()
{
	if (!sm_uiInstance++ && !sm_pInstance) new raaDataEngine();
}

void raaDE2::raaDataEngine::stop()
{
	if (!--sm_uiInstance && sm_pInstance) delete sm_pInstance;
}

raaDE2::raaDataEngine* raaDE2::raaDataEngine::instance()
{
	return sm_pInstance;
}

raaDE2::raaDataModel* raaDE2::raaDataEngine::addModel(std::string sName)
{
	raaDataModel* pModel = 0;

	if (sName.length() && m_mModels.find(sName) == m_mModels.end())
	{
		m_mModels[sName] = pModel = new raaDataModel(sName);
		m_lModels.push_back(sName);

		for (raaDataEngineListenersList::iterator it = m_lListeners.begin(); it != m_lListeners.end(); it++)
			(*it)->modelAdded(sName);
	}
	return pModel;
}

bool raaDE2::raaDataEngine::removeModel(std::string sName)
{
	if(sName.length() && m_mModels.find(sName)!=m_mModels.end())
	{
		delete m_mModels[sName];
		m_mModels.erase(sName);
		m_lModels.remove(sName);
		for (raaDataEngineListenersList::iterator it = m_lListeners.begin(); it != m_lListeners.end(); it++)
			(*it)->modelRemoved(sName);
		return true;
	}
	return false;
}

const raaDE2::raaStringList& raaDE2::raaDataEngine::models()
{
	return m_lModels;
}

raaDE2::raaDataModel* raaDE2::raaDataEngine::model(std::string sName)
{
	if (sName.length() && m_mModels.find(sName) != m_mModels.end()) return m_mModels[sName];
	return 0;
}

raaDE2::raaDataModel* raaDE2::raaDataEngine::loadModel(std::string sName, std::string sPath)
{
	raaDataModel *pModel = 0;
	if (sName.length() && sPath.length() && sPath.find(".de2")!=std::string::npos && m_mModels.find(sName) == m_mModels.end())
	{
		QFile file(sPath.c_str());

		QDir workingDir(sPath.c_str());
		workingDir.cdUp();


		QDomDocument doc;
		doc.setContent(&file, false);
		
		QDomElement root = doc.documentElement();
		QDomNode n = root.firstChild();

		while(!n.isNull())
		{
			QDomElement e = n.toElement();
			if (!e.isNull())
			{
				if(e.tagName()==QString("model"))
				{
					pModel = this->addModel(sName);

					QDomNode nP = e.firstChild();
					 while(!nP.isNull())
					 {
						 QDomElement eP = nP.toElement();

						 if(!eP.isNull())
						 {
							 if(eP.tagName()==QString("period"))
							 {
								 QString sPName;
								 QString sPDir;
								 QString sPStart="0";
								 QString sPEnd="1";
								 unsigned int uiPSeqNo = 0;
								 bool bPStart = false;

								 if (eP.hasAttribute("name")) sPName = eP.attribute("name");
								 if (eP.hasAttribute("dir")) sPDir = eP.attribute("dir");
								 if (eP.hasAttribute("start")) sPStart = eP.attribute("start");
								 if (eP.hasAttribute("end")) sPEnd = eP.attribute("end");
								 if (eP.hasAttribute("sequence_no")) uiPSeqNo = eP.attribute("sequence_no").toUInt();
								 if (eP.hasAttribute("start_period")) bPStart = eP.attribute("start_period").toInt()?true:false;

								 if(sPName.length() && sPDir.length())
								 {
									 raaDataPeriod *pPeriod = pModel->getOrCreatePeriod(sPName.toStdString());

									 if(pPeriod)
									 {
										 QDomNode nL = nP.firstChild();

										 while(!nL.isNull())
										 {
											 QDomElement eL = nL.toElement();
											 if(!eL.isNull())
											 {
												 QString sLType;
												 QString sLName;
												 QString sLFile;

												 if (eL.hasAttribute("name")) sLName = eL.attribute("name");
												 if (eL.hasAttribute("type")) sLType = eL.attribute("type");
												 if (eL.hasAttribute("file")) sLFile = eL.attribute("file");

												 if(sLType.length() && sLName.length() && sLFile.length())
												 {
													 raaDataLayer *pLayer = pModel->getOrCreateLayer(sLName.toStdString(), pPeriod);

													 if(pLayer)
													 {
														 workingDir.cd(sPDir);

														 std::cout << "File -> " << workingDir.filePath(sLFile).toStdString() << std::endl;

														 if (sLType == QString("dtWeka")) loadDTWekaLayer(pModel, pPeriod, pLayer, workingDir.filePath(sLFile).toStdString());
													 }
												 }
											 }
											 nL = nL.nextSibling();
										 }
									 }
									 pPeriod->normaliseArcs();
								 }
							 }
						 }

						 nP = nP.nextSibling();
					 }
				}
			}
			n = n.nextSibling();
		}


	}
	return 0;
}

void raaDE2::raaDataEngine::addListener(raaDataEngineListener* pListener)
{
	if (pListener && std::find(m_lListeners.begin(), m_lListeners.end(), pListener) == m_lListeners.end())
		m_lListeners.push_back(pListener);
}

void raaDE2::raaDataEngine::removeListener(raaDataEngineListener* pListener)
{
	if (pListener && std::find(m_lListeners.begin(), m_lListeners.end(), pListener) != m_lListeners.end())
		m_lListeners.remove(pListener);
}
