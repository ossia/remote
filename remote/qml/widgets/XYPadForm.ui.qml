import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0

Rectangle {
    property alias slider: slider
    property alias label: label
    id: widg
    width: 162
    height: 150
    color: "#00000000"
    Drag.dragType: Drag.Internal

    ColumnLayout {
        AddressLabel {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 162
        }

        RGBSlider {
            id: slider
            width: 162
            height: 126
            //orientation: Qt.Horizontal
        }
    }
}
