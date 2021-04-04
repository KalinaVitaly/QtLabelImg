#ifndef PHOTOWIDGET_H
#define PHOTOWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class PhotoWidget : public QWidget
{
    Q_OBJECT
public:
    PhotoWidget(QWidget *parent = nullptr);
    void setPathToPhoto(const QString&);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    QString pathToPhoto;
};

#endif // PHOTOWIDGET_H
