#pragma once
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

  QQuickItem* item() const noexcept;

  qreal x() const noexcept;
  qreal y() const noexcept;
  qreal z() const noexcept;

Q_SIGNALS:
  void removeMe();

protected:
  Context& m_ctx;

  RemoteUI::WidgetListData* m_factory{};
  QQuickItem* m_item{};
};
}
