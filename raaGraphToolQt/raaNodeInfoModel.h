#pragma once

#include <QtCore/QAbstractItemModel>
#include <raaUtilities/raaNodeListener.h>

class raaNodeInfoModel : public QAbstractItemModel, public raaNodeListener
{
	Q_OBJECT
public:
	raaNodeInfoModel();
	virtual ~raaNodeInfoModel();

	virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
	virtual QModelIndex parent(const QModelIndex& child) const;
	virtual int rowCount(const QModelIndex& parent) const;
	virtual int columnCount(const QModelIndex& parent) const;
	virtual QVariant data(const QModelIndex& index, int role) const;

	virtual void dataChanged(raaNode* pNode);

};

