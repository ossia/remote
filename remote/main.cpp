// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Models/NodeModel.hpp>
#include <Models/WidgetListModel.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <RemoteApplication.hpp>

#include "3rdparty/qml-creative-controls/src/creativecontrolsplugin.hpp"
#include "3rdparty/qml-creative-controls/src/graph.hpp"
#include "3rdparty/qml-creative-controls/src/angleslider.hpp"
#include "3rdparty/qml-creative-controls/src/scope.hpp"
#include "3rdparty/qml-creative-controls/src/polygon.hpp"
#include "3rdparty/qml-creative-controls/src/painted_polygon.hpp"
#include "3rdparty/qml-creative-controls/src/cpputils.hpp"
#include "3rdparty/qml-creative-controls/src/xytarget.hpp"
#include "3rdparty/qml-creative-controls/src/toucharea.hpp"

int main(int argc, char* argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  qmlRegisterType<RemoteUI::WidgetListData>();
  qmlRegisterType<RemoteUI::NodeModel>();

  auto uri = "com.github.jcelerier.CreativeControls";
  qmlRegisterType<CreativeControls::Graph>(uri, 1, 0, "GraphImpl");
  qmlRegisterType<CreativeControls::AngleSlider>(uri, 1, 0, "AngleSliderImpl");
  qmlRegisterType<CreativeControls::Scope>(uri, 1, 0, "ScopeImpl");
  qmlRegisterType<CreativeControls::PaintedPolygon>(uri, 1, 0, "Polygon");
  qmlRegisterType<CreativeControls::XYTarget>(uri, 1, 0, "Crosshair");
  qmlRegisterType<CreativeControls::TouchArea>(uri, 1, 0, "TouchArea");

  qmlRegisterSingletonType<CreativeControls::CppUtils>(uri, 1, 0, "CppUtils",
                                     [] (QQmlEngine*, QJSEngine*) -> QObject* {
    return new CreativeControls::CppUtils;
  });

  RemoteUI::RemoteApplication app{argc, argv};

  return app.exec();
}
