/*
 * subclass QSqlRelationalTableModel, reimplementing  Qt::ItemFlags flags(const QModelIndex & index) const
 * default Qt::ItemFlags QAbstractTableModel::flags(const QModelIndex &index) const return ItemIsEnabled and ItemIsSelectable
 * now this project want the special column can be edit. So, more return ItemIsEditable.
 * Then, can press F2 to edit the special column.
*/
#ifndef EXSQLRELATIONALTABLEMODEL_H
#define EXSQLRELATIONALTABLEMODEL_H

#include <QtWidgets>
#include <QtSql>

class ExSqlRelationalTableModel : public QSqlRelationalTableModel
{

public:
    ExSqlRelationalTableModel(QObject *parent = 0);
    ~ExSqlRelationalTableModel();

    Qt::ItemFlags flags( const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // EXSQLRELATIONALTABLEMODEL_H
