// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <QCursor>
#include <QApplication>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QTimer>

#include <Models/NodeModel.hpp>
#include <Models/WidgetListModel.hpp>
#include <RemoteApplication.hpp>
#include <core/application/ApplicationInterface.hpp>
#include <core/application/ApplicationSettings.hpp>
#include <core/presenter/DocumentManager.hpp>
#include <score/plugins/settingsdelegate/SettingsDelegateModel.hpp>
#include <src/angleslider.hpp>
#include <src/cpputils.hpp>
#include <src/creativecontrolsplugin.hpp>
#include <src/graph.hpp>
#include <src/painted_polygon.hpp>
#include <src/polygon.hpp>
#include <src/scope.hpp>
#include <src/toucharea.hpp>
#include <src/xytarget.hpp>
#include <wobjectimpl.h>

class Application : public score::ApplicationInterface
{
public:
  Application()
    : m_comps{m_data}
    , m_ctx{m_appSettings, m_comps, m_docs, m_settings}
  {
    m_instance = this;
  }

  const score::ApplicationContext&context() const override
  {
    return m_ctx;
  }

  const score::ApplicationComponents&components() const override
  {
    return m_comps;
  }

private:

  score::ApplicationComponentsData m_data;
  score::ApplicationComponents m_comps;
  score::ApplicationSettings m_appSettings;
  score::DocumentList m_docs;
  std::vector<std::unique_ptr<score::SettingsDelegateModel>> m_settings;
  score::ApplicationContext m_ctx;
};

struct CursorSetter : QObject
{
  W_OBJECT(CursorSetter)
public:
  void hideCursor()
  {
    qApp->setOverrideCursor(Qt::BlankCursor);
  }
  W_SLOT(hideCursor)

  void displayCursor()
  {
    qApp->restoreOverrideCursor();
  }
  W_SLOT(displayCursor)
};
W_OBJECT_IMPL(CursorSetter)


int main(int argc, char* argv[])
{
  qputenv("QML_DISABLE_DISTANCEFIELD", "1");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setOrganizationName("ossia");
  QCoreApplication::setOrganizationDomain("ossia.io");
  QCoreApplication::setApplicationName("remote");
  QCoreApplication::setApplicationVersion("1.0");
  qmlRegisterType<RemoteUI::WidgetListData>();
  qmlRegisterType<RemoteUI::NodeModel>();

  auto uri = "com.github.jcelerier.CreativeControls";
  qmlRegisterType<CreativeControls::Graph>(uri, 1, 0, "GraphImpl");
  qmlRegisterType<CreativeControls::AngleSlider>(uri, 1, 0, "AngleSliderImpl");
  qmlRegisterType<CreativeControls::Scope>(uri, 1, 0, "ScopeImpl");
  qmlRegisterType<CreativeControls::PaintedPolygon>(uri, 1, 0, "Polygon");
  qmlRegisterType<CreativeControls::XYTarget>(uri, 1, 0, "Crosshair");
  qmlRegisterType<CreativeControls::TouchArea>(uri, 1, 0, "TouchArea");

  qmlRegisterSingletonType<CreativeControls::CppUtils>(
      uri, 1, 0, "CppUtils", [](QQmlEngine*, QJSEngine*) -> QObject* {
        return new CreativeControls::CppUtils;
      });
  qmlRegisterSingletonType<CursorSetter>(
      "CursorSetter", 1, 0, "CursorSetter",
      [](QQmlEngine*, QJSEngine*) -> QObject* { return new CursorSetter; });
  try
  {
    Application context;
    RemoteUI::RemoteApplication app {argc, argv};
    return app.exec();
  }
  catch (std::runtime_error& e)
  {
    QApplication app(argc, argv);

    QMetaObject::invokeMethod(
        &app,
        [&] {
          QMessageBox::critical(nullptr, "Error", e.what());
          app.exit(1);
        },
        Qt::QueuedConnection);

    return app.exec();
  }
}
