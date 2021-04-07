#include "paintgraphicview.h"
#include <QDebug>
#include <QScrollBar>

PaintGraphicView::PaintGraphicView(QWidget *parent)
    : QGraphicsView(parent),
      pixmapItem(new QPixMapItem(this)),
      scene(new QGraphicsScene(this)),
      pointItem(nullptr),
      pointSize(5, 5),
      isPointSet(false)
{
    setScene(scene);
    connect(pixmapItem, &QPixMapItem::sendPoint, this, &PaintGraphicView::setQPointF);
}

void PaintGraphicView::SetIsPointSet(bool _isPointSet)
{
    isPointSet = _isPointSet;
}

QPointF PaintGraphicView::getPoint()
{
    return point;
}

void PaintGraphicView::setPointToScene()
{
//    if (pointItem != nullptr)
//    {
//        scene->removeItem(pointItem);
//        delete pointItem;
//    }
    DeletePointItem();
    pointItem = scene->addEllipse(point.x(), point.y(),pointSize.first, pointSize.second,
                                  QPen(Qt::yellow), QBrush(Qt::yellow, Qt::SolidPattern));
    isPointSet = true;
}

void PaintGraphicView::setQPointF(QPointF _point)
{
    point = _point;
    setPointToScene();
}

void PaintGraphicView::resizePoint()
{
    if(isPointSet)
    {
        pointItem->setRect(point.x(), point.y(), pointSize.first, pointSize.second);
    }
}

void PaintGraphicView::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();
    qreal sf = 1.0 + static_cast<double>(delta.y()) / 600;
    QPoint p0 = mapFromScene( 0.0, 0.0 );

    if (p0.x() - x() < 10 || sf > 1.0)
    {
        scale(sf, sf);
        pointSize.first = pointSize.first / sf;
        pointSize.second = pointSize.second / sf;
        if (isPointSet)
        {
            resizePoint();
        }
    }
}

void PaintGraphicView::DeletePointItem()
{
    if (pointItem != nullptr && isPointSet)
    {
        scene->removeItem(pointItem);
        delete pointItem;
    }
}

void PaintGraphicView::setPixmap(QPixmap pixmap)
{
    picture = pixmap;
    pixmapItem->setPixmap(pixmap);
    pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene->addItem(pixmapItem);
}
