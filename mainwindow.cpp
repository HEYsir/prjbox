#include "mainwindow.h"
#include "prjwindow.h"
#include "prjdelegate.h"
#include <QtSql>

QSqlError initDb()
{
    QString dbFileName = "localprj.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFileName);

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("prjinfo", Qt::CaseInsensitive))
       return QSqlError();

    QSqlQuery q;
    if (!q.exec(QLatin1String("create table prjinfo(id integer, time varchar, no varchar primary key, dev varchar, con varchar, code varchar, prj varchar, oa varchar,"
                              "refcode varchar, refprj varchar, inheritcode varchar, inheritprj varchar)")))
        return q.lastError();

    return QSqlError();

}

void MainWindow::viewAllTable(void)
{
    model->setTable("prjinfo");

    // Remember the indexes of the columns
    //authorIdx = model->fieldIndex("author");
    //genreIdx = model->fieldIndex("genre");

    // Set the relations to the other database tables
    //model->setRelation(authorIdx, QSqlRelation("authors", "id", "name"));
    //model->setRelation(genreIdx, QSqlRelation("genres", "id", "name"));

    // Set the localized header captions
    model->setHeaderData(model->fieldIndex("no"), Qt::Horizontal, tr("定制单号与主题"));
    model->setHeaderData(model->fieldIndex("dev"), Qt::Horizontal, tr("设备型号"));
    model->setHeaderData(model->fieldIndex("time"), Qt::Horizontal, tr("开发时间"));

    // Populate the model
    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    // Set the model and hide the ID column
    ui.prjtable->setModel(model);
    // model->removeColumns(4,8);

    // 设置列宽
    ui.prjtable->setColumnWidth(model->fieldIndex("time"), 100);
    ui.prjtable->setColumnWidth(model->fieldIndex("no"), 500);
    //ui.prjtable->setColumnWidth(model->fieldIndex("dev"), 200);
    ui.prjtable->horizontalHeader()->setStretchLastSection(true);   // 最后一列填充剩余空间

    //ui.prjtable->setItemDelegate(new PrjDelegate(ui.prjtable));

    ui.prjtable->setColumnHidden(model->fieldIndex("id"), true);
    ui.prjtable->setColumnHidden(model->fieldIndex("con"), true);
    ui.prjtable->setColumnHidden(model->fieldIndex("code"), true);
    ui.prjtable->setColumnHidden(model->fieldIndex("prj"), true);
    ui.prjtable->setColumnHidden(model->fieldIndex("oa"), true);
    ui.prjtable->setColumnHidden(model->fieldIndex("refcode"), true);
    ui.prjtable->setColumnHidden(model->fieldIndex("refprj"), true);
    ui.prjtable->setColumnHidden(model->fieldIndex("inheritcode"), true);
    ui.prjtable->setColumnHidden(model->fieldIndex("inheritprj"), true);

    ui.prjtable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.prjtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui.prjtable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.prjtable->horizontalHeader()->setHighlightSections(false);

    ui.prjtable->setCurrentIndex(model->index(0, 0));

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.addprj, SIGNAL(clicked()), this, SLOT(addprj_clicked()));

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(this, "Unable to load database", "This demo needs the SQLITE driver");

    // initialize the database
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

    // Create the data model
    model = new ExSqlRelationalTableModel(ui.prjtable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    this->viewAllTable();
}

MainWindow::~MainWindow()
{

}

void MainWindow::refresh_prj_list(bool bListView)
{
    if (bListView)
    {
        model->database().transaction(); //开始事务操作
        if (model->submitAll())
        {
            model->database().commit(); //提交
        } else
        {
            model->database().rollback(); //回滚
            QMessageBox::warning(this, tr("tableModel"),
                                 tr("数据库错误: %1")
                                 .arg(model->lastError().text()));
        }
    }
    // Populate the model
    if (!model->select()) {
        showError(model->lastError());
        return;
    }
}

void MainWindow::revertModelAll()
{
    // Revert the model
    model->revertAll();
    // Populate the model
    if (!model->select()) {
        showError(model->lastError());
        return;
    }
}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}

void MainWindow::addprj_clicked()
{
    PrjWindow *addprj = new PrjWindow(this);
    //addprj->setPrjWinTitle("新增项目开发记录");
    addprj->bListView = false;
    addprj->show();

    connect(addprj, SIGNAL(refreshPrjList(bool)), this, SLOT(refresh_prj_list(bool)));
}


void MainWindow::on_prjtable_doubleClicked(const QModelIndex &index)
{
    PrjWindow *prj = new PrjWindow(this);
    prj->bListView = true;
    prj->setPrjWinTitle("定制项目详细信息");
    prj->showPrjInfo(index, model);

    connect(prj, SIGNAL(revertModel()), this, SLOT(revertModelAll()));

    connect(prj, SIGNAL(refreshPrjList(bool)), this, SLOT(refresh_prj_list(bool)));
}

void MainWindow::on_searchCon_textChanged(const QString &filter)
{
    QString sqlkey;
    QString searchKey = ui.searchItem->currentText();
    QString searchCon = ui.searchCon->text();

    if (searchKey == tr("主题")) {
        sqlkey = tr("no");
    } else if (searchKey == tr("开发时间")) {
        sqlkey = tr("time");
    } else if (searchKey == tr("单号")) {
        sqlkey = tr("no");
    } else if (searchKey == tr("型号/平台")) {
        sqlkey = tr("dev");
    } else{
        ui.searchItem->setCurrentIndex(0);
        sqlkey = tr("dev");
    }

    //模糊查询
    if (!searchCon.isEmpty())
    {
        //模糊查询
        //sqlite3_exec(pSQLiteSOEdb,"PRAGMA case_sensitive_like = 0;",0,0,0); //查询时不区分大小写
        //SELECT * FROM tb WHERE fn like N string
        //TEXT类型的,先转成UTF-8再入库,LIKE查询问题,完美解决.

        QString subFilter = QString().sprintf("%s like '%%%s%%'", sqlkey.toUtf8().data(), filter.toUtf8().data());
        model->setFilter(subFilter); //进行筛选
        model->select(); //显示结果
    }
    else
    {
        this->viewAllTable();
    }
}

