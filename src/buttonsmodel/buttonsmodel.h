#ifndef BUTTONSMODEL_H
#define BUTTONSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QByteArray>


class ButtonElement;

class ButtonsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        TitleRole = Qt::UserRole + 1,
        CommandRole,
        ParameterRole,
    };

    explicit ButtonsModel(QObject *parent = 0);

    Q_INVOKABLE void append(QString title, QString command, bool parameter);
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE QByteArray toJsonString();
    Q_INVOKABLE bool fromJsonString(QByteArray jsonString);

    // Basic functionality:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ButtonElement*> m_data;
};

#endif // BUTTONSMODEL_H
