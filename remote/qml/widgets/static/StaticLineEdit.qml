import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticLineEdit
    anchors.fill: parent

    Text
    {
        anchors.centerIn: staticLineEdit

        text: qsTr("Text field")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignBottom
        wrapMode: Text.WordWrap
        font.bold: true
    }

}
