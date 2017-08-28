import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4


GroupBox {
    property alias btn_Connect: btn_Connect
    title: qsTr("Connection settings")


    GridLayout {
        anchors.fill: parent
        rows: 2
        columns: 3

        Label {
            Layout.row: 1
            Layout.column: 1
            text: qsTr("Serial Port:")
            font.bold: true
            font.pointSize: 10
        }
        ComboBox {
            Layout.row: 1
            Layout.column: 2
            Layout.fillWidth: true
            Layout.minimumWidth: 70
            Layout.maximumWidth: 150
            enabled: !btn_Connect.checked
            id: cmb_SerialPort
            model: serialProperties.availablePorts
        }

        Label {
            Layout.row: 2
            Layout.column: 1
            text: qsTr("Boudrate:")
            font.bold: true
            font.pointSize: 10
        }
        ComboBox {
            Layout.row: 2
            Layout.column: 2
            Layout.fillWidth: true
            Layout.minimumWidth: 70
            Layout.maximumWidth: 150
            enabled: !btn_Connect.checked
            id: cmb_Boudrate
            model: serialProperties.availableBaudrates
            currentIndex: 12
        }
        ToggleButton {
            Layout.row: 1
            Layout.column: 3
            Layout.rowSpan: 2
            id: btn_Connect
            text: qsTr("Connect")
            checked: serialCommunicator.connected
            onClicked: {
                checked ? serialCommunicator.open(cmb_SerialPort.currentText,
                                                  cmb_Boudrate.currentText)
                        : serialCommunicator.close()
            }
        }
    }
}
