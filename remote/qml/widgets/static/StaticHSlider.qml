import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticHSlider

    anchors.fill: parent

    Text
    {

        anchors{
            bottom: staticHSlider.bottom
            bottomMargin: 3
            horizontalCenter: staticHSlider.horizontalCenter
        }

        text: qsTr("HSlider")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignBottom
    }

    Image{
        anchors{
            top: staticHSlider.top
            topMargin: 5
            horizontalCenter: staticHSlider.horizontalCenter
        }
        source: "qrc:/resources/slider.png"
        width: 50
        fillMode: Image.PreserveAspectFit
        rotation: 90
    }
}
