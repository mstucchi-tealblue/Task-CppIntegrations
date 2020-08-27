#include "contactlist.h"
#include <iostream>
#include <QDebug>



ContactList::ContactList(QObject *parent) : QObject(parent)
{
    mItems.append({QStringLiteral("Marius"), QStringLiteral("+44 324342432"), true});
    mItems.append({QStringLiteral("Pete"), QStringLiteral("+14 867954309"), false});
    mItems.append({QStringLiteral("Julia"), QStringLiteral("+39 828372819"), true});
    mItems.append({QStringLiteral("Maggie"), QStringLiteral("+21 576324932"), true});
    mItems.append({QStringLiteral("Taylor"), QStringLiteral("+32 324323422"), false});
    mItems.append({QStringLiteral("Lizzy"), QStringLiteral("+99 9783432221"), true});
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

void ContactList::appendItem(QString name, QString number, bool favourite, int index)
{
    if(name.isEmpty() || number.isEmpty())
        return;

    ContactItem item;
    item.name = name;
    item.number = number;
    item.favourite = favourite;

    if( index == -1 ) {
        emit preItemAppended();
        mItems.append(item);
        emit postItemAppended();
    } else {
        emit preItemAppendedAtIndex(index);
        mItems.insert(index, item);
        emit postItemAppendedAtIndex();
    }
}

void ContactList::removeItem(int index)
{
    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();
}

void ContactList::updateItem(int index, QString name, QString number, QString favourite)
{
    bool booleanFavourite = true;
    if( favourite != "Yes" ) booleanFavourite = false;

    //If the item is not the last in the list
    if(mItems.count() != index+1) {
        appendItem(name, number, booleanFavourite, index);
        removeItem(index+1);
    } else {
        appendItem(name, number, booleanFavourite);
        removeItem(mItems.size()-2);
    }
}

QString ContactList::getItemName(int index) {
    return getItems()[index].name;
}

QString ContactList::getItemNumber(int index)
{
    return getItems()[index].number;
}

QString ContactList::getItemFavourite(int index)
{
    if( getItems()[index].favourite ) return QString("Yes");
    return QString("No");
}
