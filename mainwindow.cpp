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
    view(new PaintGraphicView(this))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(view);
    QMenu *file = menuBar()->addMenu("File");
    QAction *openDir = new QAction("Open", this);
    QAction *savePixmap = new QAction("Save", this);
    file->addAction(openDir);
    file->addAction(savePixmap);
    connect(openDir, &QAction::triggered, this, &MainWindow::OpenQFileDialog);
}

void MainWindow::OpenQFileDialogToSavePixmap()
{

}

void MainWindow::OpenQFileDialog()
{
    dirPath = QFileDialog::getExistingDirectory(this, "Open dir",QDir::homePath());
    setFilesInListWidget();
    //qDebug() << "FileDialog: " << dirPath;
}

void MainWindow::setFilesInListWidget()
{
    QStringList list = WorkWithFiles::getDirictoryContent(dirPath);
    QStringList pixmapList;
    pixmapList << list.filter(".jpg") << list.filter(".png");
    ui->listFiles->clear();
    ui->listFiles->addItems(pixmapList);
}

void MainWindow::ItemDoubleClicked(QListWidgetItem *item)
{
    pathToPixmap = dirPath + "/" + item->text();
    view->setPixmap(QPixmap(pathToPixmap));
}

MainWindow::~MainWindow()
{
    delete ui;
}
