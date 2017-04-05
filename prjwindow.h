#ifndef PRJWINDOW_H
#define PRJWINDOW_H

#include <QMainWindow>

#include "ui_prjwindow.h"

class PrjWindow : public QMainWindow
{
    Q_OBJECT

public:
    PrjWindow(QWidget *parent = 0);
    ~PrjWindow();

private:
    Ui::PrjWindow prjui;
};

#endif // PRJWINDOW_H
