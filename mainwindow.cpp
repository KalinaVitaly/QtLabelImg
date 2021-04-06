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
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu *file = menuBar()->addMenu("File");
    QAction *openDir = new QAction("Open", this);
    file->addAction(openDir);
    connect(openDir, &QAction::triggered, this, &MainWindow::OpenQFileDialog);
}

void MainWindow::SetBackItem()
{
    if(ui->listFiles->currentRow() > 0)
    {
        ui->listFiles->setCurrentRow(ui->listFiles->currentRow() - 1);
        pathToPixmap = pathToDir + "/" + ui->listFiles->currentItem()->text();
        ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
    }
}

void MainWindow::SetNextItem()
{
    if(ui->listFiles->count() > ui->listFiles->currentRow() + 1)
    {
        ui->listFiles->setCurrentRow(ui->listFiles->currentRow() + 1);
        pathToPixmap = pathToDir + "/" + ui->listFiles->currentItem()->text();
        ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
    }
    SavePointInFile();
}

void MainWindow::SavePointInFile()
{
    if (!pathToDir.isEmpty())
    {
        WorkWithFiles::savePointToTXTFile(pathToDir, ui->listFiles->currentItem()->text(),
                                          ui->graphicsView->getPoint());
    }
}

void MainWindow::OpenQFileDialog()
{
    pathToDir = QFileDialog::getExistingDirectory(this, "Open dir", QDir::homePath());
    setFilesInListWidget();
}

void MainWindow::setFilesInListWidget()
{
    QStringList list = WorkWithFiles::getDirictoryContent(pathToDir);
    QStringList pixmapList;
    pixmapList << list.filter(".jpg") << list.filter(".png");
    ui->listFiles->clear();
    ui->listFiles->addItems(pixmapList);
}

void MainWindow::ItemDoubleClicked(QListWidgetItem *item)
{
    pathToPixmap = pathToDir + "/" + item->text();
    ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
}

MainWindow::~MainWindow()
{
    delete ui;
}
