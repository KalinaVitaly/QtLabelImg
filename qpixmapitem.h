#ifndef QPIXMAPITEM_H
#define QPIXMAPITEM_H

#include <QGraphicsItem>
#include <QWheelEvent>

class QPixMapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit QPixMapItem(QObject *parent = nullptr);

protected:
    //void wheelEvent(QGraphicsSceneWheelEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMouseEvent(QGraphicsSceneHoverEvent *event) ;

signals:
    void SendPoint(QPointF);
    void SendCurrentCoordinate(QPointF);

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // QPIXMAPITEM_H
