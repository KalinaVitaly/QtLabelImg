#include "point.h"

Point::Point()
    : status(false)
{}

void Point::SetPoint(const QPointF & _point)
{
    point = _point;
    status = true;
}

void Point::DeletePoint()
{
    status = false;
}

bool Point::GetPointStatus()
{
    return status;
}

void Point::SetCurrentPointStatus(bool _status)
{
    status = _status;
}

QPointF Point::GetPoint() const
{
    return point;
}
