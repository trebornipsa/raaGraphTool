#include "StdAfx.h"

#include "raaGraphNode.h"

#include "raaGraphConnection.h"


raaGraphConnection::raaGraphConnection(raaGraphNode *pStart, raaGraphNode *pEnd)
{
	m_pStart=pStart;
	m_pEnd=pEnd;
	setZValue(0);
}

raaGraphConnection::~raaGraphConnection(void)
{
}

void raaGraphConnection::update()
{
	prepareGeometryChange();
	setLine(QLineF(m_pStart->centre(), m_pEnd->centre()));
}
