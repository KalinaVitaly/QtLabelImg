#include "photowidget.h"
#include <QDebug>

PhotoWidget::PhotoWidget(QWidget *parent)
    : QWidget(parent),
      isPaintStatus(false)
{

}

void PhotoWidget::setPathToPhoto(const QString& path)
{
    pathToPhoto = path;
}

void PhotoWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isPaintStatus) {
        rectangels[rectangels.size() - 1].setTopRight(event->pos());
        update();
    }
}

void PhotoWidget::mousePressEvent(QMouseEvent *event)
{
    rectangels.push_back(QRect(event->x(), event->y(), -1, -1));
    isPaintStatus = true;
    qDebug() << "Mouse press event";
}

void PhotoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    rectangels[rectangels.size() - 1].setTopRight(event->pos());
    isPaintStatus = false;
    update();
}

void PhotoWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPixmap img(pathToPhoto);
    QPainter painter(this);
    painter.drawPixmap(0,0,img);

    this->setFixedSize(img.size());

    painter.setPen(QPen(QBrush(Qt::yellow), 2));
    for(auto& i : rectangels)
    {
       painter.drawRect(i);
    }

}
