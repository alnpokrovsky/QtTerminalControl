import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import "Terminal"
import "Properties"
import "ButtonsModelList"

Window {
    visible: true
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("Drive control")

    SplitView {
        anchors.fill: parent
        anchors.margins: 5
        //spacing: 10

        Terminal {
            id: terminal
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 350
            anchors.margins: 5
        }

        ColumnLayout {
            Layout.minimumWidth: 350
            anchors.margins: 10

            Properties {
                Layout.minimumWidth: 350
                Layout.fillWidth: true
            }

            GroupBox {
                title: qsTr("Commands")
                Layout.fillWidth: true
                Layout.fillHeight: true

                ScrollView {
                    anchors.fill: parent

                    ButtonsModelList {
                        anchors.fill: parent
                    }
                }
            }
        }
    }
}
