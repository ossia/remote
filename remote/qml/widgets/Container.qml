import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4 as QC1
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import com.github.jcelerier.CreativeControls 1.0 as CC

Rectangle {
    id: widg

    property alias container: container
    property alias dropper: dropper
    signal removeMe()

    property var styles: CC.DarkStyle
    opacity: 0.9
    height: 200
    width: 200
    color: "#00000000"
    Drag.dragType: Drag.Internal

    CC.Container {
        id: container
        anchors.fill: parent
    }

    QtObject
    {
        id: dropper
        property var item

        function startDragging(drag)
        {
            container.color = styles.detail
        }

        function stopDragging(drag)
        {
            container.color = styles.background
        }

        function dragging(drag)
        {

        }

        function dropping(drop, centralItem)
        {
            stopDragging(drop)
            var pt = centralItem.mapToItem(container, drop.x, drop.y)

            var drop_fmt = drop.formats[0];
            var drop_text = drop.getDataAsString(drop_fmt);
            if(drop_fmt === "iscore/x-remote-widget")
            {
                centralItem.createObject(drop_text, pt.x, pt.y, widg);
                drop.acceptProposedAction();
            }
            else if(drop_fmt === "iscore/x-remote-address")
            {
                centralItem.createAddress(drop_text, pt.x, pt.y, widg);
                drop.acceptProposedAction();
            }
        }
    }


    MouseArea {
        id: mouseArea
        anchors.fill: widg
        drag.target: widg // Defined in the parent of this object
        preventStealing: true

        Timer {
            id: pressAndHoldTimer
            interval: 300
            onTriggered: pieMenu.popup(mouseArea.mouseX, mouseArea.mouseY);
        }

        onPressed: { pressAndHoldTimer.start(); widg.focus = true }
        onMouseXChanged: {pressAndHoldTimer.stop(); pressAndHoldTimer.start()}
        onMouseYChanged: {pressAndHoldTimer.stop(); pressAndHoldTimer.start()}
        onReleased: pressAndHoldTimer.stop();
    }

    Rectangle {
        id: rect
        color: "orange"
        border.color: Qt.darker(color)
        visible: widg.focus
        width: 10
        height: 10
        x: widg.width
        y: widg.height

        MouseArea {
            id: area
            anchors.fill: rect
            drag.target: rect // Defined in the parent of this object
            preventStealing: true

            onMouseXChanged: if(area.drag.active) widg.width = rect.x
            onMouseYChanged: if(area.drag.active) widg.height = rect.y
        }
    }

    PieMenu {
        id: pieMenu

        triggerMode: TriggerMode.TriggerOnRelease

        QC1.MenuItem {
            iconName: "edit-delete"
            text: "Remove"
            onTriggered: removeMe()
        }

        QC1.MenuItem {
            iconName: "go-up"
            text: "Move up"
            onTriggered: moveUp()
        }

        QC1.MenuItem {
            iconName: "go-down"
            text: "Move down"
            onTriggered: moveDown()
        }
    }
}
