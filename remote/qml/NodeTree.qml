import QtQuick 2.11
import QtQml.Models 2.11
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
Item {
    objectName: "NodeTree"
    TreeView {
        id: nodeView
        model: nodesModel
        objectName: "nodeView"
        anchors.fill: parent

        selection: ItemSelectionModel {
            id: selModel
            model: nodesModel
        }

        TableViewColumn {
            title: "Address"
            role: "address"
            width: 150
            delegate:Rectangle{

                color: "#302d2e"
            }
        }

        itemDelegate: Item {
            id: treeDelegate
            height:70

            MouseArea {
                id: mouseArea
                anchors.fill: text
                drag.target: draggable
                onPressed: {
                    selModel.setCurrentIndex(styleData.index, ItemSelectionModel.ClearAndSelect)
                }
            }

            Text {
                id: text
                anchors.verticalCenter: parent.verticalCenter
                color: styleData.selected ? "#eee" : "#d2d2d2"//"#000"
                elide: styleData.elideMode
                text: styleData.value
                font.pointSize: 10
                font.family: "Helvetica"

                Item {
                    id: draggable
                    width: 0
                    height: 0
                    anchors.fill: parent

                    Drag.active: mouseArea.drag.active
                    Drag.hotSpot.x: 0
                    Drag.hotSpot.y: 0
                    Drag.mimeData: {
                        "iscore/x-remote-address": nodesModel.nodeToAddressString(styleData.index)
                    }
                    Drag.dragType: Drag.Automatic
                }
            }
        }

        rowDelegate: Rectangle {
            color: styleData.selected
                    ? "#aaa"
                    : (styleData.alternate
                       ? "#5e5a5c"
                       : "grey")

            height: 20
        }
    }

}
