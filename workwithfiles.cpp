#include "workwithfiles.h"
#include <QDebug>

QStringList WorkWithFiles::getDirictoryContent(const QString& path)
{
    QDir dir(path);
    QFileInfoList list;
    QStringList stringList;

    if (!dir.exists()) {
        qWarning("The directory does not exist");
        exit(1);
    }

    dir.setFilter(QDir::Files);
    list = dir.entryInfoList();

    foreach (QFileInfo finfo, list)
    {
        QString name = finfo.fileName();
        stringList.append(name);
        //qDebug() << name;
    }
    return stringList;
}
