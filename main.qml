import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
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
        TableViewColumn {
                title: "title"
                role: "display"
                width: root.width
                delegate: Text {
                    text: styleData.value + " styleData.index: " + styleData.index
                }
            }
    }
}
