import QtQuick 2.11
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: widg

    property alias textField: field
    property alias label: label
    property alias color: widg.color
    property alias dropper: dropper

    signal addressChanged(string addr)
    signal textChange(string txt)

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

        TextField {
            id: field
            text: qsTr("Textedit")
            Layout.fillWidth: true

            implicitWidth: 150
            implicitHeight: 40
            width: 150
            height: 40
            style: TextFieldStyle {
                textColor: "#161516"
                background: Rectangle {
                    color: "#b4c889"
                }
            }
            onEditingFinished: {
                textChange(textField.text)
            }
        }
    }

    AddressDrop {
        id: dropper
        item: widg
    }
}
