#include "paintgraphicview.h"
#include <QDebug>
#include <QScrollBar>

PaintGraphicView::PaintGraphicView(QWidget *parent)
    : QGraphicsView(parent),
      scene(new QGraphicsScene(this))
{
    setScene(scene);
}

void PaintGraphicView::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();
    qreal sf = 1.0 + static_cast<double>(delta.y()) / 600;
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
        QScrollBar *pHorizantalScrollBar = horizontalScrollBar();
        QScrollBar *pVerticalScrollBar = verticalScrollBar();

        point = event->pos();
        if (pointItem != 0)
        {
            scene->removeItem(pointItem);
        }
        pointItem = scene->addEllipse(point.x() + pHorizantalScrollBar->value(), point.y() + pVerticalScrollBar->value(), 5, 5,
                                      QPen(Qt::yellow), QBrush(Qt::yellow, Qt::SolidPattern));
    }
}
