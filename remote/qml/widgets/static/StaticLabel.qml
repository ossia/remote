import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticLabel
    anchors.fill: parent

    Text
    {
        anchors.centerIn: staticLabel

        text: qsTr("Label")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignBottom
        font.bold: true
    }

}
