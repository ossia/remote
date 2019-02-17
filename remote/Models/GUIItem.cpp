// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "GUIItem.hpp"

#include <Device/Address/AddressSettings.hpp>
#include <Device/Node/DeviceNode.hpp>
#include <State/Expression.hpp>
#include <State/ValueParser.hpp>
#include <score/serialization/JSONValueVisitor.hpp>

#include <Models/NodeModel.hpp>
#include <RemoteApplication.hpp>
#include <RemoteContext.hpp>
#include <WebSocketClient.hpp>

#include <QQmlProperty>

namespace RemoteUI
{


GUIItem::GUIItem(Context& ctx, RemoteUI::WidgetListData* factory, QQuickItem* it)
    : m_ctx {ctx}, m_factory{factory}, m_item {it}
{
  connect(
      m_item, SIGNAL(addressChanged(QString)), this,
      SLOT(setAddress(QString)));

  auto obj = m_item->findChild<QObject*>("addressLabel");
  if (obj)
  {
    connect(obj, SIGNAL(removeMe()), this, SIGNAL(removeMe()));
  }
}

GUIItem::~GUIItem()
{
  QObject::disconnect(m_connection);

  m_item->deleteLater();
}

QJsonObject GUIItem::save() const noexcept
{
  QJsonObject obj;
  obj["x"] = x();
  obj["y"] = y();
  obj["settings"] = toJsonObject(addressSettings());
  obj["type"] = type();
  obj["parent"] = toJsonValue(parentId());
  return obj;
}

QQuickItem*GUIItem::item() const noexcept
{
  return m_item;
}

qreal GUIItem::x() const noexcept
{
  return QQmlProperty(m_item, "x").read().toReal();
}

qreal GUIItem::y() const noexcept
{
  return QQmlProperty(m_item, "y").read().toReal();
}

const Device::FullAddressSettings&GUIItem::addressSettings() const noexcept
{
  return m_addr;
}

QString GUIItem::address() const noexcept
{
  return m_addr.address.toString();
}

const QString & GUIItem::type() const noexcept
{
  return m_factory->name();
}

void GUIItem::setAddress(QString data)
{
  if (auto address = State::Address::fromString(data))
  {
    auto n = Device::try_getNodeFromAddress(m_ctx.nodes.rootNode(), *address);
    if (n)
    {
      auto as = n->target<Device::AddressSettings>();
      if (as && as->value.valid())
      {
        setAddress(Device::FullAddressSettings::make<
                 Device::FullAddressSettings::as_child>(*as, *address));
      }
    }
  }
}

void GUIItem::setAddress(const Device::FullAddressSettings& addr)
{
  m_addr = addr;

  setAddressImpl(m_addr);

  QQmlProperty(m_item, "label.text").write(m_addr.address.toString());
}

void GUIItem::sendMessage(const State::Address& m, const ossia::value& v)
{
  auto dev_name = m.device.toStdString();
  auto dev_it = ossia::find_if(m_ctx.device, [&](const auto& dev) {
    return dev->get_name() == dev_name;
  });
  if (dev_it != m_ctx.device.end())
  {
    auto& dev = **dev_it;

    if (auto n
        = ossia::net::find_node(dev, ("/" + m.path.join("/")).toStdString()))
    {
      if (auto p = n->get_parameter())
      {
        p->push_value(v);
      }
    }
  }
}
}
