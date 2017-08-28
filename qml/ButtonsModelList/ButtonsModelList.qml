import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

import "CreationDialog"
import "CreationDialog/UserButton"


ListView {
    property bool flag_Delete : false

    anchors.fill: parent
    model: btnsListModel

    Menu {
        id: menu_RightMouse
        MenuItem {
            text: qsTr("Add button")
            onTriggered: dlg_CreateUserBtn.open()
        }
        MenuItem {
            text: qsTr("Delete mode")
            onTriggered: flag_Delete = !flag_Delete
        }
        MenuItem {
            text: qsTr("Save config")
            onTriggered: {
                dlg_JsonSaveLoad.setSelectExisting(false)
                dlg_JsonSaveLoad.setTitle(qsTr("Save config to JSON"))
                dlg_JsonSaveLoad.open()
            }
        }
        MenuItem {
            text: qsTr("Load config")
            onTriggered: {
                dlg_JsonSaveLoad.setSelectExisting(true)
                dlg_JsonSaveLoad.setTitle(qsTr("Load config from JSON"))
                dlg_JsonSaveLoad.open()
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: menu_RightMouse.popup(mouseX, mouseY)
    }

    delegate: Item {
        id: item
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40

        UserButton {
            anchors.fill: parent
            anchors.margins: 5
            title: model.mtitle
            command: model.mcommand
            parameter: model.mparameter
            output: terminal.input

            Button {
                visible: flag_Delete
                text: qsTr("Delete")
                style: ButtonStyle {
                    background: Rectangle {
                        anchors.fill: parent
                        color: "red"
                        border.width: 2
                        border.color: "black"
                    }
                }
                onClicked: btnsListModel.remove(model.index)
            }
        }
    }

    CreationDialog {
        id: dlg_CreateUserBtn
        onAccepted: {
            btnsListModel.append(btn_title, btn_command, btn_parameter)
        }
    }

    FileDialog {
        id: dlg_JsonSaveLoad
        //shortcuts: shortcuts.home
        nameFilters: [ qsTr("JSON files") + " (*.json *.txt)", qsTr("All files") + " (*)" ]
        onAccepted: {
            if (selectExisting) {
                btnsListModel.fromJsonString(fileIO.read(fileUrl))
            } else {
                fileIO.write(fileUrl, btnsListModel.toJsonString())
            }
        }
    }

}
