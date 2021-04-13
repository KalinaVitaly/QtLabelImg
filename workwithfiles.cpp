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

void WorkWithFiles::SavePointsInOneFile(const QPair<QString, Point>& data, const QString& pathToDir)
{
    QFile file(pathToDir + "/result.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(&file);
        out << data.first << " x: " << data.second.GetPoint().x()
            << " y: " << data.second.GetPoint().y() << "\n";
    }

    file.close();
}

void WorkWithFiles::savePointToTXTFile(const QString &path, const QString &pixmapName, const QPointF& data)
{
    QFile file(path + "/" + pixmapName.leftRef(pixmapName.lastIndexOf(".")) + ".txt");

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << pixmapName << " x: " << data.x() << " y: " << data.y();
    }

    file.close();
}

void WorkWithFiles::SaveDelta(const QString &path, const QPair<QString, QPointF> &delta)
{
   QFile file(path);

   if (file.open(QIODevice::WriteOnly))
   {
       QTextStream out(&file);
       out << delta.first << " x: " << delta.second.x() << " y: " << delta.second.y();
   }

   file.close();
}

QString WorkWithFiles::GetDataFromTXTFile(const QString &pathFile)
{
    QFile file(pathFile);
    QTextStream in(&file);
    QString line;

    if (!file.open(QIODevice::ReadOnly)) {
      qWarning("Cannot open file for reading");
    }

    while (!in.atEnd())
    {
      line += in.readLine() + "\n";
    }

    file.close();
    return line;
}
