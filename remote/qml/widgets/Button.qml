import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0 as CC

Rectangle {
    id: widg

    property alias button: button
    property alias label: label
    property alias dropper: dropper

    signal addressChanged(string addr)
    signal clicked

    width: 40
    height: 50
    color: "#00000000"
    Drag.dragType: Drag.Internal

    ColumnLayout {
        AddressLabel {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 212
        }

        CC.Switch {
            id: button
            implicitWidth: 40
            implicitHeight: 40
        }
    }

    AddressDrop {
        id: dropper
        item: widg
    }

    Component.onCompleted: button.pressed.connect(clicked)
}
