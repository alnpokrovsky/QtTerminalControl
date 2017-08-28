#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <QObject>
#include <QString>
#include <QSerialPort>

#include "src/qqmlhelpers.h"

class QSerialPort;

class SerialCommunicator : public QObject
{
Q_OBJECT
QML_READONLY_PROPERTY(QString, terminalText)
QML_READONLY_PROPERTY(bool, connected)

public:
    explicit SerialCommunicator(QObject *parent = 0);

    Q_INVOKABLE void write(QByteArray command);
    Q_INVOKABLE void open(QString portName, QString baudrate);
    Q_INVOKABLE void close();
signals:

public slots:
    void answered();

private:
    QSerialPort _serial;
};

#endif // SERIALCOMMUNICATOR_H
