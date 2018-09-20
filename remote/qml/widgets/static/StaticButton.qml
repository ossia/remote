import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticButton

    anchors.fill: parent

    Text
    {

        anchors{
            bottom: staticButton.bottom
            bottomMargin: 3
            horizontalCenter: staticButton.horizontalCenter
        }

        text: qsTr("Button")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignBottom
    }

    Image{

        anchors{
            top: staticButton.top
            topMargin: 5
            horizontalCenter: staticButton.horizontalCenter
        }
        source: "qrc:/resources/switch.png"
        width: 50
        fillMode: Image.PreserveAspectFit
    }
}
