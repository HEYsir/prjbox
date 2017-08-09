#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QtSql>
#include <QKeyEvent>

#include "ui_mainwindow.h"
#include "exsqlrelationaltablemodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool ListChange;

private slots:
    void refresh_prj_list(bool bListView);
    void revertModelAll();
    void addprj_clicked();
    void deal_popMenuAction(QAction *);

    void on_prjtable_doubleClicked(const QModelIndex &index);

    void on_searchCon_textChanged(const QString &filter);

    void on_prjtable_customContextMenuRequested(const QPoint &pos);

    void on_addcomplier_clicked();

protected slots:
    void keyPressEvent(QKeyEvent *k);

    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                 const QVector<int> &roles = QVector<int> ());

private:
    int versionIdx;
    int platformIdx;
    void showError(const QSqlError &err);
    ExSqlRelationalTableModel *model;
    Ui::MainWindow ui;
    QMenu *popMenu;
    QModelIndex index4TimeEdit;
    void viewAllTable(void);
};


#endif // MAINWINDOW_H
