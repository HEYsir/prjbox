#ifndef PRJWINDOW_H
#define PRJWINDOW_H

#include <QMainWindow>

#include "ui_prjwindow.h"
#include <QtSql>

class PrjWindow : public QMainWindow
{
    Q_OBJECT

public:
    PrjWindow(QWidget *parent = 0);
    void showPrjInfo(const QModelIndex &index, QSqlRelationalTableModel *model);
    ~PrjWindow();

private:
    Ui::PrjWindow prjui;
};

#endif // PRJWINDOW_H
