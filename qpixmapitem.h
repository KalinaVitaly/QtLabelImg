#ifndef QPIXMAPITEM_H
#define QPIXMAPITEM_H

#include <QGraphicsItem>

class QPixMapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit QPixMapItem(QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void sendPoint(QPointF);
};

#endif // QPIXMAPITEM_H
