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

            border.color: "#302d2e"
            border.width: 1


            MouseArea {
                id: mouseArea
                anchors.fill: delegateLayout

                drag.target: draggable

                hoverEnabled: true
                onEntered: displayName()
                onExited: hideName()
            }
            function displayName(){
                label.opacity = 1.;
                nameObj.text = name;
            }
            function hideName(){
                label.opacity = 0.;
                nameObj.text = "";
            }
            Item{
                id: label

                z: 10
                anchors.fill: parent
                opacity: 0
                Behavior on opacity {NumberAnimation{easing.type: Easing.InOutQuad}}


                Rectangle{
                    color:  "grey"//"#302d2e"
                    opacity: 0.9
                    border.width: 1
                    border.color: "#302d2e"
                    anchors.fill: parent
                }
                Text{
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
            Image {
                source: image
            }

            Component.onCompleted: {
                itemFiller.createObject(delegateLayout, {});
            }

            Item {
                id: draggable
                anchors.fill: delegateLayout

                Drag.active: mouseArea.drag.active
                Drag.hotSpot.x: 10
                Drag.hotSpot.y: 10

                Drag.mimeData: { "iscore/x-remote-widget": name }
                Drag.dragType: Drag.Automatic
                Drag.imageSource: dragImageSource != "" ? "qrc:/resources/" + dragImageSource : ""
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
        cellHeight: 60

    }


}
