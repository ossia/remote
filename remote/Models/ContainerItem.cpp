#include <Models/ContainerItem.hpp>
#include <QJsonObject>
#include <QQmlProperty>
#include <QQuickItem>
namespace RemoteUI
{

ContainerItem::ContainerItem(
    Context& ctx,
    RemoteUI::WidgetListData* factory,
    QQuickItem* it)
    : m_ctx {ctx}, m_factory{factory}, m_item {it}
{
  connect(it, SIGNAL(removeMe()), this, SIGNAL(removeMe()));
}

ContainerItem::~ContainerItem()
{
}

QJsonObject ContainerItem::save() const noexcept
{
  QJsonObject obj;
  obj["x"] = x();
  obj["y"] = y();
  obj["z"] = z();
  return obj;
}

QQuickItem*ContainerItem::item() const noexcept
{
  return m_item;
}

qreal ContainerItem::x() const noexcept
{
  return QQmlProperty(m_item, "x").read().toReal();
}

qreal ContainerItem::y() const noexcept
{
  return QQmlProperty(m_item, "y").read().toReal();
}

qreal ContainerItem::z() const noexcept
{
  return QQmlProperty(m_item, "z").read().toReal();
}

}
