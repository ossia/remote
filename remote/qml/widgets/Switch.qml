import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import com.github.jcelerier.CreativeControls 1.0

Rectangle {
    id: widg

    property alias dynamicSwitch: dynamicSwitch
    property alias label: label
    property alias color: widg.color
    property alias dropper: dropper

    signal valueChange(bool val)
    signal addressChanged(string addr)

    width: 100
    height: 50
    color: "#00000000"
    Drag.dragType: Drag.Internal

    ColumnLayout {
        AddressLabel {
            id: label
            Layout.preferredHeight: 18
            Layout.preferredWidth: 40
        }
        ToggleSwitch {
            id: dynamicSwitch
            state: "OFF"
            //checked: false
            implicitWidth: 80
            implicitHeight: 40
            onStateChanged: {
                valueChange(dynamicSwitch.state === "ON")
            }
        }
    }

    AddressDrop {
        id: dropper
        item: widg
    }
}
