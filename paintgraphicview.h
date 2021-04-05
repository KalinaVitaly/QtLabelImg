#ifndef PAINTGRAPHICVIEW_H
#define PAINTGRAPHICVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>

class PaintGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PaintGraphicView(QWidget *parent = nullptr);

    void setPixmap(QPixmap);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;

private:
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixItem;
    QGraphicsEllipseItem *pointItem;
    QPixmap picture;
    QPointF point;
};

#endif // PAINTGRAPHICVIEW_H
