#include "qpixmapitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

QPixMapItem::QPixMapItem(QObject *parent)
    : QObject(parent)
{
    setAcceptHoverEvents(true);
}

void QPixMapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit SendPoint(event->pos());
    }
}

void QPixMapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    emit SendCurrentCoordinate(event->pos());
}
