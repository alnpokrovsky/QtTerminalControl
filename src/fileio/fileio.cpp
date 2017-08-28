#include "fileio.h"
#include <QFile>
#include <QUrl>
#include <QTextStream>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{
    ;
}

QString FileIO::read(QString mSource)
{
    if (mSource.isEmpty()){
        emit error(tr("Source is empty"));
        return "";
    }

    QFile file(QUrl(mSource).toLocalFile());

    if (!file.open(QIODevice::ReadOnly)) {
        emit error(tr("Unable to open the file"));
        return "";
    }

    QString fileContent;
    QTextStream t( &file );
    fileContent = t.readAll();
    file.close();
    return fileContent;
}

bool FileIO::write(QString mSource, const QString data)
{
    if (mSource.isEmpty()){
        emit error(tr("Source is empty"));
        return false;
    }

    QFile file(QUrl(mSource).toLocalFile());

    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        emit error(tr("Unable to open the file"));
        return false;
    }

    QTextStream out(&file);
    out << data;

    file.close();

    return true;
}
