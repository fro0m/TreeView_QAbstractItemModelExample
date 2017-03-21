import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import ggh.model 1.0

Window {
    id:root
    visible: true
    width: 1100
    height: 480
    title: qsTr("Hello World")
    TestModel {id: mdl}

    TreeView {
        id: treeView
        anchors.fill: parent
        model: mdl
        property var toMove: []
        signal tryToMove()
        onTryToMove: {
            if (toMove.length == 2) {
                mdl.moveRow(toMove[0], toMove[1])
                toMove = []
            }
        }

        TableViewColumn {
            title: "title"
            role: "display"
            width: root.width
            delegate: RowLayout {
                Rectangle {
                    id: moveBtn
                    height: parent.height
                    Layout.preferredWidth: 40
                    color: "red"
                    radius: 5
                    border {
                        color: "black"
                        width: 2
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            treeView.toMove.push(styleData.index)
                            treeView.tryToMove()
                        }
                    }
                }

                Text {
                    Layout.fillWidth: true
                    text: styleData.value + " styleData.index: " + styleData.index
                }
            }
        }
    }
}
