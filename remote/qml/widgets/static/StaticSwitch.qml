import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticSwitch

    anchors.fill: parent

    Text
    {
        anchors{
            bottom: staticSwitch.bottom
            bottomMargin: 3
            horizontalCenter: staticSwitch.horizontalCenter
        }

        text: qsTr("Switch")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignBottom
    }

    Image{

        anchors{
            top: staticSwitch.top
            topMargin: 5
            horizontalCenter: staticSwitch.horizontalCenter
        }
        source: "qrc:/resources/switch.png"
        width: 50
        fillMode: Image.PreserveAspectFit

    }
}
