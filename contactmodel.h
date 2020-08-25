#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractListModel>

class ContactList;

class ContactModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ContactList *list READ list WRITE setList )

public:
    explicit ContactModel(QObject *parent = nullptr);

    //Defining the model roles
    enum {
        NameRole = Qt::UserRole,
        NumberRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // After the enum I wrote this function
    virtual QHash<int, QByteArray> roleNames() const override;

    //metodi setter e getter
    ContactList *list() const;
    void setList(ContactList *list);

private:
    ContactList *mList;

};

#endif // CONTACTMODEL_H
