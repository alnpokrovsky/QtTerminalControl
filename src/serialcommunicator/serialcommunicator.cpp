#include "serialcommunicator.h"

#include <QSerialPort>
#include <QByteArray>

SerialCommunicator::SerialCommunicator(QObject *parent)
    : QObject(parent),
      m_connected(false)
{
    connect(&_serial, QSerialPort::readyRead, this, SerialCommunicator::answered);
}

void SerialCommunicator::write(QByteArray command)
{
    m_terminalText.append("\n\n > " + command + "\n");
    emit terminalTextChanged(m_terminalText);
    _serial.write(command);
}

void SerialCommunicator::open(QString portName, QString baudrate)
{
    _serial.setPortName(portName);
    _serial.setBaudRate(baudrate.toInt());
    if (_serial.open(QIODevice::ReadWrite)) {
        update_connected(true);
    }
}

void SerialCommunicator::close()
{
    _serial.close();
    update_connected(false);
}

void SerialCommunicator::answered()
{
    m_terminalText.append(_serial.readAll());
    emit terminalTextChanged(m_terminalText);
}
