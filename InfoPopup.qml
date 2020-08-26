import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Popup {
    property int contactIndex
    width: 200
    height: 170

    ColumnLayout {
        anchors.fill:parent
        RowLayout {

            Label{
                text:"Name:"
            }

            TextArea {
                id: updateName
                Layout.fillWidth: true
                text: contactList.getItemName(infoPopup.contactIndex)
            }
        }
        RowLayout {
            Label{
                text:"Number:"
            }

            TextArea {
                id: updateNumber
                Layout.fillWidth: true
                text: contactList.getItemNumber(infoPopup.contactIndex)
            }
        }

        RowLayout {
            Label{
                text:"Favourite:"
            }

            TextArea {
                id: updateFavourite
                Layout.fillWidth: true
                text: contactList.getItemFavourite(infoPopup.contactIndex)
            }

        }

        RowLayout {
            Button {
                id: applyButton
                text: qsTr("Apply")
                Layout.fillWidth: true
                onClicked: {
                    contactList.updateItem(contactIndex,updateName.text, updateNumber.text, updateFavourite.text)
                    infoPopup.close()
                }
            }

            Button {
                id: closeButton
                text: qsTr("Close")
                Layout.fillWidth: true
                onClicked: infoPopup.close()
            }
        }
    }

}
