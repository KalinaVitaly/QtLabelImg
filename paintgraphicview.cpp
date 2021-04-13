#include "paintgraphicview.h"
#include <QDebug>
#include <QScrollBar>

PaintGraphicView::PaintGraphicView(QWidget *parent)
    : QGraphicsView(parent),
      pixmapItem(new QPixMapItem(this)),
      scene(new QGraphicsScene(this)),
      pointItem(nullptr),
      pointSize(8, 8)
{
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);
    connect(pixmapItem, &QPixMapItem::SendPoint, this, &PaintGraphicView::SetQPointF);
    transformSystemCoordinate = transform();
}

void PaintGraphicView::ResizeAndSetQPixmapItem()
{
    //set in the center of scene
    setTransform(transformSystemCoordinate);
    pointSize.first = 8;
    pointSize.second = 8;
    QScrollBar *hsb = horizontalScrollBar();
    QScrollBar *vsb = verticalScrollBar();
    hsb->setValue((hsb->maximum() + hsb->minimum()) / 2);
    vsb->setValue((vsb->maximum() + vsb->minimum()) / 2);
}

QGraphicsScene*  PaintGraphicView::GetScene()
{
    return scene;
}

void PaintGraphicView::mouseReleaseEvent(QMouseEvent *event)
{
    emit NextPixmap();
    //ResizeToStartPosition();
}

QPixMapItem* PaintGraphicView::GetQPixMapItem()
{
    return pixmapItem;
}

QPointF PaintGraphicView::GetCurrentPoint()
{
    return (*points)[pixmapName].GetPoint();
}

void PaintGraphicView::SetPointToScene()
{
    DeletePointItemFromScene();
    pointItem = scene->addEllipse((*points)[pixmapName].GetPoint().x(), (*points)[pixmapName].GetPoint().y(),pointSize.first, pointSize.second,
                                  QPen(Qt::yellow), QBrush(Qt::yellow, Qt::SolidPattern));
}

void PaintGraphicView::SetQPointF(QPointF _point)
{
    (*points)[pixmapName].SetPoint(_point);
    SetPointToScene();
}

void PaintGraphicView::ResizePoint()
{
    if((*points)[pixmapName].GetPointStatus())
    {
        pointItem->setRect((*points)[pixmapName].GetPoint().x(), (*points)[pixmapName].GetPoint().y(),
                           pointSize.first, pointSize.second);
    }
}

void PaintGraphicView::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();
    qreal sf = 1.0 + static_cast<double>(delta.y()) / 600;

    QPoint p0 = mapFromScene(0.0, 0.0);
    int dx = p0.x() - x();

    if (dx < 10 || sf > 1.0)
    {
        scale(sf, sf);
        //        scale(1/sf, 1/sf);
        pointSize.first = pointSize.first / sf;
        pointSize.second = pointSize.second / sf;
        if ((*points)[pixmapName].GetPointStatus())
        {
            ResizePoint();
        }
    }
}

void PaintGraphicView::SetPoints(QMap<QString, Point>& _points)
{
    points = &_points;
}

void PaintGraphicView::DeletePointItemFromScene()
{
    if (pointItem != nullptr && (*points)[pixmapName].GetPointStatus())
    {
        scene->removeItem(pointItem);
        delete pointItem;
        pointItem = nullptr;
    }
}

void PaintGraphicView::SetPixmap(const QString& _pixmapName, const QPixmap& pixmap)
{
    pixmapName = _pixmapName;
    picture = pixmap;
    pixmapItem->setPixmap(pixmap);
    pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable, true);

    scene->addItem(pixmapItem);
    scene->setSceneRect(0, 0, picture.width(), picture.height());

    ResizeAndSetQPixmapItem();

    if ((*points)[pixmapName].GetPointStatus())
    {
        SetPointToScene();
    }
}

PaintGraphicView::~PaintGraphicView()
{
    scene->clear();
    delete  pixmapItem;
    delete scene;
}
