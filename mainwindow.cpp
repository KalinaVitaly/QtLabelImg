#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileInfoList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::OnSearchButtonClicked()
{
    PathToDir = ui->pathEdit->text();
    QStringList list = WorkWithFiles::getDirictoryContent(PathToDir);
    //ui->photosInDir->addItems()
    //qDebug() << "Search button pressed";
}
