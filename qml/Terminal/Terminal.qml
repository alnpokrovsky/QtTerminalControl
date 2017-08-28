import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

import "../Properties"

ColumnLayout {
    property alias input: input_Cmd

    FileDialog {
        id: dlg_SaveLog
        title: qsTr("Save log to file")
        nameFilters: [ "Log files (*.log *.txt)", "All files (*)" ]
        onAccepted: fileIO.write(fileUrl, textArea.text)
    }

    /*FileDialog {
        id: dlg_Script
        nameFilters: [ "Script files (*.script *.txt)", "All files (*)" ]
        onAccepted: {
            selectExisting ? fileIO.read(fileUrl)
                           : fileIO.write(fileUrl, ser)
        }
    }*/

    RowLayout {
        Layout.fillWidth: true
        Button {
            text: qsTr("Save log")
            onClicked: dlg_SaveLog.open()
        }
        /*Button {
            text: qsTr("Make script")
        }
        Button {
            text: qsTr("Load script")
        }*/
    }

    TextArea {
        id: textArea
        readOnly: true
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.minimumWidth: 350
        wrapMode: TextEdit.Wrap
        text: serialCommunicator.terminalText
        style: TextAreaStyle {
            textColor: "#FEFEFE"
            selectionColor: "steelblue"
            backgroundColor: "black"
        }
        Rectangle {
            anchors.fill: parent
            anchors.margins: -2
            color: "transparent"
            border.width: 1
            border.color: "gray"
        }
    }

    RowLayout {
        Layout.fillWidth: true
        TextField {
            id: input_Cmd
            placeholderText: qsTr("Enter your command")
            Layout.fillWidth: true
            Keys.onReturnPressed: {
                if (serialCommunicator.connected) {
                    serialCommunicator.write(input_Cmd.text)
                    input_Cmd.text = ""
                }
            }
            Keys.onUpPressed: {

            }
            Keys.onDownPressed: {

            }
        }
        Button {
            text: qsTr("Send")
            enabled: serialCommunicator.connected
            onClicked: {
                serialCommunicator.write(input_Cmd.text)
                input_Cmd.text = ""
            }
        }
    }
}
