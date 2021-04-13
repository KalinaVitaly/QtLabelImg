#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QListWidgetItem>
#include <QEvent>
#include "paintgraphicview.h"
#include "calculation.h"
#include "point.h"

namespace Ui {
class MainWindow;
}

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMap<QString, Point> points;
    QString pathToDir;
    QString pathToPixmap;
    QString pathToTxtFile;
    QString pathToFirstFile;
    QString pathToSecondFile;
    Calculation *calculation;
private:
    void SetFilesInListWidget(QListWidget *, const QStringList &, QString &);
    void SavePointInFile();
    void SetDataFromListWidgetToCalc(QListWidget *, const QString &, int);
    void AddedStartPoints(const QStringList&);
private slots:
    void OpenQFileDialog();
    void OpenDirForFirstListWidgetClicked();
    void OpenDirForSecondListWidgetClicked();
    void ItemDoubleClicked(QListWidgetItem *);
    void CalculateClicked();
    void SetNextItem();
    void SetBackItem();
    void SetCoordinatesToLabel(QPointF);
};

#endif // MAINWINDOW_H
