#include "buttonsmodel.h"

#include "buttonelement/buttonelement.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>


QHash<int, QByteArray> ButtonsModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[TitleRole] = "mtitle";
    roles[CommandRole] = "mcommand";
    roles[ParameterRole] = "mparameter";
    return roles;
}

ButtonsModel::ButtonsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    ;
}

QByteArray ButtonsModel::toJsonString()
{
    QJsonArray btnsArray;
    for (ButtonElement * btn : m_data) {
        btnsArray.append(btn->toJSON());
    }
    QJsonObject obj;
    obj["buttons"] = btnsArray;
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson();
}

bool ButtonsModel::fromJsonString(QByteArray jsonString)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonString);
    if (!doc.object()["buttons"].isArray())
        return false;
    QJsonArray array = doc.object()["buttons"].toArray();

    this->removeRows(0,rowCount());

    beginInsertRows(QModelIndex(), rowCount(), array.size()-1);
    for (const QJsonValueRef & ref : array) {
        m_data << ButtonElement::fromJSON(ref.toObject(), this);
    }
    endInsertRows();
    return true;
}

int ButtonsModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant ButtonsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case TitleRole:
        return m_data[index.row()]->get_title();
    case CommandRole:
        return m_data[index.row()]->get_command();
    case ParameterRole:
        return m_data[index.row()]->get_parameter();
    default:
        return QVariant();
    }
}

Qt::ItemFlags ButtonsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool ButtonsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid()) {
        //m_data.replace(index.row(), value.value<ButtonElement*>());
        switch (role) {
        case TitleRole:
            m_data[index.row()]->set_title(value.toString());
            break;
        case CommandRole:
            m_data[index.row()]->set_command(value.toString());
            break;
        case ParameterRole:
            m_data[index.row()]->set_parameter(value.toBool());
            break;
        default:
            break;
        }

        emit dataChanged(index,index);
        return true;
    }
    return false;
}

bool ButtonsModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    if (index.isValid()) {
        m_data[index.row()]->set_title(roles.value(TitleRole).toString());
        m_data[index.row()]->set_command(roles.value(CommandRole).toString());
        m_data[index.row()]->set_parameter(roles.value(ParameterRole).toBool());
        return true;
    }
    return false;
}

void ButtonsModel::append(QString title, QString command, bool parameter)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << new ButtonElement(title,command,parameter,this);
    endInsertRows();
}

void ButtonsModel::remove(int row)
{
    removeRows(row, 1);
}

bool ButtonsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        m_data.insert(row, new ButtonElement(this));
    }
    endInsertRows();
    return true;
}

bool ButtonsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0)
        return false;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        delete m_data.at(row);
        m_data.removeAt(row);
    }
    endRemoveRows();
    return true;
}
