#include "qpixmapitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

QPixMapItem::QPixMapItem(QObject *parent)
    : QObject(parent) {}

void QPixMapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << event->pos().x() << " " << event->pos().y();
        emit sendPoint(event->pos());
    }
}

