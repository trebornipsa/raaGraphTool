#pragma once

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsLineItem>

class raaGraphNode;

class raaGraphModel: public QGraphicsScene
{
	Q_OBJECT
public:
	raaGraphModel(void);
	virtual ~raaGraphModel(void);

	raaGraphNode* addAutoItem(int iX, int iY, QString sName, unsigned int uiShape, int iR, int iG, int iB);
	raaGraphNode* addAutoItem(int iX, int iY, QString sName, unsigned int uiShape, QString sColor);
	void addConnection(raaGraphNode *pStart, raaGraphNode *pEnd);
	void addConnection(raaGraphNode *pStart, raaGraphNode *pEnd, float fWeight);

protected:
	void dragEnterEvent(QGraphicsSceneDragDropEvent *pEvent);
	void dragMoveEvent(QGraphicsSceneDragDropEvent *pEvent);
	void dragLeaveEvent(QGraphicsSceneDragDropEvent *pEvent);
	void dropEvent(QGraphicsSceneDragDropEvent *pEvent);
	void drawBackground(QPainter *pPainter, const QRectF &rRect);

	void mousePressEvent(QGraphicsSceneMouseEvent *pMouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *pMouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *pMouseEvent);

	unsigned int m_uiMouseMode;



	QBrush m_Background;
	QPen m_Grid;
	QPen m_Line;

	raaGraphNode *m_pStartNode;
	QGraphicsLineItem m_ConnectionLine;
	QPointF m_Start;	

};

