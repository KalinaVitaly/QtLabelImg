#ifndef WORKWITHFILES_H
#define WORKWITHFILES_H

#include <QObject>
#include <QFileInfo>
#include <QDir>
#include "point.h"

class WorkWithFiles final : public QObject
{
    Q_OBJECT
public:
    explicit WorkWithFiles(QObject *parent = nullptr) = delete;
    WorkWithFiles(const WorkWithFiles&) = delete;
    WorkWithFiles& operator=(const WorkWithFiles&) = delete;

    static QStringList getDirictoryContent(const QString&);
    static QString GetDataFromTXTFile(const QString &);
    static void savePointToTXTFile(const QString &, const QString &, const QPointF&);
    static void SavePointsInOneFile(const QPair<QString, Point>&, const QString&);
    static void SaveDelta(const QString &, const QPair<QString, QPointF> &);
};

#endif // WORKWITHFILES_H
