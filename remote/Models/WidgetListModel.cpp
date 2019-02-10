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
  componentList.push_back(new RemoteUI::WidgetListData {
      WidgetKind::HSlider, "HSlider", "Horizontal Slider", "drag_hslider.png",
      QUrl("qrc:///qml/widgets/dynamic/DynamicHSlider.qml"),
      QUrl("qrc:///qml/widgets/static/StaticHSlider.qml"),
      factory<Slider>(),
      engine});

  componentList.push_back(new RemoteUI::WidgetListData {
      WidgetKind::VSlider, "VSlider", "Vertical Slider", "drag_vslider.png",
      QUrl("qrc:///qml/widgets/dynamic/DynamicVSlider.qml"),
      QUrl("qrc:///qml/widgets/static/StaticVSlider.qml"),
      factory<Slider>(),
      engine});

  componentList.push_back(new RemoteUI::WidgetListData {
      WidgetKind::CheckBox, "Switch", "CheckBox", "drag_switch.png",
      QUrl("qrc:///qml/widgets/dynamic/DynamicSwitch.qml"),
      QUrl("qrc:///qml/widgets/static/StaticSwitch.qml"),
      factory<CheckBox>(),
      engine});

  componentList.push_back(new RemoteUI::WidgetListData {
      WidgetKind::LineEdit, "LineEdit", "LineEdit", "",
      QUrl("qrc:///qml/widgets/dynamic/DynamicLineEdit.qml"),
      QUrl("qrc:///qml/widgets/static/StaticLineEdit.qml"),
      factory<LineEdit>(),
      engine});

  componentList.push_back(new RemoteUI::WidgetListData {
      WidgetKind::Label, "Label", "Label", "",
      QUrl("qrc:///qml/widgets/dynamic/DynamicLabel.qml"),
      QUrl("qrc:///qml/widgets/static/StaticLabel.qml"),
      factory<Label>(),
      engine});

  componentList.push_back(new RemoteUI::WidgetListData {
      WidgetKind::PushButton, "Button", "Button", "drag_switch.png",
      QUrl("qrc:///qml/widgets/dynamic/DynamicButton.qml"),
      QUrl("qrc:///qml/widgets/static/StaticButton.qml"),
      factory<PushButton>(),
      engine});

  // QML absolutely wants a QList<QObject*>
  for (auto l : componentList)
    objectList.push_back(l);
}
}
