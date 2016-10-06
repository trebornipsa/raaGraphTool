#pragma once

#include <raaUtilities/raaNodeData.h>

class raaNode;

class raaModelIndex : public raaNodeData
{
public:
	raaModelIndex(unsigned int uiRow, raaNode *pParent);
	~raaModelIndex();
	unsigned int row();
	raaNode *parent();
protected:
	unsigned int m_uiRow;
	raaNode *m_pParent;
};

