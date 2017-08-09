#ifndef CPLINFO_H
#define CPLINFO_H

#include <QWidget>
#include <QCloseEvent>
#include <QDialog>
#include "ui_cplinfo.h"
#include <QVariant>
#include <QtSql>

namespace Ui {
class cplinfo;
}

class CplInfo : public QDialog
{
    Q_OBJECT

public:
    explicit CplInfo(QWidget *parent = 0);
    ~CplInfo();

private slots:
    void on_cplsave_clicked();

signals:
    void revertModel();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::cplinfo cplui;
};

#endif // CPLINFO_H
