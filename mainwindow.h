#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QListWidgetItem>
#include "paintgraphicview.h"

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
    PaintGraphicView *view;
private:
    void SetFilesInListWidget(QListWidget *);
    void SavePointInFile();
private slots:
    void OpenQFileDialog();
    void ItemDoubleClicked(QListWidgetItem *);
    void SetNextItem();
    void SetBackItem();
};

#endif // MAINWINDOW_H
