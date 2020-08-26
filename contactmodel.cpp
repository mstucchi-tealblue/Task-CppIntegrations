#include "contactmodel.h"
#include "contactlist.h"

ContactModel::ContactModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int ContactModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->getItems().size();
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    //After namesRole() implementation I implemented the data function
    const ContactItem item = mList->getItems().at(index.row());
    switch(role) {
    case NameRole:
        return QVariant(item.name);
    case NumberRole:
        return QVariant(item.number);
    case FavouriteRole:
        return QVariant(item.favourite);
    }

    return QVariant();
}

bool ContactModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    ContactItem item = mList->getItems().at(index.row());
    switch(role) {
    case NameRole:
        item.name = value.toString();
        break;
    case NumberRole:
        item.number = value.toString();
        break;
    case FavouriteRole:
        item.favourite = value.toBool();
        break;
    }

    if (mList->setItemAt(index.row(),item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ContactModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

//Implementation after enum
QHash<int, QByteArray> ContactModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[NumberRole] = "number";
    names[FavouriteRole] = "favourite";
    return names;

}

ContactList *ContactModel::list() const
{
    return mList;
}

void ContactModel::setList(ContactList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList) {
        connect(mList, &ContactList::preItemAppended, this, [=]() {
            const int index = mList->getItems().size();
            beginInsertRows(QModelIndex(),index,index);
        });

        connect(mList, &ContactList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &ContactList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(),index, index);
        });

        connect(mList, &ContactList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
