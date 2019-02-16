import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

import QtQuick.Dialogs 1.3

CentralAreaForm {
    Layout.fillWidth: true
    Layout.fillHeight: true

    FileDialog {
        id: fileDialog
        visible: false
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: false
        onAccepted: {
            if(selectExisting)
                centralItem.load(fileDialog.fileUrls[0])
            else
                centralItem.save(fileDialog.fileUrls[0])
        }
    }
    Shortcut {
        sequence: StandardKey.Open
        onActivated: {
            fileDialog.selectExisting = true
            fileDialog.visible = true
        }
    }

    Shortcut {
        sequence: StandardKey.Save
        onActivated: {
            fileDialog.selectExisting = false
            fileDialog.visible = true
        }
    }

    ScrollView
    {
        id: scrollView

        anchors.fill: parent
        frameVisible: true
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOn
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn

        Rectangle {
            id: centralItem
            objectName: "centralItem"

            signal load(url u);
            signal save(url u);
            signal createObject(string objname, real x, real y)
            signal createAddress(string objname, real x, real y)

            width:2000
            height:2000
            implicitWidth:2000
            implicitHeight:2000


            color: "#302d2e"
        }

        width:2000
        height:2000
    }

    property var draggedItem : null;

    DropArea {
        anchors.fill: parent


        keys: ["iscore/x-remote-widget", "iscore/x-remote-address"]
        onEntered: {
            centralItem.color = "grey"
        }
        onPositionChanged: {
            var item = centralItem.childAt(drag.x, drag.y);
            if(item !== null)
            {
                centralItem.color = "grey"
                if(item !== draggedItem)
                {
                    if(draggedItem != null)
                    {
                        draggedItem.dropper.stopDragging(drag)
                    }
                    draggedItem = item
                    draggedItem.dropper.startDragging(drag)
                }
                else
                {
                    draggedItem.dropper.dragging(drag)
                }

            }
            else
            {
                centralItem.color = "grey"
                if(draggedItem != null)
                {
                    draggedItem.dropper.stopDragging(drag)
                }
                draggedItem = null
            }
        }

        onExited: {
            centralItem.color = "#5e5a5c"
            draggedItem = null;
        }
        onDropped: {
            // Create a component
            if(draggedItem != null)
            {
                var res = draggedItem.dropper.dropping(drop);
                if(res)
                    drop.acceptProposedAction();
            }
            else
            {
                var drop_fmt = drop.formats[0];
                var drop_text = drop.getDataAsString(drop_fmt);
                if(drop_fmt === "iscore/x-remote-widget")
                {
                    centralItem.createObject(drop_text, drop.x, drop.y);
                    drop.acceptProposedAction();
                }
                else if(drop_fmt === "iscore/x-remote-address")
                {
                    centralItem.createAddress(drop_text, drop.x, drop.y);
                    drop.acceptProposedAction();
                }

            }
            draggedItem = null;
            centralItem.color = "#302d2e"
        }
    }
}
