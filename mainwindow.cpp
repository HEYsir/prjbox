#include "mainwindow.h"
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
    if (!q.exec(QLatin1String("create table prjinfo(id integer primary key, time varchar, no varchar, dev varchar, con varchar, code varchar, prj varchar, oa varchar,"
                              "refcode varchar, refprj varchar, inheritcode varchar, inheritprj varchar)")))
        return q.lastError();

    return QSqlError();

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
    model = new QSqlRelationalTableModel(ui.prjtable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("prjinfo");

    // Remember the indexes of the columns
    //authorIdx = model->fieldIndex("author");
    //genreIdx = model->fieldIndex("genre");

    // Set the relations to the other database tables
    //model->setRelation(authorIdx, QSqlRelation("authors", "id", "name"));
    //model->setRelation(genreIdx, QSqlRelation("genres", "id", "name"));

    // Set the localized header captions
    model->setHeaderData(model->fieldIndex("no"), Qt::Horizontal, tr("定制单号"));
    model->setHeaderData(model->fieldIndex("dev"), Qt::Horizontal, tr("设备型号"));
    model->setHeaderData(model->fieldIndex("time"), Qt::Horizontal, tr("开发时间"));

    // Populate the model
    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    model->removeColumns(4,8);
    // Set the model and hide the ID column
    ui.prjtable->setModel(model);
    //ui.prjtable->setItemDelegate(new PrjDelegate(ui.prjtable));
    ui.prjtable->setColumnHidden(model->fieldIndex("id"), true);
    ui.prjtable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.prjtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.prjtable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Initialize the Author combo box
    //ui.authorEdit->setModel(model->relationModel(authorIdx));
    //ui.authorEdit->setModelColumn(model->relationModel(authorIdx)->fieldIndex("name"));

    //ui.genreEdit->setModel(model->relationModel(genreIdx));
    //ui.genreEdit->setModelColumn(model->relationModel(genreIdx)->fieldIndex("name"));

    ui.prjtable->setCurrentIndex(model->index(0, 0));
}

MainWindow::~MainWindow()
{

}

void MainWindow::refresh_prj_list()
{
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
    QDialog *addprj = new PrjWindow(this);
    //addprj->setPrjWinTitle("新增项目开发记录");

    addprj->show();

    connect(addprj, SIGNAL(refreshPrjList()), this, SLOT(refresh_prj_list()));

}


void MainWindow::on_prjtable_doubleClicked(const QModelIndex &index)
{
    prj.setPrjWinTitle("定制项目详细信息");
    prj.showPrjInfo(index, model);
}
