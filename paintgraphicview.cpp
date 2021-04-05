#include "paintgraphicview.h"
#include <QDebug>

PaintGraphicView::PaintGraphicView(QWidget *parent)
    : QGraphicsView(parent),
      scene(new QGraphicsScene(this))
{
    setScene(scene);
}

void PaintGraphicView::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();
//    qDebug() << delta.x() << " " << delta.y();
    qreal sf = 1.0 + static_cast<double>(delta.y()) / 600;
    qDebug() << delta.x() << " " << delta.y() << " " << sf << " " << static_cast<double>(delta.x()) / 100;
    QPoint p0 = mapFromScene( 0.0, 0.0 );
    if (p0.x() - x()<10 || sf > 1.0)
    {
        scale(sf, sf);
    }
}

void PaintGraphicView::setPixmap(QPixmap pixmap)
{
    picture = pixmap;
    pixItem = scene->addPixmap(pixmap);
}


void PaintGraphicView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        point = event->pos();
        if (pointItem != 0)
        {
            scene->removeItem(pointItem);
        }

        qDebug() << event->x() << " " << event->y();
        pointItem = scene->addEllipse(point.x(), point.y(), 5, 5,
                                      QPen(Qt::yellow), QBrush(Qt::yellow, Qt::SolidPattern));
    }
}
