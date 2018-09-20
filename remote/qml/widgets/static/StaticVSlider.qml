import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticVSlider

    anchors.fill: parent

    Text
    {

        anchors{
            bottom: staticVSlider.bottom
            bottomMargin: 3
            horizontalCenter: staticVSlider.horizontalCenter
        }

        text: qsTr("VSlider")
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignBottom

    }

    Image{

        anchors{
            top: staticVSlider.top
            topMargin: 5
            horizontalCenter: staticVSlider.horizontalCenter
        }
        source: "qrc:/resources/slider.png"
        width: 50
        fillMode: Image.PreserveAspectFit
    }
}
