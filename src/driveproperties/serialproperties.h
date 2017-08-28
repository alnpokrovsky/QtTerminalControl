#ifndef SERIALPROPERTIES_H
#define SERIALPROPERTIES_H

#include <QObject>
#include <QStringList>
#include <QList>

#include "src/qqmlhelpers.h"

class QTimer;

class SerialProperties : public QObject
{
    Q_OBJECT
    QML_READONLY_PROPERTY(QStringList, availablePorts)
    QML_READONLY_PROPERTY(QStringList, availableBaudrates)
public:
    explicit SerialProperties(QObject *parent = 0);

public slots:
    void updateAvailablePorts();

protected:
    void initAvailableBaudrates();

private:
    QTimer * _timer;
    static const int UPDATE_TIME = 10000;
};

#endif // SERIALPROPERTIES_H
