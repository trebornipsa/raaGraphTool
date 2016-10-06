#include "StdAfx.h"

#include <stdlib.h>
#include <time.h>
#include <list>
#include <map>
#include <iostream>
#include <fstream>

#include <QtGui/QDrag>
#include <QtGui/QDropEvent>
#include <QtCore/QMimeData>
#include <QtOpenGL/QGLWidget>
#include <QtGui\QFileDialog>

#include "raaGraphClass.h"
#include "raaGraphNode.h"
#include "raaGraphModel.h"
#include "raaGraphToolInterface.h"
#include "raaGraphToolInterface.moc"

typedef std::list<raaGraphNode*> raaGraphNodes;
typedef std::map<unsigned int, raaGraphNode*> raaGraphNodesMap;

raaGraphToolInterface::raaGraphToolInterface(void)
{
	m_pModel=new raaGraphModel();
	m_pModel->setSceneRect(QRect(0,0,5000,5000));

	setupUi(this);

	graph_view->setScene(m_pModel);

//	QGLFormat format(QGL::DoubleBuffer|QGL::DepthBuffer|QGL::Rgba|QGL::AlphaChannel|QGL::DirectRendering|QGL::SingleBuffer);
	
		
	QGLFormat format=QGLFormat::defaultFormat();
	format.setOption(QGL::DoubleBuffer|QGL::DepthBuffer|QGL::Rgba|QGL::AlphaChannel|QGL::DirectRendering);
//	format.setDepthBufferSize(4);

	QGLContext *pContext=new QGLContext(format);

	graph_view->setViewport(new QGLWidget(pContext));

	graph_view->setOptimizationFlags(QGraphicsView::DontClipPainter);
	graph_view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	graph_view->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);
	graph_view->setCacheMode(QGraphicsView::CacheBackground);
	graph_view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

	tree_widget->setHeaderHidden(true);
	connect(tree_widget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), SLOT(startClassDrag(QTreeWidgetItem*, int))); 
	connect(zoom_in_button, SIGNAL(pressed()), SLOT(zoomIn()));
	connect(zoom_out_button, SIGNAL(pressed()), SLOT(zoomOut()));
	connect(create_button, SIGNAL(pressed()), SLOT(createItems()));
	connect(actionLoad_Pajek, SIGNAL(triggered(bool)), SLOT(loadPajek(bool)));
}

raaGraphToolInterface::~raaGraphToolInterface(void)
{
}

void raaGraphToolInterface::addClass( QString sName, unsigned int uiShape, int iR, int iG, int iB)
{
	tree_widget->addTopLevelItem(new raaGraphClass(sName, uiShape, iR, iG, iB));
}

void raaGraphToolInterface::startClassDrag( QTreeWidgetItem* pItem, int iCol)
{
	raaGraphClass *pClass=dynamic_cast<raaGraphClass*>(pItem);
	if(pClass)
	{
		QDrag *pDrag=new QDrag(this);
		QMimeData *pMime=new QMimeData();
		pMime->setText(QString("raaGraph::instNode::")+pClass->mime());
		pDrag->setMimeData(pMime);
		Qt::DropAction drop=pDrag->exec();
	}
}

void raaGraphToolInterface::zoomOut()
{
	graph_view->scale(1.05f, 1.05f);	
	raaGraphNode::scale(0.95f);
	graph_view->update();
}

void raaGraphToolInterface::zoomIn()
{
	graph_view->scale(0.95f, 0.95f);	
	raaGraphNode::scale(1.05f);
	graph_view->update();
}

void raaGraphToolInterface::createItems()
{
	bool bOk=false;
	unsigned int uiNum=create_num_lineedit->text().toInt(&bOk);

	srand(time(0));

	if(bOk)
	{
		raaGraphNodes lNodes;

		for(unsigned int i=0;i<uiNum;i++)
		{
			int x = rand() % 4900 + 100;
			int y = rand() % 4900 + 100;

			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;

			lNodes.push_back(m_pModel->addAutoItem(x, y, QString("Auto"), 0, r, g, b));
		}

		for(raaGraphNodes::iterator it1=lNodes.begin();it1!=lNodes.end();it1++)
			for(raaGraphNodes::iterator it2=lNodes.begin();it2!=lNodes.end();it2++)
			{
				raaGraphNode *pNode1=*it1;
				raaGraphNode *pNode2=*it2;

				if(pNode1!=pNode2)
					m_pModel->addConnection(pNode1, pNode2);
			}
	}
}

void raaGraphToolInterface::loadPajek( bool )
{
	QString sFile=QFileDialog::getOpenFileName(this);

	std::ifstream in(sFile.toLocal8Bit());
	raaGraphNodesMap mNodes;
	
	if(in.is_open())
	{
		while(!in.eof())
		{
			std::string sLine;

			std::getline(in, sLine);
			std::cout << sLine << std::endl;

			QString s(sLine.c_str());


			if(s[0]=='*')
			{
				std::cout << "\t instruction" << std::endl;

				QStringList sl=s.split(' ', QString::SkipEmptyParts);

				if(sl[0]=="*Vertices")
				{
					for(int i=0;i<sl[1].toInt();i++)
					{
						std::getline(in, sLine);
						QString v(sLine.c_str());
						QStringList vl=v.split(' ', QString::SkipEmptyParts);

						int iIndex=vl[0].toInt();

						QString sName=vl[1];
						sName.remove('\"');



						float x=vl[2].toFloat()*5000.0f;
						float y=vl[3].toFloat()*5000.0f;
//						float z=vl[4].toFloat()*2500.0f;

//						QString sCol=vl[6];

						QString sCol("White");

						mNodes[iIndex]=m_pModel->addAutoItem((int)x, 5000-(int)y, sName, 0, sCol);
					}
				}
				else if(sl[0]=="*Arcs")
				{
//					for(int i=0;i<sl[1].toInt();i++)
					while(!in.eof())
					{
						std::getline(in, sLine);
						if(sLine.length())
						{
							QString v(sLine.c_str());
							QStringList vl=v.split(' ', QString::SkipEmptyParts);

							std::cout << "\tStart: " << vl[0].toInt() << " End: " << vl[1].toInt() << std::endl;

							raaGraphNode *pStart=mNodes[vl[0].toInt()];
							raaGraphNode *pEnd=mNodes[vl[1].toInt()];

							float fWeight=vl[2].toFloat()/3000000.0f;

							m_pModel->addConnection(pStart, pEnd, fWeight);
						}
						else break;
					}
				}


			}

		}

		in.close();
	}	
}
