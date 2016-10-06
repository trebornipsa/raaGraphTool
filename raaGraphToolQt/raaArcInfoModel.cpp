#include "stdafx.h"

#include <raaUtilities/raaNode.h>

#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>
#include <raaDataEngine/raaDataNode.h>
#include <raaDataEngine/raaDataLayer.h>
#include <raaDataEngine/raaDataArc.h>

#include "raaModelIndex.h"

#include "raaArcInfoModel.h"
#include "raaArcInfoModel.moc"


raaArcInfoModel::raaArcInfoModel()
{
}

raaArcInfoModel::~raaArcInfoModel()
{
}

QModelIndex raaArcInfoModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent)) return QModelIndex();

	raaNode *pParent = 0;
	raaNode *pChild = 0;

	if (!parent.isValid()) pParent = raaDataEngine::instance()->currentModel();
	else pParent = (raaNode*)parent.internalPointer();

	if (raaDataModel *pDM = dynamic_cast<raaDataModel*>(pParent))
		pChild = pDM->arc(row);

	if (pChild)
	{
		if (raaDataArc *pDA = dynamic_cast<raaDataArc*>(pChild))
		{
			pDA->addListener(this);
			if (!pDA->hasNodeData("raaArcInfoIndex")) pDA->addNodeData("raaArcInfoIndex", new raaModelIndex(row, pParent));
			return createIndex(row, column, pDA);
		}
	}
	return QModelIndex();
}

QModelIndex raaArcInfoModel::parent(const QModelIndex& child) const
{
	return QModelIndex();
}

int raaArcInfoModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0) return 0;
	if (!parent.isValid()) return raaDataEngine::instance()->currentModel()->arcs().size();
	return 0;
}

int raaArcInfoModel::columnCount(const QModelIndex& parent) const
{
	if (parent.row() > 0) return 0;
	return 2;
}

QVariant raaArcInfoModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	if (role != Qt::DisplayRole) return QVariant();

	raaNode *pNode = (raaNode*)index.internalPointer();

	if (raaDataArc *pDA = dynamic_cast<raaDataArc*>(pNode))
	{
		switch (index.column())
		{
		case 0:
			return QVariant(pDA->name().c_str());
		case 1:
			return QVariant(pDA->activityCount());
		default:
			return QVariant();
		}
	}
	return QVariant();
}

void raaArcInfoModel::dataChanged(raaNode* pNode)
{
	if (raaDataArc *pDA = dynamic_cast<raaDataArc*>(pNode))
	{
		if (pDA &&pDA->hasNodeData("raaArcInfoIndex"))
		{
			if(raaModelIndex *pMI = (raaModelIndex*)pDA->nodeData("raaArcInfoIndex"))
				QAbstractItemModel::dataChanged(createIndex(pMI->row(), 0, pNode), createIndex(pMI->row(), 2, pDA));
		}
	}
}