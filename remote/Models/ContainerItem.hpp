#pragma once
#include <ossia/detail/optional.hpp>
#include <QObject>
#include <QJsonObject>

class QQuickItem;
namespace RemoteUI
{
class WidgetListData;
struct Context;

class ContainerItem : public QObject
{
  Q_OBJECT
public:
  ContainerItem(Context& ctx, RemoteUI::WidgetListData* factory, QQuickItem* it);
  ~ContainerItem();

  QJsonObject save() const noexcept;

  int32_t id() const noexcept { return m_id; }
  void setId(int32_t id) noexcept { m_id = id; }

  ossia::optional<int32_t> parentId() const noexcept { return m_parentId; }
  void setParentId(ossia::optional<int32_t> id) noexcept { m_parentId = id; }

  QQuickItem* item() const noexcept;

  qreal x() const noexcept;
  qreal y() const noexcept;
  qreal z() const noexcept;
  qreal width() const noexcept;
  qreal height() const noexcept;

Q_SIGNALS:
  void removeMe();

protected:
  Context& m_ctx;

  RemoteUI::WidgetListData* m_factory{};
  QQuickItem* m_item{};
  int32_t m_id{};
  ossia::optional<int32_t> m_parentId{};
};
}
