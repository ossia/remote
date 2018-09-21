// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <Models/NodeModel.hpp>
#include <Models/WidgetListModel.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <RemoteApplication.hpp>
#include <QCursor>

#include <src/creativecontrolsplugin.hpp>
#include <src/graph.hpp>
#include <src/angleslider.hpp>
#include <src/scope.hpp>
#include <src/polygon.hpp>
#include <src/painted_polygon.hpp>
#include <src/cpputils.hpp>
#include <src/xytarget.hpp>
#include <src/toucharea.hpp>
#include <wobjectimpl.h>
struct CursorSetter
    : QObject
{
  W_OBJECT(CursorSetter)
public:
    void hideCursor() {
        qApp->setOverrideCursor(Qt::BlankCursor);
    } W_SLOT(hideCursor)

    void displayCursor() {
        qApp->restoreOverrideCursor();
    } W_SLOT(displayCursor)
};
W_OBJECT_IMPL(CursorSetter)
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
  qmlRegisterSingletonType<CursorSetter>("CursorSetter", 1, 0, "CursorSetter",
                                     [] (QQmlEngine*, QJSEngine*) -> QObject* {
    return new CursorSetter;
  });
  RemoteUI::RemoteApplication app{argc, argv};

  return app.exec();
}
