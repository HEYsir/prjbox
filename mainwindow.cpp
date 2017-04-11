#include "mainwindow.h"
#include "prjdelegate.h"
#include "initdb.h"
#include <QtSql>

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
    model->setHeaderData(model->fieldIndex("con"), Qt::Horizontal, tr("需求"));
    model->setHeaderData(model->fieldIndex("code"), Qt::Horizontal, tr("定制源码"));
    model->setHeaderData(model->fieldIndex("prj"), Qt::Horizontal, tr("定制项目SVN"));
    model->setHeaderData(model->fieldIndex("dev"), Qt::Horizontal, tr("设备型号"));
    model->setHeaderData(model->fieldIndex("oa"), Qt::Horizontal, tr("定制OA链接"));
    model->setHeaderData(model->fieldIndex("refcode"), Qt::Horizontal, tr("参考源码"));
    model->setHeaderData(model->fieldIndex("refprj"), Qt::Horizontal, tr("参考项目SVN"));
    model->setHeaderData(model->fieldIndex("inheritcode"), Qt::Horizontal, tr("继承源码"));
    model->setHeaderData(model->fieldIndex("inheritprj"), Qt::Horizontal, tr("继承项目SVN"));
    model->setHeaderData(model->fieldIndex("rating"), Qt::Horizontal, tr("价值度"));

    // Populate the model
    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    // Set the model and hide the ID column
    ui.prjtable->setModel(model);
    ui.prjtable->setItemDelegate(new PrjDelegate(ui.prjtable));
    ui.prjtable->setColumnHidden(model->fieldIndex("id"), true);
    ui.prjtable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Initialize the Author combo box
    //ui.authorEdit->setModel(model->relationModel(authorIdx));
    //ui.authorEdit->setModelColumn(model->relationModel(authorIdx)->fieldIndex("name"));

    //ui.genreEdit->setModel(model->relationModel(genreIdx));
    //ui.genreEdit->setModelColumn(model->relationModel(genreIdx)->fieldIndex("name"));
#if 0
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new BookDelegate(this));
    mapper->addMapping(ui.titleEdit, model->fieldIndex("title"));
    mapper->addMapping(ui.yearEdit, model->fieldIndex("year"));
    mapper->addMapping(ui.authorEdit, authorIdx);
    mapper->addMapping(ui.genreEdit, genreIdx);
    mapper->addMapping(ui.ratingEdit, model->fieldIndex("rating"));

    connect(ui.prjtable->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));
#endif
    ui.prjtable->setCurrentIndex(model->index(0, 0));
}

MainWindow::~MainWindow()
{

}

void MainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}

void MainWindow::addprj_clicked()
{
    this->prj.show();
}
