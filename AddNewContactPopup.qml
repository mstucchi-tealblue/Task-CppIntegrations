import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Popup {
    id: addNewContactPopup
    width: 200
    height: 170
    ColumnLayout {
        anchors.fill:parent
        RowLayout {

            Label{
                text:"Name"
            }

            TextArea {
                id: newName
                Layout.fillWidth: true
                placeholderText: "Insert new contact name"
            }
        }
        RowLayout {
            Label{
                text:"Number"
            }

            TextArea {
                id: newNumber
                Layout.fillWidth: true
                placeholderText: "Insert new contact number"
            }
        }

        RowLayout {
            CheckBox {
                id: setFavourite
                property bool state: setFavourite.checked ? true : false
                text: qsTr("Favourite")
            }

        }

        RowLayout {
            Button {
                text: "Ok"
                scale: 0.8
                Layout.alignment: Qt.AlignCenter
                onClicked: {
                    contactList.appendItem(newName.text, newNumber.text, setFavourite.state)
                    newName.text = ""
                    newNumber.text = ""
                    setFavourite.checkState = Qt.Unchecked
                    addNewContactPopup.close()
                }
            }
        }


    }
}
