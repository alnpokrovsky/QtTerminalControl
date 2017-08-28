import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import "UserButton"

Dialog {
    property string btn_title: input_Title.text
    property string btn_command: input_Command.text
    property bool btn_parameter: chkbox_Parameter.checked


    title: qsTr("User's button creation")

    standardButtons: StandardButton.Save | StandardButton.Cancel

    ColumnLayout {
        anchors.fill: parent

        GridLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            columns: 2
            rows: 3
            rowSpacing: 10
            columnSpacing: 5

            Label {
                text: qsTr("Button's title:")
            }
            TextField {
                id: input_Title
                Layout.fillWidth: true
                text: qsTr("Title")
            }

            Label {
                text: qsTr("Command:")
            }
            TextField {
                id: input_Command
                Layout.fillWidth: true
                text: qsTr("Command")
            }

            CheckBox {
                id: chkbox_Parameter
                text: qsTr("Parameter:")
            }

            ComboBox {
                enabled: chkbox_Parameter.checked
                Layout.fillWidth: true
                anchors.margins: 5
                model: [qsTr("Number")]
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"
        }

        GroupBox {
            title: qsTr("View")
            Layout.columnSpan: 2
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent

                UserButton {
                    title: input_Title.text
                    command: input_Command.text
                    parameter: chkbox_Parameter.checked
                    output: input_Try

                }

                TextField {
                    id: input_Try
                    Layout.fillWidth: true
                    placeholderText: qsTr("Try command")
                }
            }
        }
    }
}
