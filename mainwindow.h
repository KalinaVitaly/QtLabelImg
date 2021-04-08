#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QListWidgetItem>
#include "paintgraphicview.h"
#include "calculation.h"

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
    QString pathToDir;
    QString pathToPixmap;
    QString pathToTxtFile;
    QString pathToFirstFile;
    QString pathToSecondFile;
    PaintGraphicView *view;
    Calculation *calc;
private:
    void SetFilesInListWidget(QListWidget *, const QStringList &, const QString &);
    void SavePointInFile();
    void SetDataFromListWidgetToCalc(QListWidget *, const QString &, int);
private slots:
    void OpenQFileDialog();
    void ItemDoubleClicked(QListWidgetItem *);
    void CalculateClick();
    void SetNextItem();
    void SetBackItem();
};

#endif // MAINWINDOW_H
