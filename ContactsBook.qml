import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import ContactM 1.0

ColumnLayout {
    Frame {
        id: root
        Layout.fillWidth: true
         RowLayout {
            ColumnLayout{
                ListView {
                    id: book
                    implicitWidth: 250
                    implicitHeight: 250
                    clip: true
                    //anchors.fill: parent
                    model: ContactModel {
                        id: contactModel
                        list: contactList
                    }

                    delegate: ColumnLayout {
                        TextArea {
                            id: contactName
                            Layout.fillWidth: true
                            text: model.name + "\n" + model.number
                            color: activeFocus ? "red":"black"
                            visible:  favouriteButton.active ? model.favourite : model
                            MouseArea {
                                anchors.fill: parent
                                onClicked: book.currentIndex = model.index
                                onDoubleClicked: {
                                    infoPopup.x = root.width/2 - infoPopup.width/2;
                                    infoPopup.y = root.height/2 - infoPopup.height/2;
                                    infoPopup.contactIndex = model.index
                                    infoPopup.open()
                                }
                            }
                        }
                    }
                    highlight: Rectangle {
                        color: "lightgreen"
                        Behavior on y {
                            SpringAnimation {
                                spring: 3
                                damping: 0.2
                            }
                        }
                    }

                }
            }

            ColumnLayout {
                Button {
                    property bool active: false
                    id: favouriteButton
                    text: "Show only preferred"
                    onClicked: active = !active
                }
            }

        }
    }

    RowLayout
    {
        Button {
            text: qsTr("Add contact")
            Layout.fillWidth: true
            onClicked: {
                addNewContactPopup.x = root.width/2 - addNewContactPopup.width/2;
                addNewContactPopup.y = root.height/2 - addNewContactPopup.height/2;
                addNewContactPopup.open()
            }

        }
        Button {
            text: qsTr("Remove contact")
            Layout.fillWidth: true
            onClicked: contactList.removeItem(book.currentIndex)
        }
    }

    AddNewContactPopup {
        id: addNewContactPopup
    }

    InfoPopup {
        id: infoPopup
    }


}




