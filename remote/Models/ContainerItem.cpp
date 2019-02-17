#include <Models/ContainerItem.hpp>
#include <QJsonObject>
#include <QQmlProperty>
#include <QQuickItem>
#include <score/serialization/JSONValueVisitor.hpp>
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
  obj["width"] = width();
  obj["height"] = height();
  obj["id"] = id();
  obj["parent"] = toJsonValue(parentId());
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
qreal ContainerItem::width() const noexcept
{
  return QQmlProperty(m_item, "width").read().toReal();
}
qreal ContainerItem::height() const noexcept
{
  return QQmlProperty(m_item, "height").read().toReal();
}

}
