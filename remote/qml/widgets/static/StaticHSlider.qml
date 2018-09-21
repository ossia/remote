import QtQuick 2.11
import QtQuick.Controls 2.4

Item
{
    id: staticHSlider

    anchors.fill: parent

    Image{
        id: img
        anchors.centerIn: parent
        source: "qrc:/resources/slider.png"
        width: 50
        fillMode: Image.PreserveAspectFit
        rotation: 90
    }

}
