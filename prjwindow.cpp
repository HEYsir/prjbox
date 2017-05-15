#include "prjwindow.h"
#include "mainwindow.h"

void addPrj(QSqlQuery &q, const QString &time, const QString &no,  const QString &dev, const QString &con, const QString &code, const QString &prj, const QString &oa,
                const QString &refcode, const QString &refprj, const QString &inheritcode, const QString &inheritprj, const QString &platform, const QString &version, const QString &deadline)
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
    q.addBindValue(platform);
    q.addBindValue(version);
    q.addBindValue(deadline);

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
    mapper->addMapping(this->prjui.platform, model->fieldIndex("platform"));
    mapper->addMapping(this->prjui.version, model->fieldIndex("version"));
    mapper->addMapping(this->prjui.deadline,  model->fieldIndex("deadline"));

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
        if (!this->bListView)
        {
            // 1 判断以定制单号为限定条件,判断同定制单号记录是否已经存在,存在则判断是否更新
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString current_date = current_date_time.toString("yyyyMMdd");

            QString chOA = this->prjui.oa->text();
            QString chPrj = this->prjui.prj->text();
            QString chRefcode = this->prjui.refcode->text();
            QString chRefprj = this->prjui.refprj->text();
            QString chInheritCode = this->prjui.inheritcode->text();
            QString chInheritPrj = this->prjui.inheritprj->text();
            QString strVersion = this->prjui.version->text();
            QString strDeadline = this->prjui.deadline->text();

            QString strPlatform = this->prjui.platform->text();

            QSqlQuery q;
            if (!q.prepare(QLatin1String("insert or ignore into prjinfo(time, no, dev, con, code, prj, oa, refcode, refprj, inheritcode, inheritprj, platform, version, deadline) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")))
                //return q.lastError();
                return;

            addPrj(q,  current_date, strNo, strDev, strCon, strCode,chPrj, chOA, chRefcode, chRefprj, chInheritCode, chInheritPrj, strPlatform, strVersion, strDeadline);

            q.finish();
        }

        emit refreshPrjList(this->bListView); // 告诉主窗口刷新项目列表
        this->destroy();
    }
}

void PrjWindow::closeEvent(QCloseEvent *event)
{
    emit revertModel(); // 告诉主窗口子窗口关闭，如果model有未提交修改，则全部撤销

    event->accept();  //接受退出信号，程序退出
}
