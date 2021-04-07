#include "workwithfiles.h"
#include <QDebug>
#include <QTextStream>
#include <QPoint>

QStringList WorkWithFiles::getDirictoryContent(const QString& path)
{
    QDir dir(path);
    QFileInfoList list;
    QStringList stringList;

    if (!dir.exists())
    {
        qWarning("The directory does not exist");
        exit(1);
    }

    dir.setFilter(QDir::Files);
    list = dir.entryInfoList();

    foreach (QFileInfo finfo, list)
    {
        QString name = finfo.fileName();
        stringList.append(name);
    }
    return stringList;
}

void WorkWithFiles::savePointToTXTFile(const QString &path, const QString &pixmapName, const QPointF& data)
{
    //qDebug() << path + "/" + pixmapName.leftRef(pixmapName.lastIndexOf(".")) + ".txt";
    QFile file(path + "/" + pixmapName.leftRef(pixmapName.lastIndexOf(".")) + ".txt");

    if (file.open(QIODevice::WriteOnly))
    {
        qDebug() << pixmapName;
        QTextStream out(&file);
        out << pixmapName << "\n";
        out << "x: " << data.x() << " y: " << data.y();
    }

    file.close();
}
