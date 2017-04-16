#include "prjwindow.h"
#include "mainwindow.h"
#include "initdb.h"

void addPrj(QSqlQuery &q, const QString &time, const QString &no,  const QString &dev, const QString &con, const QString &code, const QString &prj, const QString &oa,
                const QString &refcode, const QString &refprj, const QString &inheritcode, const QString &inheritprj)
{
    q.addBindValue(time);
    q.addBindValue(no);
    q.addBindValue(dev);
    q.addBindValue(con);
    q.addBindValue(code);
    q.addBindValue(prj);
    q.addBindValue(oa);
    q.addBindValue(refcode);
    q.addBindValue(refprj);
    q.addBindValue(inheritcode);
    q.addBindValue(inheritprj);
    q.exec();
}

PrjWindow::PrjWindow(QWidget *parent)
    : QDialog(parent)
{
    prjui.setupUi(this);
}

PrjWindow::~PrjWindow()
{

}

void PrjWindow::setPrjWinTitle(const QString &title)
{
    prjui.prjwintitle->setText(title);
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

void PrjWindow::on_prjsave_clicked()
{
    QString strNo = this->prjui.no->text();
    QString strDev = this->prjui.dev->text();
    QString strCode = this->prjui.code->text();
    QString strCon = this->prjui.con->toPlainText();

    if (strNo.isEmpty())
    {
        this->prjui.no->setPalette(Qt::red);
    }
    else
    {
        this->prjui.no->setPalette(Qt::white);
    }
    if (strDev.isEmpty())
    {
        this->prjui.dev->setPalette(Qt::red);
    }
    else
    {
        this->prjui.dev->setPalette(Qt::white);
    }
    if (strCode.isEmpty())
    {
        this->prjui.code->setPalette(Qt::red);
    }
    else
    {
        this->prjui.code->setPalette(Qt::white);
    }
    if (strCon.isEmpty())
    {
        this->prjui.con->setPalette(Qt::red);
    }
    else
    {
        this->prjui.con->setPalette(Qt::white);
    }

    if (strNo.isEmpty())
    {
        this->prjui.no->setFocus();
    }
    else if (strDev.isEmpty())
    {
        this->prjui.dev->setFocus();
    }
    else if (strCode.isEmpty())
    {
        this->prjui.code->setFocus();
    }
    else if (strCon.isEmpty())
    {
        this->prjui.con->setFocus();
    }
    else
    {
        // 1 判断以定制单号为限定条件,判断同定制单号记录是否已经存在,存在则判断是否更新
        QDateTime current_date_time = QDateTime::currentDateTime();
        const char * current_date = current_date_time.toString("yyyyMMdd").toStdString().c_str();

        const char * chNo = strNo.toStdString().c_str();
        const char * chDev = strDev.toStdString().c_str();
        const char * chCode = strCode.toStdString().c_str();
        const char * chCon = strCon.toStdString().c_str();

        const char * chOA = this->prjui.oa->text().toStdString().c_str();
        const char * chPrj = this->prjui.prj->text().toStdString().c_str();
        const char * chRefcode = this->prjui.refcode->text().toStdString().c_str();
        const char * chRefprj = this->prjui.refprj->text().toStdString().c_str();
        const char * chInheritCode = this->prjui.inheritcode->text().toStdString().c_str();
        const char * chInheritPrj = this->prjui.inheritprj->text().toStdString().c_str();

        QSqlQuery q;
        if (!q.prepare(QLatin1String("insert into prjinfo(time, no, dev, con, code, prj, oa, refcode, refprj, inheritcode, inheritprj) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")))
            //return q.lastError();
            return;
        addPrj(q,  QLatin1String(current_date), QLatin1String(chNo), QLatin1String(chDev), QLatin1String(chCon), QLatin1String(chCode),QLatin1String(chPrj), QLatin1String(chOA),
                QLatin1String(chRefcode), QLatin1String(chRefprj), QLatin1String(chInheritCode), QLatin1String(chInheritPrj));

        emit refreshPrjList(); // 告诉主窗口刷新项目列表

        this->destroy();
    }
}
