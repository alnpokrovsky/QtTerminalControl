import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1


RowLayout {
    property string title: "Title"
    property string command: "Command"
    property bool parameter: false
    property TextField output

    anchors.fill: parent

    SpinBox {
        id: input_Parameter
        visible: parameter
        Layout.fillWidth: true
        Layout.minimumWidth: 50
    }
    Button {
        Layout.fillWidth: true
        text: title
        onClicked: {
            output.text = command + (input_Parameter.visible ? input_Parameter.value : "")
        }
    }
}
