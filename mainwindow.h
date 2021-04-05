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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString dirPath;
    QString pathToPixmap;
    PaintGraphicView *view;
    QPoint point;
private:
    void setFilesInListWidget();

private slots:
    void OpenQFileDialog();
    void OpenQFileDialogToSavePixmap();
    void ItemDoubleClicked(QListWidgetItem *);
};

#endif // MAINWINDOW_H
