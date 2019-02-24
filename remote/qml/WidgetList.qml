import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

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
                width: 40
                height: 40

                x: spacing
                y: spacing
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }

            MouseArea {
                id: mouseArea
                anchors.fill: delegateLayout

                drag.target: draggable

                hoverEnabled: true

                ToolTip
                {
                   visible: mouseArea.containsMouse
                   text: name
                   delay: 700
                }
            }

            Component.onCompleted: {
                if (image.toString() !== "") {
                    img.source = image
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
