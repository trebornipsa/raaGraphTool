#pragma once

#include <QtGui/QGraphicsLineItem>

class raaGraphNode;

class raaGraphConnection: public QGraphicsLineItem
{
public:
	raaGraphConnection(raaGraphNode *pStart, raaGraphNode *pEnd);
	virtual ~raaGraphConnection(void);

	void update();

protected:
	raaGraphNode *m_pStart;
	raaGraphNode *m_pEnd;
};

