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
    calculation(new Calculation(this))
{
    ui->setupUi(this);
    ui->graphicsView->SetPoints(points);

    connect(ui->graphicsView, &PaintGraphicView::NextPixmap, this, &MainWindow::SetNextItem);
    connect(ui->graphicsView->GetQPixMapItem(), &QPixMapItem::SendCurrentCoordinate, this, &MainWindow::SetCoordinatesToLabel);

    setMinimumSize(1200, 600);
}



void MainWindow::SetCoordinatesToLabel(QPointF point)
{
    ui->CoordinatesLabel->setText("x: " + QString::number(point.x(), 'f', 2) + " y: " + QString::number(point.y(), 'f', 2));
}


void MainWindow::SetBackItem()
{
    SavePointInFile();
    ui->graphicsView->DeletePointItemFromScene();
    if(ui->listFilesTabFirst->currentRow() > 0)
    {
        ui->listFilesTabFirst->setCurrentRow(ui->listFilesTabFirst->currentRow() - 1);
        pathToPixmap = pathToDir + "/" + ui->listFilesTabFirst->currentItem()->text();
        ui->graphicsView->SetPixmap(ui->listFilesTabFirst->currentItem()->text(), QPixmap(pathToPixmap));
    }
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
            ui->graphicsView->DeletePointItemFromScene();
        }
        else
        {
            ui->listFilesTabFirst->setCurrentRow(0);
        }
        pathToPixmap = pathToDir + "/" + ui->listFilesTabFirst->currentItem()->text();
        ui->graphicsView->SetPixmap(ui->listFilesTabFirst->currentItem()->text(), QPixmap(pathToPixmap));
    }
}

void MainWindow::SavePointInFile()
{
    if (!pathToPixmap.isEmpty())
    {
        QString pixmapName = ui->listFilesTabFirst->currentItem()->text();
        WorkWithFiles::SavePointsInOneFile(qMakePair(pixmapName, points[pixmapName]), pathToDir);
//        WorkWithFiles::savePointToTXTFile(pathToDir, ui->listFilesTabFirst->currentItem()->text(),
//                                          ui->graphicsView->GetCurrentPoint());
    }
}

void MainWindow::OpenDirForFirstListWidgetClicked()
{
    QStringList filesWithValidFileExtensions;
    filesWithValidFileExtensions << ".txt";
    SetFilesInListWidget(ui->listFilesFirstTabSecond, filesWithValidFileExtensions, pathToFirstFile);
}

void MainWindow::OpenDirForSecondListWidgetClicked()
{
    QStringList filesWithValidFileExtensions;
    filesWithValidFileExtensions << ".txt";
    SetFilesInListWidget(ui->listFilesSecondTabSecond, filesWithValidFileExtensions, pathToSecondFile);
}

void MainWindow::OpenQFileDialog()
{
    ui->graphicsView->DeletePointItemFromScene();
    points.clear();
    ui->graphicsView->GetScene()->removeItem(ui->graphicsView->GetQPixMapItem());

    QStringList filesWithValidFileExtensions;
    filesWithValidFileExtensions << ".jpg" << ".png";
    SetFilesInListWidget(ui->listFilesTabFirst, filesWithValidFileExtensions, pathToDir);
}

void MainWindow::SetFilesInListWidget(QListWidget *lf, const QStringList & validFileExtensions, QString & path)
{
    path = QFileDialog::getExistingDirectory(this, "Open dir", QDir::homePath());
    QStringList list = WorkWithFiles::getDirictoryContent(path);
    QStringList pixmapList;

    for(auto& i : validFileExtensions)
    {
        pixmapList << list.filter(i);
    }

    AddedStartPoints(pixmapList);

    lf->clear();
    lf->addItems(pixmapList);
}

void MainWindow::AddedStartPoints(const QStringList& list)
{
    points.clear();

    for(auto& i : list)
    {
        points[i] = Point();
    }
}

void MainWindow::SetDataFromListWidgetToCalc(QListWidget *list, const QString &path, int numberOfListWidget)
{
    for(int i = 0; i < list->count(); ++i)
    {
        list->setCurrentRow(i);
        calculation->SetData(WorkWithFiles::GetDataFromTXTFile(path + "/" + list->currentItem()->text()), numberOfListWidget);
    }
}

void MainWindow::CalculateClicked()
{
    SetDataFromListWidgetToCalc(ui->listFilesFirstTabSecond, pathToFirstFile, 0);
    SetDataFromListWidgetToCalc(ui->listFilesSecondTabSecond, pathToSecondFile, 1);
    calculation->CalculateDelta();

    QString pathToSaveDelta = QFileDialog::getExistingDirectory(this, "Save delta", QDir::homePath());
    QMap<QString, QPointF> delta = calculation->GetDelta();
    QList<QString> keys = delta.keys();

    for(auto& i : keys)
    {
        WorkWithFiles::SaveDelta(pathToSaveDelta + "/" + i.left(i.indexOf(".")) + ".txt", QPair<QString, QPointF>(i, delta[i]));
    }
}

void MainWindow::ItemDoubleClicked(QListWidgetItem *item)
{
    ui->graphicsView->DeletePointItemFromScene();
    SavePointInFile();
    pathToPixmap = pathToDir + "/" + item->text();
    ui->graphicsView->SetPixmap(item->text(), QPixmap(pathToPixmap));
}

MainWindow::~MainWindow()
{
    delete calculation;
    delete ui;
}
