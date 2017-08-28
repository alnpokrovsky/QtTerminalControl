#include "serialproperties.h"

#include <QSerialPortInfo>
#include <QStringList>
#include <QTimer>
#include <QtAlgorithms>

SerialProperties::SerialProperties(QObject *parent)
    : QObject(parent),
      _timer(new QTimer(this))
{
    connect(_timer, &QTimer::timeout, this, SerialProperties::updateAvailablePorts);
    initAvailableBaudrates();
    updateAvailablePorts();
    _timer->start(UPDATE_TIME);
}

void SerialProperties::updateAvailablePorts()
{
    QStringList updatedPorts;
    bool needUpdate = false;

    for (const QSerialPortInfo &serialPortInfo : QSerialPortInfo::availablePorts()) {
        updatedPorts.append(serialPortInfo.portName());
        if (!m_availablePorts.contains(serialPortInfo.portName())) {
            needUpdate = true;
        }
    }

    if (needUpdate || m_availablePorts.length() != updatedPorts.length())
    {
        update_availablePorts(updatedPorts);
    }
}

void SerialProperties::initAvailableBaudrates()
{
    QStringList baudrates;
    for (const qint32 & br : QSerialPortInfo::standardBaudRates()){
        baudrates.append(QString::number(br));
    }
    update_availableBaudrates(baudrates);
}
