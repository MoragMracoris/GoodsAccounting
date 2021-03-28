#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();

    this->setupModel(TABLE,
                     QStringList() << tr("Name")
                                   << tr("Years")
                                   << tr("MainInfo")
                                   << tr("ImagePath")
               );

    this->createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exitBtn_clicked()
{
    QMessageBox::StandardButton questionResult =  QMessageBox::question(this, "Title", "Question text", QMessageBox::Yes | QMessageBox::No);

    if(questionResult == QMessageBox::Yes){
            QApplication::quit();
            return;
    }

    qDebug() << "User selected \"no\"";
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Initializes the data model representation with the installation name
     * in the database table, on which will be accessed in the table
     * */
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    /* Set the columns names in a table with sorted data
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Set Sort Ascending steering column data
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    ui->personsTableView->setModel(model);
    //ui->personsTableView->setColumnHidden(0, true);
    // Allow the selection of lines
    ui->personsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Set selection mode, only one row in table
    ui->personsTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Set the size of the columns by content
    ui->personsTableView->resizeColumnsToContents();
    ui->personsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->personsTableView->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Fetches the data from the table
}
