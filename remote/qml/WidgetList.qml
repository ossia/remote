import QtQuick 2.11
import QtQuick.Layouts 1.3

Item {

    id: widgList
    property real spacing: 0;
    Component {
        id: itemFiller
        Item {
            Layout.fillHeight: true
        }
    }
    Component {
        id: nameDelegate

        Rectangle {
            id: delegateLayout

            height: theView.cellHeight
            width: theView.cellWidth
            color: "transparent"

            Image {
                id: img
                width: theView.cellWidth - 2*spacing
                height: theView.cellHeight - 2*spacing
                x: spacing
                y: spacing
            }

            MouseArea {
                id: mouseArea
                anchors.fill: delegateLayout

                drag.target: draggable

                hoverEnabled: true
                onEntered: if (image.toString() !== "")
                               displayName()
                onExited: if (image.toString() !== "")
                              hideName()
            }
            function displayName() {
                label.opacity = 1.
                nameObj.text = name
            }
            function hideName() {
                label.opacity = 0.
                nameObj.text = ""
            }
            Item {
                id: label

                z: 10
                anchors.fill: parent
                Behavior on opacity {
                    NumberAnimation {
                        easing.type: Easing.InOutQuad
                    }
                }

                Rectangle {
                    color: "grey" //"#302d2e"
                    opacity: 0.9
                    anchors.fill: parent
                }
                Text {
                    id: nameObj

                    text: ""
                    anchors.centerIn: parent

                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 12
                    verticalAlignment: Text.AlignBottom
                    wrapMode: Text.WordWrap
                    font.bold: true
                    color: "#161516"
                }
            }

            Component.onCompleted: {
                if (image.toString() !== "") {
                    img.source = image
                    hideName()
                } else {
                    displayName()
                }

                itemFiller.createObject(delegateLayout, { })
            }

            Item {
                id: draggable
                anchors.fill: delegateLayout

                Drag.active: mouseArea.drag.active
                Drag.hotSpot.x: 10
                Drag.hotSpot.y: 10

                Drag.mimeData: {
                    "iscore/x-remote-widget": name
                }
                Drag.dragType: Drag.Automatic
                Drag.imageSource: dragImageSource != "" ? "qrc:/resources/" + dragImageSource : ""
            }
        }
    }

    GridView {
        id: theView
        model: factoriesModel

        anchors.fill: parent
        highlightFollowsCurrentItem: true
        clip: true
        delegate: nameDelegate

        cellWidth: 60
        cellHeight: 60
    }
}
