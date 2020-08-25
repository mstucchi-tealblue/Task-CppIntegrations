import QtQuick 2.15
import QtQuick.Window 2.15



Window {
    id: root
    visible: true
    width: contactBook.width
    height: contactBook.height + 5

    ContactsBook {
        id: contactBook
    }

}
