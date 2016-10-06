#include "stdafx.h"

#include <raaUtilities/raaNode.h>

#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>
#include <raaDataEngine/raaDataNode.h>
#include <raaDataEngine/raaDataLayer.h>
#include <raaDataEngine/raaDataArc.h>

#include "raaModelIndex.h"

#include "raaNodeInfoModel.h"
#include "raaNodeInfoModel.moc"

raaNodeInfoModel::raaNodeInfoModel()
{
}

raaNodeInfoModel::~raaNodeInfoModel()
{
}

QModelIndex raaNodeInfoModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent)) return QModelIndex();

	raaNode *pParent = 0;
	raaNode *pChild = 0;

	if (!parent.isValid()) pParent = raaDataEngine::instance()->currentModel();
	else pParent = (raaNode*)parent.internalPointer();

	if (raaDataModel *pDM = dynamic_cast<raaDataModel*>(pParent))
		pChild = pDM->node(row);

	if(pChild)
	{
		if(raaDataNode *pDN=dynamic_cast<raaDataNode*>(pChild))
		{
			pDN->addListener(this);
			if(!pDN->hasNodeData("raaNodeInfoIndex")) pDN->addNodeData("raaNodeInfoIndex", new raaModelIndex(row, pParent));
			return createIndex(row, column, pDN);
		}
	}
	return QModelIndex();
}

QModelIndex raaNodeInfoModel::parent(const QModelIndex& child) const
{
	return QModelIndex();
}

int raaNodeInfoModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0) return 0;
	if (!parent.isValid()) return raaDataEngine::instance()->currentModel()->nodes().size();
	return 0;
}

int raaNodeInfoModel::columnCount(const QModelIndex& parent) const
{
	if (parent.row() > 0) return 0;
	return 2;
}

QVariant raaNodeInfoModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	if (role != Qt::DisplayRole) return QVariant();

	raaNode *pNode = (raaNode*)index.internalPointer();

	if(raaDataNode *pDN=dynamic_cast<raaDataNode*>(pNode))
	{
		switch(index.column())
		{
		case 0:
			return QVariant(pDN->name().c_str());
		case 1:
			return QVariant(pDN->activityCount());
		default:
			return QVariant();
		}
	}
	return QVariant();
}

void raaNodeInfoModel::dataChanged(raaNode* pNode)
{
	if (raaDataNode *pDN = dynamic_cast<raaDataNode*>(pNode))
	{
		if (pDN && pDN->hasNodeData("raaNodeInfoIndex"))
		{
			if(raaModelIndex *pMI = (raaModelIndex*)pDN->nodeData("raaModeInfoIndex"))
				QAbstractItemModel::dataChanged(createIndex(pMI->row(), 0, pNode), createIndex(pMI->row(), 2, pDN));
		}
	}
}