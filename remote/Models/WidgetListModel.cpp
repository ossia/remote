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
      QUrl("qrc:///qml/widgets/DynamicHSlider.qml"),
      QUrl("qrc:///resources/slider.png"),
      factory<Slider>(),
      engine};

  componentList["VSlider"] = new RemoteUI::WidgetListData {
      "VSlider", "Vertical Slider", "drag_vslider.png",
      QUrl("qrc:///qml/widgets/DynamicVSlider.qml"),
      QUrl("qrc:///resources/slider.png"),
      factory<Slider>(),
      engine};

  componentList["Switch"] = new RemoteUI::WidgetListData {
      "Switch", "CheckBox", "drag_switch.png",
      QUrl("qrc:///qml/widgets/DynamicSwitch.qml"),
      QUrl("qrc:///resources/switch.png"),
      factory<CheckBox>(),
      engine};

  componentList["LineEdit"] = new RemoteUI::WidgetListData {
      "LineEdit", "LineEdit", "",
      QUrl("qrc:///qml/widgets/DynamicLineEdit.qml"),
      QUrl(),
      factory<LineEdit>(),
      engine};

  componentList["Label"] = new RemoteUI::WidgetListData {
      "Label", "Label", "",
      QUrl("qrc:///qml/widgets/DynamicLabel.qml"),
      QUrl(),
      factory<Label>(),
      engine};

  componentList["Button"] = new RemoteUI::WidgetListData {
      "Button", "Button", "drag_switch.png",
      QUrl("qrc:///qml/widgets/DynamicButton.qml"),
      QUrl("qrc:///resources/switch.png"),
      factory<PushButton>(),
      engine};

  // QML absolutely wants a QList<QObject*>
  for (auto l : componentList)
    objectList.push_back(l);
}
}
