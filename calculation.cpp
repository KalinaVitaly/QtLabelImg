#include "calculation.h"
#include <QDebug>

Calculation::Calculation(QObject *parent) : QObject(parent)
{

}

QMap<QString, QPointF> Calculation::GetDelta()
{
    return delta;
}

QPair<QString, QPointF> Calculation::ParseData(const QString & data)
{
    QPair<QString, QPointF> result;
    result.first = data.left(data.indexOf("x: "));
    result.second.setX(data.mid(data.lastIndexOf("x: ") + 3, data.indexOf(" y:") - data.lastIndexOf("x: ") - 3).toDouble());
    result.second.setY(data.mid(data.lastIndexOf("y: ") + 3, data.size() - data.lastIndexOf("x: ") - 3).toDouble());
//    qDebug() << data << result.first << " " << " " << result.second.x() << " " << result.second.y();
    return result;
}

void Calculation::CalculateDelta()
{
    QList<QString> keys = DataFromFirstListWidget.keys();

    for(auto& i : keys)
    {
        if (DataFromSecondListWidget.contains(i))
        {
            delta[i].setX(DataFromFirstListWidget[i].x() - DataFromSecondListWidget[i].x());
            delta[i].setY(DataFromFirstListWidget[i].y() - DataFromSecondListWidget[i].y());
        }
    }
}

void Calculation::SetData(const QString & data, int numberOfListWidget)
{
    QPair<QString, QPointF> result = ParseData(data);
    if (numberOfListWidget == 0)
    {
        DataFromFirstListWidget[result.first] = result.second;
    }
    else
    {
        DataFromSecondListWidget[result.first] = result.second;
    }
}

void Calculation::WatchData()
{
    QList<QString> keys1 = DataFromFirstListWidget.keys();
    QList<QString> keys2 = DataFromSecondListWidget.keys();
    for(auto& i : keys1)
    {
        qDebug() << "WatchData1:" <<  i << " " << DataFromFirstListWidget[i].x()
                 << " " << DataFromFirstListWidget[i].y();
    }
    for(auto& i : keys2)
    {
        qDebug() << "WatchData2:" <<  i << " " << DataFromSecondListWidget[i].x()
                 << " " << DataFromSecondListWidget[i].y();
    }
    for(auto& i : keys2)
    {
        qDebug() << "Delta:" <<  i << " " << delta[i];
    }
}
