import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticSwitch

    anchors.fill: parent

    Image{

        anchors.centerIn: parent

        source: "qrc:/resources/switch.png"
        width: 50
        fillMode: Image.PreserveAspectFit

    }
}
