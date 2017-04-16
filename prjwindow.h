#ifndef PRJWINDOW_H
#define PRJWINDOW_H

#include <QDialog>
#include "ui_prjwindow.h"
#include <QVariant>
#include <QtSql>

class PrjWindow : public QDialog
{
    Q_OBJECT

public:
    PrjWindow(QWidget *parent = 0);
    void setPrjWinTitle(const QString &title);
    void showPrjInfo(const QModelIndex &index, QSqlRelationalTableModel *model);
    ~PrjWindow();

signals:
    void refreshPrjList();

private slots:
    void on_prjsave_clicked();

private:
    Ui::PrjWindow prjui;
};

#endif // PRJWINDOW_H
