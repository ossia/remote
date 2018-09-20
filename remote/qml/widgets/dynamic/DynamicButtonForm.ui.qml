import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0

Rectangle
{
    property alias button: button
    property alias label: label
    id: widg
    width: 40
    height: 50
    color: "#00000000"
    Drag.dragType: Drag.Internal

    ColumnLayout {
        AddressLabel
        {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 212
        }
        Switch
        {
            id: button
            //text: qsTr("Button")
            implicitWidth: 40
            implicitHeight: 40
        }
    }

}
