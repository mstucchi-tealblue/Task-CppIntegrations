#include "contactlist.h"

ContactList::ContactList(QObject *parent) : QObject(parent)
{
    mItems.append({QStringLiteral("Marius"), QStringLiteral("+44 324342432")});
    mItems.append({QStringLiteral("Pete"), QStringLiteral("+14 867954309")});
}

bool ContactList::setItemAt(int index, const ContactItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const ContactItem &oldItem = mItems.at(index);
    if(item.name == oldItem.name && item.number == oldItem.number)
        return false;

    mItems[index] = item;
    return true;
}

QVector<ContactItem> ContactList::getItems() const
{
    return mItems;
}

void ContactList::appendItem(QString name, QString number)
{
    emit preItemAppended();

    ContactItem item;
    item.name = name;
    item.number = number;
    mItems.append(item);

    emit postItemAppended();

}

void ContactList::removeItem(int index)
{
    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();
}
