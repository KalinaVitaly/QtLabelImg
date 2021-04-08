#ifndef WORKWITHFILES_H
#define WORKWITHFILES_H

#include <QObject>
#include <QFileInfo>
#include <QDir>

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
    static void SaveDelta(const QString &, const QPointF&);
};

#endif // WORKWITHFILES_H
