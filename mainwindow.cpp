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
    SavePointInFile();
    if(ui->listFiles->currentRow() > 0)
    {
        ui->listFiles->setCurrentRow(ui->listFiles->currentRow() - 1);
        pathToPixmap = pathToDir + "/" + ui->listFiles->currentItem()->text();
        ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
        ui->graphicsView->DeletePointItem();
    }
    ui->graphicsView->SetIsPointSet(false);
}

void MainWindow::SetNextItem()
{
    if(ui->listFiles->count() > 0)
    {
        if (ui->listFiles->currentRow() != -1)
        {
            SavePointInFile();
            if(ui->listFiles->count() > ui->listFiles->currentRow() + 1)
            {
                ui->listFiles->setCurrentRow(ui->listFiles->currentRow() + 1);
                ui->graphicsView->DeletePointItem();
            }
            ui->graphicsView->SetIsPointSet(false);
        }
        else
        {
            ui->listFiles->setCurrentRow(0);
        }
        pathToPixmap = pathToDir + "/" + ui->listFiles->currentItem()->text();
        ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
    }
}

void MainWindow::SavePointInFile()
{
    if (!pathToDir.isEmpty() && !pathToPixmap.isEmpty())
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
    ui->graphicsView->DeletePointItem();
    ui->graphicsView->SetIsPointSet(false);
    pathToPixmap = pathToDir + "/" + item->text();
    ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
}

MainWindow::~MainWindow()
{
    delete ui;
}
