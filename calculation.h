#ifndef CALCULATION_H
#define CALCULATION_H

#include <QObject>
#include <QMap>
#include <QPointF>

class Calculation : public QObject
{
    Q_OBJECT
public:
    explicit Calculation(QObject *parent = nullptr);
public:
    void SetData(const QString &, int numberOfListWidget);
    QMap<QString, QPointF> ParseData(const QString &);
    QMap<QString, QPointF> GetDelta();
    void CalculateDelta();
    void WatchData();
private:
    QMap<QString, QPointF> DataFromFirstListWidget;
    QMap<QString, QPointF> DataFromSecondListWidget;
    QMap<QString, QPointF> delta;
};

#endif // CALCULATION_H
