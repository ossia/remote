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
            width: parent.width * 0.9
        }
        backgroundVisible: false

        style: TreeViewStyle{
            branchDelegate: Image{
                source: styleData.isExpanded ?
                            "qrc:///resources/branch_open.png"
                          : "qrc:///resources/branch_closed.png"
                fillMode: Image.PreserveAspectFit
            }
            headerDelegate: Rectangle{

                color: "#777777"// "#302d2e"// "#bababa"
               // border.color: "#dcdcdc"
               // border.width: 1

                height: textItem.implicitHeight //* 1.2
                width: textItem.implicitWidth

                Text {
                    id: textItem
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: styleData.textAlignment
                    anchors.leftMargin: 12
                    text: styleData.value
                    elide: Text.ElideRight

                    color: "#302d2e"// "black"
                    font.bold: true
                    font.capitalization: Font.AllUppercase
                }
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
                   : "#302d2e"/*(styleData.alternate
                      ? "grey"
                      : "#5e5a5c")*/

            height: 20
        }
    }

}
