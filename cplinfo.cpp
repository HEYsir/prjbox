#include "cplinfo.h"
#include "ui_cplinfo.h"

cplinfo::cplinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cplinfo)
{
    ui->setupUi(this);
}

cplinfo::~cplinfo()
{
    delete ui;
}
