import QtQuick 2.11
import QtQuick.Controls 2.4

RGBSliderForm
{
    id: widg

    signal valueChange(color val)
    signal addressChanged(string addr)

    slider.onColorChanged: {
        valueChange(color);
    }

    property alias dropper: dropper
    AddressDrop
    {
        id: dropper
        item: widg
    }
}
