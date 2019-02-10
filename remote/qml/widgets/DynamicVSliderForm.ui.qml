import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0

Rectangle
{
    id: widg
    property alias slider: slider
    property alias label: label
    property alias color: widg.color
    width: 154
    height: 231
    color: "#00000000"

    Drag.dragType: Drag.Internal

    ColumnLayout {
        width: 154
        height: 231
        AddressLabel
        {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 212
        }

        VSlider
        {
            id: slider
            x: 86
            y: 24
            width: 40
            height: 162
            //Layout.fillWidth: true
           // orientation: Qt.Vertical
        }
    }
}
