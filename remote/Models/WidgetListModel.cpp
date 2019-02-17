// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "WidgetListModel.hpp"
#include <Models/Items.hpp>

namespace RemoteUI
{
WidgetListData::~WidgetListData()
{
}

template<typename T>
auto factory()
{
  return [] (auto&&... args) {
    return new T{std::forward<decltype(args)>(args)...};
  };
}

WidgetListModel::WidgetListModel(QQmlApplicationEngine& engine)
{
  componentList["HSlider"] = new RemoteUI::WidgetListData {
      "HSlider", "Horizontal Slider", "drag_hslider.png",
      QUrl("qrc:///qml/widgets/HSlider.qml"),
      QUrl("qrc:///resources/slider.png"),
      factory<Slider>(),
      engine};

  componentList["VSlider"] = new RemoteUI::WidgetListData {
      "VSlider", "Vertical Slider", "drag_vslider.png",
      QUrl("qrc:///qml/widgets/VSlider.qml"),
      QUrl("qrc:///resources/slider.png"),
      factory<Slider>(),
      engine};

  componentList["Switch"] = new RemoteUI::WidgetListData {
      "Switch", "CheckBox", "drag_switch.png",
      QUrl("qrc:///qml/widgets/Switch.qml"),
      QUrl("qrc:///resources/switch.png"),
      factory<CheckBox>(),
      engine};

  componentList["LineEdit"] = new RemoteUI::WidgetListData {
      "LineEdit", "LineEdit", "",
      QUrl("qrc:///qml/widgets/LineEdit.qml"),
      QUrl(),
      factory<LineEdit>(),
      engine};

  componentList["Label"] = new RemoteUI::WidgetListData {
      "Label", "Label", "",
      QUrl("qrc:///qml/widgets/Label.qml"),
      QUrl(),
      factory<Label>(),
      engine};

  componentList["Button"] = new RemoteUI::WidgetListData {
      "Button", "Button", "drag_switch.png",
      QUrl("qrc:///qml/widgets/Button.qml"),
      QUrl("qrc:///resources/switch.png"),
      factory<PushButton>(),
      engine};
  componentList["RGBSlider"] = new RemoteUI::WidgetListData {
      "RGBSlider", "RGB", "",
      QUrl("qrc:///qml/widgets/RGBSlider.qml"),
      QUrl(),
      factory<RGBSlider>(),
      engine};
  componentList["HSVSlider"] = new RemoteUI::WidgetListData {
      "HSVSlider", "HSV", "",
      QUrl("qrc:///qml/widgets/HSVSlider.qml"),
      QUrl(),
      factory<HSVSlider>(),
      engine};
  componentList["XYPad"] = new RemoteUI::WidgetListData {
      "XYPad", "X-Y", "",
      QUrl("qrc:///qml/widgets/XYPad.qml"),
      QUrl(),
      factory<XYPad>(),
      engine};
  componentList["Joystick"] = new RemoteUI::WidgetListData {
      "Joystick", "Joystick", "",
      QUrl("qrc:///qml/widgets/Joystick.qml"),
      QUrl(),
      factory<Joystick>(),
      engine};
  componentList["Container"] = new RemoteUI::WidgetListData {
      "Container", "Container", "",
      QUrl("qrc:///qml/widgets/Container.qml"),
      QUrl(),
      factory<Container>(),
      engine};

  // QML absolutely wants a QList<QObject*>
  for (auto l : componentList)
    objectList.push_back(l);
}
}
