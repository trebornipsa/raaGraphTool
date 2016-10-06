#include "stdafx.h"
#include "raaModelIndex.h"

raaModelIndex::raaModelIndex(unsigned int uiRow, raaNode *pParent)
{
	m_uiRow = uiRow;
	m_pParent = pParent;
}

raaModelIndex::~raaModelIndex()
{
}

unsigned raaModelIndex::row()
{
	return m_uiRow;
}

raaNode* raaModelIndex::parent()
{
	return m_pParent;
}
