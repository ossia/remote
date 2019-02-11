import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0

Rectangle {
    property alias slider: slider
    property alias label: label
    id: widg
    width: 162
    height: 20
    color: "#00000000"
    Drag.dragType: Drag.Internal

    ColumnLayout {
        AddressLabel {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 162
        }

        HSlider {
            id: slider
            width: 162
            height: 40
            //orientation: Qt.Horizontal
        }
    }
}