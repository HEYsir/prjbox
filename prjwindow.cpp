#include "prjwindow.h"
#include "mainwindow.h"

PrjWindow::PrjWindow(QWidget *parent)
    : QMainWindow(parent)
{
    prjui.setupUi(this);
}

PrjWindow::~PrjWindow()
{

}

void PrjWindow::showPrjInfo(const QModelIndex &index, QSqlRelationalTableModel *model)
{
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);

    mapper->setModel(model);

    //mapper->setItemDelegate(new BookDelegate(this));
    mapper->addMapping(this->prjui.no, model->fieldIndex("no"));
    mapper->addMapping(this->prjui.dev, model->fieldIndex("dev"));
    mapper->addMapping(this->prjui.con, model->fieldIndex("con"));
    mapper->addMapping(this->prjui.code, model->fieldIndex("code"));
    mapper->addMapping(this->prjui.prj, model->fieldIndex("prj"));
    mapper->addMapping(this->prjui.oa, model->fieldIndex("oa"));
    mapper->addMapping(this->prjui.refcode, model->fieldIndex("refcode"));
    mapper->addMapping(this->prjui.refprj, model->fieldIndex("refprj"));
    mapper->addMapping(this->prjui.inheritcode, model->fieldIndex("inheritcode"));
    mapper->addMapping(this->prjui.inheritprj,  model->fieldIndex("inheritprj"));

    mapper->setCurrentModelIndex(index);

    this->show();
}
