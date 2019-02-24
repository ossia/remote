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
      "HSlider", "Horizontal Slider", "hslider-icon24.png",
      QUrl("qrc:///qml/widgets/HSlider.qml"),
      QUrl("qrc:///resources/hslider-icon.png"),
      factory<Slider>(),
      engine};

  componentList["VSlider"] = new RemoteUI::WidgetListData {
      "VSlider", "Vertical Slider", "vslider-icon24.png",
      QUrl("qrc:///qml/widgets/VSlider.qml"),
      QUrl("qrc:///resources/vslider-icon.png"),
      factory<Slider>(),
      engine};

  componentList["Switch"] = new RemoteUI::WidgetListData {
      "Switch", "CheckBox", "toggleSwitch-icon24.png",
      QUrl("qrc:///qml/widgets/Switch.qml"),
      QUrl("qrc:///resources/toggleSwitch-icon.png"),
      factory<CheckBox>(),
      engine};

  componentList["LineEdit"] = new RemoteUI::WidgetListData {
      "LineEdit", "LineEdit", "textEdit-icon24.png",
      QUrl("qrc:///qml/widgets/LineEdit.qml"),
      QUrl("qrc:///resources/textEdit-icon.png"),
      factory<LineEdit>(),
      engine};

  componentList["Label"] = new RemoteUI::WidgetListData {
      "Label", "Label", "label-icon24.png",
      QUrl("qrc:///qml/widgets/Label.qml"),
      QUrl("qrc:///resources/label-icon.png"),
      factory<Label>(),
      engine};

  componentList["Button"] = new RemoteUI::WidgetListData {
      "Button", "Button", "switch-icon24.png",
      QUrl("qrc:///qml/widgets/Button.qml"),
      QUrl("qrc:///resources/switch-icon.png"),
      factory<PushButton>(),
      engine};
  componentList["RGBSlider"] = new RemoteUI::WidgetListData {
      "RGBSlider", "RGB", "rgbSlider-icon24.png",
      QUrl("qrc:///qml/widgets/RGBSlider.qml"),
      QUrl("qrc:///resources/rgbSlider-icon.png"),
      factory<RGBSlider>(),
      engine};
  componentList["HSVSlider"] = new RemoteUI::WidgetListData {
      "HSVSlider", "HSV", "hsvSlider-icon24.png",
      QUrl("qrc:///qml/widgets/HSVSlider.qml"),
      QUrl("qrc:///resources/hsvSlider-icon.png"),
      factory<HSVSlider>(),
      engine};
  componentList["XYPad"] = new RemoteUI::WidgetListData {
      "XYPad", "X-Y", "pad-icon24.png",
      QUrl("qrc:///qml/widgets/XYPad.qml"),
      QUrl("qrc:///resources/pad-icon.png"),
      factory<XYPad>(),
      engine};

  componentList["Joystick"] = new RemoteUI::WidgetListData {
      "Joystick", "Joystick", "joystick-icon24.png",
      QUrl("qrc:///qml/widgets/Joystick.qml"),
      QUrl("qrc:///resources/joystick-icon.png"),
      factory<Joystick>(),
      engine};

  componentList["Container"] = new RemoteUI::WidgetListData {
      "Container", "Container", "container-icon24.png",
      QUrl("qrc:///qml/widgets/Container.qml"),
      QUrl("qrc:///resources/container-icon.png"),
      factory<Container>(),
      engine};


  componentList["Graph"] = new RemoteUI::WidgetListData {
      "Graph", "Graph", "graph-icon24.png",
      QUrl("qrc:///qml/widgets/Graph.qml"),
      QUrl("qrc:///resources/graph-icon.png"),
      factory<Joystick>(),
      engine};

  componentList["Leds"] = new RemoteUI::WidgetListData {
      "Leds", "Leds", "leds-icon24.png",
      QUrl("qrc:///qml/widgets/Leds.qml"),
      QUrl("qrc:///resources/leds-icon.png"),
      factory<Leds>(),
      engine};

  componentList["Matrix"] = new RemoteUI::WidgetListData {
      "Matrix", "Matrix", "matrix-icon24.png",
      QUrl("qrc:///qml/widgets/Matrix.qml"),
      QUrl("qrc:///resources/matrix-icon.png"),
      factory<Matrix>(),
      engine};

  componentList["Multislider"] = new RemoteUI::WidgetListData {
      "Multislider", "Multislider", "multiSlider-icon24.png",
      QUrl("qrc:///qml/widgets/MultiSlider.qml"),
      QUrl("qrc:///resources/multislider-icon.png"),
      factory<MultiSlider>(),
      engine};

  componentList["Graph"] = new RemoteUI::WidgetListData {
      "Graph", "Graph", "graph-icon24.png",
      QUrl("qrc:///qml/widgets/Graph.qml"),
      QUrl("qrc:///resources/graph-icon.png"),
      factory<Graph>(),
      engine};

  componentList["Scope"] = new RemoteUI::WidgetListData {
      "Scope", "Scope", "scope-icon24.png",
      QUrl("qrc:///qml/widgets/Scope.qml"),
      QUrl("qrc:///resources/scope-icon.png"),
      factory<Scope>(),
      engine};

  componentList["DonutSlider"] = new RemoteUI::WidgetListData {
      "DonutSlider", "DonutSlider", "donutSlider-icon24.png",
      QUrl("qrc:///qml/widgets/DonutSlider.qml"),
      QUrl("qrc:///resources/donutSlider-icon.png"),
      factory<Scope>(),
      engine};

  componentList["Keyboard"] = new RemoteUI::WidgetListData {
      "Keyboard", "Keyboard", "keyboard-icon24.png",
      QUrl("qrc:///qml/widgets/Keyboard.qml"),
      QUrl("qrc:///resources/keyboard-icon.png"),
      factory<Scope>(),
      engine};

  // QML absolutely wants a QList<QObject*>
  for (auto l : componentList)
    objectList.push_back(l);
}
}
