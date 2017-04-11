#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QtSql>

#include "ui_mainwindow.h"
#include "prjwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    PrjWindow prj;
    ~MainWindow();

private slots:
    void addprj_clicked();

private:
    void showError(const QSqlError &err);
    Ui::MainWindow ui;
    QSqlRelationalTableModel *model;
};


#endif // MAINWINDOW_H
