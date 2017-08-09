#ifndef CPLINFO_H
#define CPLINFO_H

#include <QWidget>

namespace Ui {
class cplinfo;
}

class cplinfo : public QWidget
{
    Q_OBJECT

public:
    explicit cplinfo(QWidget *parent = 0);
    ~cplinfo();

private:
    Ui::cplinfo *ui;
};

#endif // CPLINFO_H
