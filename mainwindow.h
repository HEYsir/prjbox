#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QtSql>

#include "ui_mainwindow.h"
#include "exsqlrelationaltablemodel.h"

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

    void on_searchCon_textChanged(const QString &filter);

private:
    void showError(const QSqlError &err);
    ExSqlRelationalTableModel *model;
    Ui::MainWindow ui;
    void viewAllTable(void);
};


#endif // MAINWINDOW_H
