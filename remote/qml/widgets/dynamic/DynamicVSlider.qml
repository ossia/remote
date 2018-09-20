import QtQuick 2.11
import QtQuick.Controls 2.4

DynamicVSliderForm
{
    signal valueChange(real val)
    signal addressChanged(string addr)

   // slider.onPositionChanged: { valueChange(slider.from + slider.position * (slider.to - slider.from)); }
    slider.onValueChanged: { valueChange(slider.value); }

    id: widg
    property alias dropper: dropper
    AddressDrop
    {
        id: dropper
        item: widg
    }
}
