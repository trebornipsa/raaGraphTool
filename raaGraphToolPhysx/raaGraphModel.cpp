#include "StdAfx.h"

#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneDragDropEvent>
#include <QtCore/QMimeData>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGraphicsProxyWidget>

#include "raaGraphConnection.h"
#include "raaGraphNode.h"
#include "raaGraphModel.h"
#include "raaGraphModel.moc"

typedef QList<QGraphicsItem*> QGraphicsItems;

raaGraphModel::raaGraphModel(void)
{
	m_pStartNode=0;
	m_Background.setColor(QColor::fromRgb(43, 85, 128));
	m_Background.setStyle(Qt::SolidPattern);

	m_Grid.setColor(QColor::fromRgb(73, 115, 158));
	m_Grid.setStyle(Qt::SolidLine);

	m_Line.setColor(QColor(160, 160, 160, 50));
	m_Line.setStyle(Qt::SolidLine);

}


raaGraphModel::~raaGraphModel(void)
{
}

void raaGraphModel::dragEnterEvent( QGraphicsSceneDragDropEvent *pEvent )
{
	pEvent->acceptProposedAction();
}

void raaGraphModel::dragMoveEvent( QGraphicsSceneDragDropEvent *pEvent )
{
	pEvent->acceptProposedAction();
}

void raaGraphModel::dragLeaveEvent( QGraphicsSceneDragDropEvent *pEvent )
{
	pEvent->accept();
}

void raaGraphModel::dropEvent( QGraphicsSceneDragDropEvent *pEvent )
{
	if(pEvent && pEvent->mimeData() && pEvent->mimeData()->hasText())
	{
		QString sData=pEvent->mimeData()->text();

		if(sData.contains("raaGraph"))
		{
			QStringList slCmds=sData.split("::");

			if(slCmds.at(1)=="instNode")
			{
				QPointF p=pEvent->scenePos();
				raaGraphNode *pNode=new raaGraphNode(this, slCmds.at(2), slCmds.at(3).toInt(), slCmds.at(4).toInt(), slCmds.at(5).toInt(), slCmds.at(6).toInt());
				addItem(pNode);
				pNode->setPos(p);
			}
		}
	}
	pEvent->acceptProposedAction();
}

void raaGraphModel::drawBackground( QPainter *pPainter, const QRectF &rRect )
{
	pPainter->setBrush(m_Background);
	pPainter->fillRect(rRect, m_Background);

//	pPainter->setPen(m_Grid);

//	for(int i=0;i<width();i+=250) pPainter->drawLine(i,0,i,height());
//	for(int j=0;j<height();j+=250) pPainter->drawLine(0, j, width(), j);
}

void raaGraphModel::mousePressEvent( QGraphicsSceneMouseEvent *pMouseEvent )
{
	if(pMouseEvent->button()==Qt::RightButton && !m_pStartNode)
	{
		QGraphicsItems list=items(pMouseEvent->scenePos());

		for(QGraphicsItems::iterator it=list.begin();it!=list.end();it++)
		{
			if(raaGraphNode *pNode=dynamic_cast<raaGraphNode*>(*it))
			{
				m_pStartNode=pNode;
				m_Start=pNode->centre();
				m_ConnectionLine.setLine(QLineF(m_Start, pMouseEvent->scenePos()));
				m_ConnectionLine.setPen(m_Line);
				addItem(&m_ConnectionLine);

				break;
			}
		}
	}
	else QGraphicsScene::mousePressEvent(pMouseEvent);
}

void raaGraphModel::mouseMoveEvent( QGraphicsSceneMouseEvent *pMouseEvent )
{
	if(m_pStartNode) m_ConnectionLine.setLine(QLineF(m_Start, pMouseEvent->scenePos()));
	else QGraphicsScene::mouseMoveEvent(pMouseEvent);
}

void raaGraphModel::mouseReleaseEvent( QGraphicsSceneMouseEvent *pMouseEvent )
{
	if(pMouseEvent->button()==Qt::RightButton && m_pStartNode)
	{
		QGraphicsItems list=items(pMouseEvent->scenePos());

		for(QGraphicsItems::iterator it=list.begin();it!=list.end();it++)
		{
			if(raaGraphNode *pNode=dynamic_cast<raaGraphNode*>(*it))
			{
				if(pNode!=m_pStartNode)
				{
					raaGraphConnection *pConnection=new raaGraphConnection(m_pStartNode, pNode);
					m_pStartNode->addConnection(pConnection);
					pNode->addConnection(pConnection);
					pConnection->update();
					addItem(pConnection);
				}
			}
		}

		m_pStartNode=0;
		removeItem(&m_ConnectionLine);
	}
	else QGraphicsScene::mouseReleaseEvent(pMouseEvent);	
}

raaGraphNode* raaGraphModel::addAutoItem( int iX, int iY, QString sName, unsigned int uiShape, int iR, int iG, int iB )
{
	raaGraphNode *pNode=new raaGraphNode(this, sName, uiShape, iR, iG, iB);
	addItem(pNode);
	pNode->setPos(QPointF(iX, iY));
	return pNode;
}

raaGraphNode* raaGraphModel::addAutoItem( int iX, int iY, QString sName, unsigned int uiShape, QString sColor )
{
	raaGraphNode *pNode=new raaGraphNode(this, sName, uiShape, sColor);
	addItem(pNode);
	pNode->setPos(QPointF(iX, iY));
	return pNode;
}

void raaGraphModel::addConnection( raaGraphNode *pStart, raaGraphNode *pEnd )
{
	if(pStart && pEnd)
	{
		raaGraphConnection *pConnection=new raaGraphConnection(pStart, pEnd);
		pConnection->setPen(m_Line);
		pStart->addConnection(pConnection);
		pEnd->addConnection(pConnection);
		pConnection->update();
		addItem(pConnection);
	}
}

void raaGraphModel::addConnection( raaGraphNode *pStart, raaGraphNode *pEnd, float fWeight )
{
	if(pStart && pEnd)
	{
		raaGraphConnection *pConnection=new raaGraphConnection(pStart, pEnd);

		int i=50+205*fWeight;

		QPen p(QColor(i,i,i,i));
//		p.setWidth()

		pConnection->setPen(p);
		pStart->addConnection(pConnection);
		pEnd->addConnection(pConnection);
		pConnection->update();
		addItem(pConnection);
	}
}
