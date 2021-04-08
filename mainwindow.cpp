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

    ui->radioButton->setChecked(true);
    calc = new Calculation(this);
}

void MainWindow::SetBackItem()
{
    SavePointInFile();
    if(ui->listFilesTabFirst->currentRow() > 0)
    {
        ui->listFilesTabFirst->setCurrentRow(ui->listFilesTabFirst->currentRow() - 1);
        pathToPixmap = pathToDir + "/" + ui->listFilesTabFirst->currentItem()->text();
        ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
    }
    ui->graphicsView->DeletePointItem();
    ui->graphicsView->SetIsPointSet(false);
}

void MainWindow::SetNextItem()
{
    if(ui->listFilesTabFirst->count() > 0)
    {
        if (ui->listFilesTabFirst->currentRow() != -1)
        {
            SavePointInFile();
            if(ui->listFilesTabFirst->count() > ui->listFilesTabFirst->currentRow() + 1)
            {
                ui->listFilesTabFirst->setCurrentRow(ui->listFilesTabFirst->currentRow() + 1);
            }
            ui->graphicsView->DeletePointItem();
            ui->graphicsView->SetIsPointSet(false);
        }
        else
        {
            ui->listFilesTabFirst->setCurrentRow(0);
        }
        pathToPixmap = pathToDir + "/" + ui->listFilesTabFirst->currentItem()->text();
        ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
    }
}

void MainWindow::SavePointInFile()
{
    if (!pathToPixmap.isEmpty())
    {
        WorkWithFiles::savePointToTXTFile(pathToDir, ui->listFilesTabFirst->currentItem()->text(),
                                          ui->graphicsView->getPoint());
    }
}

void MainWindow::OpenQFileDialog()
{
    QStringList filesWithValidFileExtensions;

    if (ui->tabWidget->currentIndex() == 0)
    {
        pathToDir = QFileDialog::getExistingDirectory(this, "Open dir", QDir::homePath());
        filesWithValidFileExtensions << ".jpg" << ".png";
        SetFilesInListWidget(ui->listFilesTabFirst, filesWithValidFileExtensions, pathToDir);
    }
    else if (ui->tabWidget->currentIndex() == 1)
    {
        filesWithValidFileExtensions << ".txt";

        if (ui->radioButton->isChecked())
        {
            pathToFirstFile = QFileDialog::getExistingDirectory(this, "Open dir", QDir::homePath());
            SetFilesInListWidget(ui->listFilesFirstTabSecond, filesWithValidFileExtensions, pathToFirstFile);
        }
        else if (ui->radioButton_2->isChecked())
        {
            pathToSecondFile = QFileDialog::getExistingDirectory(this, "Open dir", QDir::homePath());
            SetFilesInListWidget(ui->listFilesSecondTabSecond, filesWithValidFileExtensions, pathToSecondFile);
        }
    }
}

void MainWindow::SetFilesInListWidget(QListWidget *lf, const QStringList & validFileExtensions, const QString & path)
{
    QStringList list = WorkWithFiles::getDirictoryContent(path);
    QStringList pixmapList;

    for(auto& i : validFileExtensions)
    {
        pixmapList << list.filter(i);
    }

    lf->clear();
    lf->addItems(pixmapList);
}


void MainWindow::SetDataFromListWidgetToCalc(QListWidget *list, const QString &path, int numberOfListWidget)
{
    for(int i = 0; i < list->count(); ++i)
    {
        list->setCurrentRow(i);
        calc->SetData(WorkWithFiles::GetDataFromTXTFile(path + "/" + list->currentItem()->text()), numberOfListWidget);
    }
}

void MainWindow::CalculateClick()
{
    SetDataFromListWidgetToCalc(ui->listFilesFirstTabSecond, pathToFirstFile, 0);
    SetDataFromListWidgetToCalc(ui->listFilesSecondTabSecond, pathToSecondFile, 1);
    calc->CalculateDelta();
    //here
    QString pathToSaveDelta = QFileDialog::getExistingDirectory(this, "Save delta", QDir::homePath());
    QMap<QString, QPointF> delta = calc->GetDelta();
    QList<QString> keys = delta.keys();

    for(auto& i : keys)
    {
        WorkWithFiles::SaveDelta(pathToSaveDelta + "/" + i.left(i.indexOf(".")) + ".txt", QPair<QString, QPointF>(i, delta[i]));
        //qDebug() << i << " " << i.left(i.indexOf("."));
    }
    calc->WatchData();
}

void MainWindow::ItemDoubleClicked(QListWidgetItem *item)
{
    ui->graphicsView->DeletePointItem();
    SavePointInFile();
    ui->graphicsView->SetIsPointSet(false);
    pathToPixmap = pathToDir + "/" + item->text();
    ui->graphicsView->setPixmap(QPixmap(pathToPixmap));
}

MainWindow::~MainWindow()
{
    delete ui;
}
