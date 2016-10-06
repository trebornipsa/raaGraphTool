#pragma once

#include <QtCore/QAbstractItemModel>

class raaLayerModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
	virtual QModelIndex parent(const QModelIndex& child) const;
	virtual int rowCount(const QModelIndex& parent) const;
	virtual int columnCount(const QModelIndex& parent) const;
	virtual QVariant data(const QModelIndex& index, int role) const;
	raaLayerModel();
	virtual ~raaLayerModel();

	void itemClicked(const QModelIndex&);
};

