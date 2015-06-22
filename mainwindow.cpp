#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "models/sudoku.h"
#include <QDateTime>
#include <QDebug>
void MainWindow::initialize()
{
    if(sudoku)
    {
        delete sudoku;
        sudoku=0;
    }
    sudoku= new Sudoku();
    ui->tableView->setModel(sudoku);
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sudoku = 0;
    initialize();
    ui->tableView->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{  
    //qint64 start = QDateTime::currentMSecsSinceEpoch();
    sudoku->solve();
   // qDebug()<<(QDateTime::currentMSecsSinceEpoch()-start);
}

void MainWindow::on_pushButton_2_clicked()
{
    initialize();
}
