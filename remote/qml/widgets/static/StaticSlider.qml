import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticSlider

    anchors.fill: parent

    Image{
        anchors.centerIn: parent

        source: "qrc:/resources/slider.png"
        width:40
        height: width
    }

}
