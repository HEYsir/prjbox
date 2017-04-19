#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QtSql>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void refresh_prj_list(bool bListView);
    void revertModelAll();
    void addprj_clicked();

    void on_prjtable_doubleClicked(const QModelIndex &index);

private:
    void showError(const QSqlError &err);
    QSqlRelationalTableModel *model;
    Ui::MainWindow ui;
};


#endif // MAINWINDOW_H
