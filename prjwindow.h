#ifndef PRJWINDOW_H
#define PRJWINDOW_H

#include <QMainWindow>

class PrjWindow : public QMainWindow
{
    Q_OBJECT

public:
    PrjWindow(QWidget *parent = 0);
    ~PrjWindow();
};

#endif // PRJWINDOW_H
