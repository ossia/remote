#pragma once
#include <ossia/network/generic/generic_device.hpp>

#include <QApplication>
#include <QQmlApplicationEngine>

#include <Models/CentralItemModel.hpp>
#include <Models/NodeModel.hpp>
#include <Models/WidgetListModel.hpp>
#include <ZeroconfListener.hpp>

namespace RemoteUI
{

class RemoteApplication final : public QObject
{
public:
  RemoteApplication(int& argc, char** argv);
  ~RemoteApplication();

  int exec();

private:
  void loadPlugins();
  QApplication m_app;
  QQmlApplicationEngine m_engine;

  RemoteUI::WidgetListModel m_widgets {m_engine};
  RemoteUI::NodeModel m_nodes;

  RemoteUI::Context m_context;
  RemoteUI::CentralItemModel m_centralItemModel;
  std::vector<std::unique_ptr<ossia::net::generic_device>> m_clients;
  ZeroconfListener m_zeroconf;
};
}
