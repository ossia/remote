import QtQuick 2.11
import QtQuick.Layouts 1.3

Item {

    id: widgList

    Component {
        id: itemFiller
        Item { Layout.fillHeight: true}
    }

    Component {
        id: nameDelegate

        Rectangle
        {
            id: delegateLayout

            height: theView.cellHeight
            width: theView.cellWidth
            color: "grey"

            border.color: "#5e5a5c"
            border.width: 1

            MouseArea {
                id: mouseArea
                anchors.fill: delegateLayout
                drag.target: draggable
            }

            Component.onCompleted: {
                var obj = exampleComponent.createObject(delegateLayout, {});
                obj.enabled = false;
                itemFiller.createObject(delegateLayout, {});
            }

            Item {
                id: draggable
                width: 0
                height: 0
                anchors.fill: parent

                Drag.active: mouseArea.drag.active
                Drag.hotSpot.x: 0
                Drag.hotSpot.y: 0

                Drag.mimeData: { "iscore/x-remote-widget": name }
                Drag.dragType: Drag.Automatic
            }
        }
    }

    GridView {
        id: theView
        model: factoriesModel

        anchors.centerIn: parent
        width: 180
        height: 150

        highlightFollowsCurrentItem: true
        clip: true
        delegate: nameDelegate

        cellWidth: 60
        cellHeight: 75

    }
}
