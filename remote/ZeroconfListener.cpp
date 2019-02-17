#include "ZeroconfListener.hpp"

#include <Device/Address/AddressSettings.hpp>
#include <Device/Node/DeviceNode.hpp>
#include <Device/Protocol/DeviceInterface.hpp>

#include <ossia/network/common/node_visitor.hpp>
#include <ossia/network/generic/generic_device.hpp>
#include <ossia/network/oscquery/oscquery_mirror.hpp>

#include <Models/NodeModel.hpp>
#include <asio/io_service.hpp>
#include <asio/ip/resolver_service.hpp>
#include <asio/ip/tcp.hpp>

namespace RemoteUI
{
ZeroconfListener::ZeroconfListener(Context& ctx)
    : context {ctx}, service {"_oscjson._tcp"}
{
  for (const auto& i : service.getInstances())
    instanceAdded(i);

  service.addListener(this);
  service.beginBrowsing(servus::Interface::IF_ALL);

  QObject::connect(&timer, &QTimer::timeout, [this] { service.browse(0); });
  timer.start(100);
}

ZeroconfListener::~ZeroconfListener()
{
  timer.stop();
  service.removeListener(this);
  service.endBrowsing();
}

void ZeroconfListener::instanceAdded(const std::string& instance)
{
  for (const auto& dev : context.device)
  {
    if (dev->get_name() == instance)
      return;
  }

  std::string ip = service.get(instance, "servus_ip");
  std::string port = service.get(instance, "servus_port");
  if (ip.empty())
  {
    ip = service.get(instance, "servus_host");
  }

  try
  {
    asio::io_service io_service;
    asio::ip::tcp::resolver resolver(io_service);
    asio::ip::tcp::resolver::query query(ip, port);
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    if (iter->endpoint().address().is_loopback())
    {
      ip = "localhost";
    }
  }
  catch (...)
  {
  }

  if (ip.empty() || port.empty())
  {
    return;
  }

  try
  {
    auto clt = std::make_unique<ossia::net::generic_device>(
        std::make_unique<ossia::oscquery::oscquery_mirror_protocol>(
            "ws://" + ip + ":" + port),
        instance);
    clt->get_protocol().update(clt->get_root_node());
    auto n = Device::ToDeviceExplorer(clt->get_root_node());
    n.set(
        Device::DeviceSettings {{}, QString::fromStdString(clt->get_name())});
    context.nodes.add_device(std::move(n));
    context.device.push_back(std::move(clt));
  }
  catch (...)
  {
    std::cerr << "Could not connect: "
              << "ws://" + ip + ":" + port << "\n";
  }
}

void ZeroconfListener::instanceRemoved(const std::string& instance)
{
  context.nodes.remove_device(QString::fromStdString(instance));
  auto it = ossia::find_if(context.device, [&](const auto& d) {
    return d->get_name() == instance;
  });

  if (it != context.device.end())
  {
    context.device.erase(it);
  }
}
}
