import QtQuick 2.11
import QtQml.Models 2.11
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

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
        }


        headerDelegate: Rectangle{

            color: "#bababa"
            height: textItem.implicitHeight * 1.2
            width: textItem.implicitWidth
            // border.color: "#302d2e"
            // border.width: 1
            Text {
                id: textItem
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: styleData.textAlignment
                anchors.leftMargin: 12
                text: styleData.value
                elide: Text.ElideRight
                color: "black"
                font.bold: true
            }
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1
                anchors.topMargin: 1
                width: 1
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
                      ? "grey"
                      : "#5e5a5c")

            height: 20
        }
    }

}
