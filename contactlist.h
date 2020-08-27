#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QObject>
#include <QVector>

//creo l'item che popolerà la lista
struct ContactItem
{
    QString name;
    QString number;
    bool favourite;

};

class ContactList : public QObject
{
    Q_OBJECT
public:
    explicit ContactList(QObject *parent = nullptr);

    bool setItemAt(int index, const ContactItem &item);

    QVector<ContactItem> getItems() const;


signals:
    void preItemAppended();
    void postItemAppended();
    void preItemAppendedAtIndex(int index);
    void postItemAppendedAtIndex();
    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem(QString name, QString number, bool favourite, int index = -1);
    void removeItem(int index);
    void updateItem(int index, QString name, QString number, QString favourite);

    QString getItemName(int index);
    QString getItemNumber(int index);
    QString getItemFavourite(int index);



private:
    QVector<ContactItem> mItems;


};

#endif // CONTACTLIST_H
