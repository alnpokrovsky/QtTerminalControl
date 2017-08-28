#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QString>

class FileIO : public QObject
{
    Q_OBJECT

public:
    FileIO(QObject *parent = nullptr);

    Q_INVOKABLE QString read(QString mSource);
    Q_INVOKABLE bool write(QString mSource, const QString data);

signals:
    void error(const QString& msg);
};

#endif // FILEIO_H
