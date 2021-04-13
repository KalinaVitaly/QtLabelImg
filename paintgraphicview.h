#ifndef PAINTGRAPHICVIEW_H
#define PAINTGRAPHICVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include "point.h"
#include "qpixmapitem.h"
#include <QTransform>

class PaintGraphicView final : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PaintGraphicView(QWidget *parent = nullptr);
    ~PaintGraphicView();
public:
    void SetPixmap(const QString&, const QPixmap&);
    void DeletePointItemFromScene();
    void SetPoints(QMap<QString, Point>&);
    QPointF GetCurrentPoint();
    QPixMapItem *GetQPixMapItem();
    QGraphicsScene* GetScene();
protected:
    void wheelEvent(QWheelEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
private:
    QPixMapItem *pixmapItem;
    QGraphicsScene *scene;
    QPixmap picture;
    QGraphicsEllipseItem *pointItem;
    QPair<qreal, qreal> pointSize;
    QMap<QString, Point> *points;
    QString pixmapName;
    QTransform transformSystemCoordinate;
private:
    void SetPointToScene();
    void ResizePoint();
    void ResizeAndSetQPixmapItem();
private slots:
    void SetQPointF(QPointF);

signals:
    void SendPoint(QPointF);
    void NextPixmap();
};

#endif // PAINTGRAPHICVIEW_H
