#include "photowidget.h"
#include <QDebug>

PhotoWidget::PhotoWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

void PhotoWidget::setPathToPhoto(const QString& path)
{
    pathToPhoto = path;
}

void PhotoWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->x() << " " << event->y();
}

void PhotoWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPixmap img(pathToPhoto);
    QPainter painter(this);
    painter.drawPixmap(0,0,img);
    this->setFixedSize(img.size());
}
