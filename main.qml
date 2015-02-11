//------------------------------------------------------------------------------
//      Created : 2015-2-11
//       Author : Dmitry Sokolov <mr.dmitry.sokolov@gmail.com>
//  Description :
//------------------------------------------------------------------------------

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

import My.Controls 1.0

ApplicationWindow {
    id: applicationWindow1
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    CustomItem {
        id: rect1
        anchors.fill: parent
        anchors.margins: 5
        anchors.bottomMargin: 10
    }

    toolBar: ToolBar {
        id: tb1
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("Open")
            }
            ToolButton {
                text: qsTr("Save")
            }
            Item {
                height: 1
                Layout.fillWidth: true
            }
            ToolButton {
                text: qsTr("Exit")
                onClicked: Qt.quit()
            }
        }
    }

    Text {
        id: text1
        color: "#05ff00"
        text: qsTr("Hello World")
        anchors.top: parent.top
        anchors.right: parent.right
    }

}
