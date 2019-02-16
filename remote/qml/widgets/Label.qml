import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle {
    id: widg

    property alias text: text
    property alias label: label
    property alias dropper: dropper

    signal addressChanged(string addr)

    width: 212
    height: 86
    color: "#00000000"
    Drag.dragType: Drag.Internal

    ColumnLayout {
        AddressLabel {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 212
        }

        Text {
            id: text
            font.bold: true
            font.pointSize: 12
        }
    }

    AddressDrop {
        id: dropper
        item: widg
    }
}
