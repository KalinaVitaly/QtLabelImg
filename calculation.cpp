#include "calculation.h"
#include <QDebug>

Calculation::Calculation(QObject *parent) : QObject(parent)
{

}

QMap<QString, QPointF> Calculation::GetDelta()
{
    return delta;
}

QMap<QString, QPointF> Calculation::ParseData(const QString & data)
{
    QMap<QString, QPointF> result;
    QPointF point;
    QStringList lines = data.split(QLatin1Char('\n'), Qt::SkipEmptyParts, Qt::CaseInsensitive);

    for(auto& i : lines)
    {
        point.setX(i.mid(i.lastIndexOf("x: ") + 3, i.indexOf(" y:") - i.lastIndexOf("x: ") - 3).toDouble());
        point.setY(i.mid(i.lastIndexOf("y: ") + 3, i.size() - i.lastIndexOf("x: ") - 3).toDouble());
        result[i.left(i.indexOf("x: ") - 1)] = point;
    }

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
    QMap<QString, QPointF> result = ParseData(data);
    if (numberOfListWidget == 0)
    {
        DataFromFirstListWidget.insert(result);
    }
    else
    {
        DataFromSecondListWidget.insert(result);
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
