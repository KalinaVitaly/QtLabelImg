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
    //void mouseClickEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
private:
    QVector<QRect> rectangels;
    QString pathToPhoto;
    bool isPaintStatus;
};

#endif // PHOTOWIDGET_H
