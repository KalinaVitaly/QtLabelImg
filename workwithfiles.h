#ifndef WORKWITHFILES_H
#define WORKWITHFILES_H

#include <QObject>
#include <QFileInfo>
#include <QDir>

class WorkWithFiles : public QObject
{
    Q_OBJECT
public:
    explicit WorkWithFiles(QObject *parent = nullptr) = delete;
    WorkWithFiles(const WorkWithFiles&) = delete;
    WorkWithFiles& operator=(const WorkWithFiles&) = delete;

    static QStringList getDirictoryContent(const QString&);

};

#endif // WORKWITHFILES_H
