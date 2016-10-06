#include "stdafx.h"
#include <iostream>

#include <raaDataEngine/raaDataArc.h>
#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>
#include <raaDataEngine/raaDataLayer.h>
#include <raaDataEngine/raaDataNode.h>
#include "raaModelIndex.h"
#include "raaLayerModel.h"
#include "raaLayerModel.moc"



raaLayerModel::raaLayerModel()
{
}


raaLayerModel::~raaLayerModel()
{
}

void raaLayerModel::itemClicked(const QModelIndex& index)
{
	if (!index.isValid()) return;

	raaNode *pNode = (raaNode*)index.internalPointer();


	if(raaDataLayer *pDL=dynamic_cast<raaDataLayer*>(pNode))
	{
		switch(index.column())
		{
		case 2:
			if (pDL->active())  pDL->unrefActive();
			else pDL->refActive();
		default:
			return;
		}
	}
}

QModelIndex raaLayerModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent)) return QModelIndex();

	raaNode *pParent = 0;

	if (!parent.isValid()) pParent = raaDataEngine::instance()->currentModel();
	else pParent = (raaNode*)parent.internalPointer();

	raaNode *pChild = 0;
	if (raaDataModel *pDM = dynamic_cast<raaDataModel*>(pParent))
		pChild = pDM->layer(row);
	else if (raaDataLayer *pDL = dynamic_cast<raaDataLayer*>(pParent))
		pChild = pDL->arcs()[row];

	if (pChild)
	{
		if (raaDataLayer *pLayer = dynamic_cast<raaDataLayer*>(pChild))
		{
			if (!pLayer->hasNodeData("QIndex")) pLayer->addNodeData("QIndex", new raaModelIndex(row, pParent));
			return createIndex(row, column, pLayer);;
		}
		else if (raaDataArc *pArc = dynamic_cast<raaDataArc*>(pChild))
		{
			if (!pArc->hasNodeData("QIndex")) pArc->addNodeData("QIndex", new raaModelIndex(row, pParent));
			return createIndex(row, column, pArc);;
		}
	}
	return QModelIndex();
}

QModelIndex raaLayerModel::parent(const QModelIndex& child) const
{
	if (!child.isValid()) return QModelIndex();

	raaNode *pChild = (raaNode*)child.internalPointer();

	if(pChild)
	{
		raaNode *pParent = 0;
		if (pChild->hasNodeData("QIndex"))
		{
			raaModelIndex *pMI = (raaModelIndex*)pChild->nodeData("QIndex");
			if (pParent = pMI ? pMI->parent() : 0)
			{
				if(pParent)
					if (pParent == raaDataEngine::instance()->currentModel()) return QModelIndex(); else return createIndex(pMI->row(), 0, pParent);
			}
		}
	}
	return QModelIndex();
}

int raaLayerModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0) return 0;

	raaNode *pParent = 0;

	if (!parent.isValid()) pParent = raaDataEngine::instance()->currentModel();
	else pParent = (raaNode*)parent.internalPointer();

	if (raaDataModel *pDM = dynamic_cast<raaDataModel*>(pParent))
	{
		return pDM->layers().size();
	}
	else if (raaDataLayer *pDL = dynamic_cast<raaDataLayer*>(pParent))
	{
		return pDL->arcs().size();
	}
	return 0;
}

int raaLayerModel::columnCount(const QModelIndex& parent) const
{
	if (parent.column() > 0) return 0;

	raaNode *pParent = 0;

	if (!parent.isValid()) pParent = raaDataEngine::instance()->currentModel();
	else pParent = (raaNode*)parent.internalPointer();

	if (raaDataModel *pDM = dynamic_cast<raaDataModel*>(pParent))
	{
		return 4;
	}
	else if (raaDataLayer *pDL = dynamic_cast<raaDataLayer*>(pParent))
	{
		return 4;
	}
	else if (raaDataArc *pDA = dynamic_cast<raaDataArc*>(pParent))
	{
		return 2;
	}

	return 0;
}

QVariant raaLayerModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return QVariant();
	if (role!=Qt::DisplayRole) return QVariant();

	raaNode *pNode = (raaNode*)index.internalPointer();

	if (raaDataModel *pDM = dynamic_cast<raaDataModel*>(pNode))
	{
		switch (index.column())
		{
		case 1:
			return QVariant(QString(pDM->name().c_str()));
		case 0:
			return QVariant(QString("Model"));
		default:
			return QVariant();
		}
	}
	else if (raaDataLayer *pDL = dynamic_cast<raaDataLayer*>(pNode))
	{
		switch (index.column())
		{
		case 3:
				return QVariant(pDL->layerStrength());
		case 2:
			if (pDL->active())
				return QVariant(QString("active"));
			else
				return QVariant(QString("inactive"));
		case 1:
			return QVariant(QString(pDL->name().c_str()));
		case 0:
			return QVariant(QString("Layer"));
		default:
			return QVariant();
		}
	}
	else if (raaDataArc *pDA = dynamic_cast<raaDataArc*>(pNode))
	{
		switch (index.column())
		{
		case 2:
			return QVariant();
		case 1:
			return QVariant(QString(pDA->name().c_str()));
		case 0:
			return QVariant(QString("Arc"));
		default:
			return QVariant();
		}
	}
	return QVariant();
}
