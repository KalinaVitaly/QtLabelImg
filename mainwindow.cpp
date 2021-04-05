#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include "workwithfiles.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    //pixItem = scene->addPixmap(QPixmap("C:/Users/v.kalina/Desktop/yolov5/train_data/images/train/1.jpg"));
    QMenu *file = menuBar()->addMenu("File");
    QAction *openDir = new QAction("Open", this);
    file->addAction(openDir);
    connect(openDir, &QAction::triggered, this, &MainWindow::OpenQFileDialog);
}

void MainWindow::OpenQFileDialog()
{
    filePath = QFileDialog::getExistingDirectory(this, "Open dir",QDir::homePath());
    setFilesInListWidget();
    //qDebug() << "FileDialog: " << dirPath;
}

void MainWindow::setFilesInListWidget()
{
    QStringList list = WorkWithFiles::getDirictoryContent(filePath);
    ui->listFiles->clear();
    ui->listFiles->addItems(list);
}

void MainWindow::ItemDoubleClicked(QListWidgetItem *item)
{
    QString pathToPixmap = filePath + "/" + item->text();
    pixItem = scene->addPixmap(QPixmap(pathToPixmap));
}

MainWindow::~MainWindow()
{
    delete ui;
}
