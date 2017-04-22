/*
 * subclass QSqlRelationalTableModel, reimplementing  Qt::ItemFlags flags(const QModelIndex & index) const
 * default Qt::ItemFlags QAbstractTableModel::flags(const QModelIndex &index) const return ItemIsEnabled and ItemIsSelectable
 * now this project want the special column can be edit. So, more return ItemIsEditable.
 * Then, can press F2 to edit the special column.
*/

#include "exsqlrelationaltablemodel.h"

ExSqlRelationalTableModel::ExSqlRelationalTableModel(QObject *parent)
    :QSqlRelationalTableModel(parent)
{
}

Qt::ItemFlags ExSqlRelationalTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);

    if (index.column() == 1)
        flags |= Qt::ItemIsEditable;

    return flags;
}

ExSqlRelationalTableModel::~ExSqlRelationalTableModel()
{

}
