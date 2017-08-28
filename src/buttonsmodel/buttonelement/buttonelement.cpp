#include "buttonelement.h"

ButtonElement::ButtonElement(QObject *parent) : QObject(parent)
{
    ;
}

ButtonElement::ButtonElement(QString title, QString command, bool parameter, QObject *parent)
    : QObject(parent),
      m_title(title),
      m_command(command),
      m_parameter(parameter)
{
    ;
}

QJsonObject ButtonElement::toJSON()
{
    QJsonObject obj;
    obj["title"] = get_title();
    obj["command"] = get_command();
    obj["parameter"] = get_parameter();
    return obj;
}

ButtonElement * ButtonElement::fromJSON(QJsonObject obj, QObject *parent)
{
    QString title = obj["title"].toString();
    QString command = obj["command"].toString();
    bool parameter = obj["parameter"].toBool();

    return new ButtonElement(title, command, parameter, parent);
}
