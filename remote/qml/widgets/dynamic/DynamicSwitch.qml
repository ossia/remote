import QtQuick 2.11
import QtQuick.Controls 2.4

DynamicSwitchForm
{
    signal valueChange(bool val)
    signal addressChanged(string addr)

//    dynamicSwitch.onPositionChanged: { valueChange(slider.position); }
    dynamicSwitch.onStateChanged: { valueChange(dynamicSwitch.state === "ON"); }

    id: widg
    property alias dropper: dropper
    AddressDrop
    {
        id: dropper
        item: widg
    }
}
