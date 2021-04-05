#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QListWidgetItem>

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
    QString filePath;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixItem;
private:
    void setFilesInListWidget();

private slots:
    void OpenQFileDialog();
    void ItemDoubleClicked(QListWidgetItem *);
};

#endif // MAINWINDOW_H
