#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H

#include <QObject>
#include <QJsonObject>

#include "src/qqmlhelpers.h"


class ButtonElement : public QObject
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(QString, title)
    QML_WRITABLE_PROPERTY(QString, command)
    QML_WRITABLE_PROPERTY(bool, parameter)

public:
    ButtonElement(QObject *parent = 0);
    ButtonElement(QString title, QString command, bool parameter, QObject *parent = 0);

    QJsonObject toJSON();
    static ButtonElement * fromJSON(QJsonObject obj, QObject * parent = 0);

signals:

public slots:
};

#endif // BUTTONELEMENT_H
