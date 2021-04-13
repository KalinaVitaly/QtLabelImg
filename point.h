#ifndef POINT_H
#define POINT_H

#include <QMap>
#include <QPointF>

class Point final
{
public:
    explicit Point();
public:
    void SetPoint(const QPointF &);
    void SetCurrentPointStatus(bool);
    void DeletePoint();
    bool GetPointStatus();
    QPointF GetPoint() const;

private:
    QString pixmapName;
    QPointF point;
    bool status;
};

#endif // POINT_H
