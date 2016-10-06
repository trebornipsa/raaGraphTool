#pragma once

#include <list>

#include <QtWidgets/QGraphicsItem>

class raaGraphModel;
class raaGraphConnection;

typedef std::list<raaGraphConnection*>raaGraphConnections;

class raaGraphNode: public QGraphicsItem
{
public:
	raaGraphNode(raaGraphModel *pModel, QString sName, unsigned int uiShape, int iR, int iG, int iB);
	raaGraphNode(raaGraphModel *pModel, QString sName, unsigned int uiShape, QString sColor);
	virtual ~raaGraphNode(void);

	void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget);
	QRectF boundingRect() const;
	void updateGeom();
	raaGraphModel* model();
	QPointF centre();

	void addConnection(raaGraphConnection *pConnection);

	static void scale(float f);

protected:
	void recalcGeom(QPainter *p);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *pEvent);

	raaGraphModel *m_pModel;

	bool m_bUpdateGeom;
	bool m_bDragging;

	QRect m_BackgroundRect;
	QRect m_TextRect;
	QColor m_Color;
	QPointF m_Centre;

	QString m_sNodeName;	

	unsigned int m_uiShape;

	raaGraphConnections m_lConnections;

	static float sm_fScale;
};

