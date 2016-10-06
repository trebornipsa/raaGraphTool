#include "StdAfx.h"

#include <windows.h>
#include <GL/gl.h>

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtCore/QPoint>
#include <QtGui/QDrag>
#include <QtGui/QDropEvent>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include "raaGraphConnection.h"
#include "raaGraphModel.h"
#include "raaGraphNode.h"

float raaGraphNode::sm_fScale=1.0f;

raaGraphNode::raaGraphNode(raaGraphModel *pModel, QString sName, unsigned int uiShape, int iR, int iG, int iB)
{
	m_sNodeName=sName;
	m_bDragging=false;
	m_pModel=pModel;
	m_bUpdateGeom=true;
	m_Color=QColor::fromRgb(iR, iG, iB);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setZValue(2);
	m_uiShape=uiShape;
}

raaGraphNode::raaGraphNode(raaGraphModel *pModel, QString sName, unsigned int uiShape, QString sColor)
{
	m_sNodeName=sName;
	m_bDragging=false;
	m_pModel=pModel;
	m_bUpdateGeom=true;
	m_Color=QColor(sColor);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setZValue(2);
	m_uiShape=uiShape;
}

raaGraphNode::~raaGraphNode(void)
{
}

void raaGraphNode::paint( QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget )
{
	if(m_bUpdateGeom && pPainter)
	{
		m_bUpdateGeom=false;
		recalcGeom(pPainter);
	}

/*
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);

	glVertex3f(-0.5f, -0.5f, 0.0f);	
	glVertex3f(0.5f, -0.5f, 0.0f);	
	glVertex3f(0.5f, 0.5f, 0.0f);	
	glVertex3f(-0.5f, 0.5f, 0.0f);	

	glEnd();
*/


//	glPushMatrix();
//	glScalef(sm_fScale, sm_fScale, sm_fScale);

	setScale(sm_fScale);

	if(m_uiShape==0) pPainter->fillRect(m_BackgroundRect, m_Color);
	else if(m_uiShape==1) pPainter->drawEllipse(m_BackgroundRect);
	pPainter->drawText(m_TextRect, Qt::AlignHCenter|Qt::AlignVCenter|Qt::TextSingleLine, m_sNodeName);

//	glPopMatrix();
}

QRectF raaGraphNode::boundingRect() const
{
	return m_BackgroundRect;
}

void raaGraphNode::updateGeom()
{
	m_bUpdateGeom=true;
	update(m_BackgroundRect);
}

raaGraphModel* raaGraphNode::model()
{
	return m_pModel;
}

void raaGraphNode::recalcGeom( QPainter *p )
{
	m_TextRect = p->boundingRect(m_BackgroundRect, Qt::AlignHCenter|Qt::AlignVCenter|Qt::TextSingleLine, m_sNodeName);	
//	m_TextRect.setWidth(((int)(((float)m_TextRect.width())*sm_fScale)));
//	m_TextRect.setHeight(((int)(((float)m_TextRect.height())*sm_fScale)));
	m_BackgroundRect=QRect(m_TextRect.left()-2, m_TextRect.top()-2, m_TextRect.width()+2, m_TextRect.height()+2);
	m_Centre=QPoint(m_BackgroundRect.x()+(m_BackgroundRect.width()>>1), m_BackgroundRect.y()+(m_BackgroundRect.height()>>1));
	prepareGeometryChange();
}

void raaGraphNode::mouseMoveEvent( QGraphicsSceneMouseEvent *pEvent )
{
	QGraphicsItem::mouseMoveEvent(pEvent);
	for(raaGraphConnections::iterator it=m_lConnections.begin();it!=m_lConnections.end();it++) (*it)->update();
}

QPointF raaGraphNode::centre()
{
	return mapToScene(m_Centre);
}

void raaGraphNode::addConnection( raaGraphConnection *pConnection )
{
	if(pConnection) m_lConnections.push_back(pConnection);

}

void raaGraphNode::scale( float f )
{
	sm_fScale*=f;
}
