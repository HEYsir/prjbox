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
    Qt::ItemFlags flags = QSqlTableModel::flags(index);

    if (index.column() == 1)
       flags |= Qt::ItemIsEditable;

    return flags;
}

ExSqlRelationalTableModel::~ExSqlRelationalTableModel()
{

}

QVariant ExSqlRelationalTableModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;


    if (!index.isValid())
        return QVariant();

    QSqlRelationalTableModel *tmp = (QSqlRelationalTableModel *)index.model();
    QModelIndex itemIndex = tmp->index(index.row(), tmp->fieldIndex("finprj"), QModelIndex());
    if (Qt::BackgroundColorRole == role)
    {

        if (!itemIndex.data().toString().isEmpty())
        {
            return QSqlRelationalTableModel::data(index, role);
        }

        if (tmp->fieldIndex("deadline") == index.column())
        {
            QString timestring = index.data(Qt::DisplayRole).toString();
            if (timestring.isEmpty())
            {
                return QColor(Qt::magenta);
            }
            QDate time = QDate::fromString(timestring, "yyyyMMdd");
            QDate Curtime =QDate::currentDate();
            if (Curtime > time)
            {
                return QColor(Qt::red);
            }
            else if (Curtime >= time.addDays(-2))
            {
                return QColor(Qt::yellow);
            }
            else
            {
                return QColor(Qt::green);
            }
        }
        else
        {
             return QSqlRelationalTableModel::data(index, role);
        }
    }
    else
    {
        return QSqlRelationalTableModel::data(index, role);
    }
}
