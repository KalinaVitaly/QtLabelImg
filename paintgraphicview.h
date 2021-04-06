#ifndef PAINTGRAPHICVIEW_H
#define PAINTGRAPHICVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>

#include "qpixmapitem.h"

class PaintGraphicView final : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PaintGraphicView(QWidget *parent = nullptr);
public:
    void setPixmap(QPixmap);
    QPointF getPoint();
    void SetIsPointSet(bool);
    void DeletePointItem();
protected:
    void wheelEvent(QWheelEvent *) override;
private:
    QPixMapItem *pixmapItem;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *pointItem;
    QPixmap picture;
    QPointF point;
    QPair<qreal, qreal> pointSize;
    bool isPointSet;
private:
    void setPointToScene();
    void resizePoint();
private slots:
    void setQPointF(QPointF);
};

#endif // PAINTGRAPHICVIEW_H
