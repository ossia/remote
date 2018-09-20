import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticSlider

    anchors.fill: parent

    Text
    {

        anchors{
            bottom: staticSlider.bottom
            bottomMargin: 3
            horizontalCenter: staticSlider.horizontalCenter
        }

        text: qsTr("Slider")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignBottom
    }

    Image{
        source: "qrc:/resources/slider.png"
        width:40
        height: width
    }

}
