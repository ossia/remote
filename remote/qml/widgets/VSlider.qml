import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0

Rectangle {
    id: widg

    property alias slider: slider
    property alias label: label
    property alias dropper: dropper

    property real from: 0.
    property real to: 1.

    signal valueChange(real val)
    signal addressChanged(string addr)

    width: 154
    height: 231
    color: "#00000000"
    Drag.dragType: Drag.Internal

    ColumnLayout {
        AddressLabel {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 162
        }

        VSlider {
            id: slider
            x: 86
            y: 24
            width: 40
            height: 162
            //orientation: Qt.Horizontal
            onValueChanged: {
                valueChange(slider.value)
            }
            mapFunc: function (val) {
                return from + (to - from) * val
            }
        }
    }

    AddressDrop {
        id: dropper
        item: widg
    }
}
