#include "mainwindow.h"
#include "cplinfo.h"

void addCpl(QSqlQuery &q, const QString &version, const QString &platform,  const QString &cpl, const QString &package, const QString &other, const QString &dev)
{
    q.addBindValue(version);
    q.addBindValue(platform);
    q.addBindValue(cpl);
    q.addBindValue(package);
    q.addBindValue(other);
    q.addBindValue(dev);

    q.exec();
}

CplInfo::CplInfo(QWidget *parent) :
    QDialog(parent)
{
    cplui.setupUi(this);
}

CplInfo::~CplInfo()
{
    delete &cplui;
}

void CplInfo::on_cplsave_clicked()
{
    QString strPlatform = this->cplui.platform->text();
    QString strVersion = this->cplui.version->text();
    QString strCpl = this->cplui.complier->toPlainText();
    QString strPack = this->cplui.pack->toPlainText();
    QString strOther = this->cplui.other->toPlainText();
    QString strDev = this->cplui.dev->text();

    if (strPlatform.isEmpty())
    {
        this->cplui.platform->setPalette(Qt::red);
    }
    else
    {
        this->cplui.platform->setPalette(Qt::white);
    }
    if (strVersion.isEmpty())
    {
        this->cplui.version->setPalette(Qt::red);
    }
    else
    {
        this->cplui.version->setPalette(Qt::white);
    }
    if (strCpl.isEmpty())
    {
        this->cplui.complier->setPalette(Qt::red);
    }
    else
    {
        this->cplui.complier->setPalette(Qt::white);
    }
    if (strPack.isEmpty())
    {
        this->cplui.pack->setPalette(Qt::red);
    }
    else
    {
        this->cplui.pack->setPalette(Qt::white);
    }

    if (strPlatform.isEmpty())
    {
        this->cplui.platform->setFocus();
    }
    else if (strCpl.isEmpty())
    {
        this->cplui.complier->setFocus();
    }
    else
    {
        QSqlQuery q;
        if (!q.prepare(QLatin1String("insert or ignore into cplinfo(version, platform, cpl, package, other, dev) values(?, ?, ?, ?, ?, ?)")))
            //return q.lastError();
            return;

        addCpl(q, strPlatform, strVersion, strCpl, strPack, strOther, strDev);

        q.finish();

        this->destroy();
    }
}

void CplInfo::closeEvent(QCloseEvent *event)
{
    emit revertModel(); // 告诉主窗口子窗口关闭，如果model有未提交修改，则全部撤销

    event->accept();  //接受退出信号，程序退出
}
