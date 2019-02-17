#pragma once
#include <Device/Address/AddressSettings.hpp>

#include <QObject>

namespace State
{
struct Message;
}
class QQuickItem;
namespace Device
{
struct FullAddressSettings;
}
namespace RemoteUI
{
struct Context;
class WidgetListData;
class GUIItem : public QObject
{
  Q_OBJECT
  friend struct SetSliderAddress;
  friend struct SetCheckboxAddress;
  friend struct SetLineEditAddress;
  friend struct SetRGBAddress;
  friend struct SetHSVAddress;
  friend struct SetXYAddress;
  friend struct SetJoystickAddress;

public:
  GUIItem(Context& ctx, RemoteUI::WidgetListData* factory, QQuickItem* it);
  ~GUIItem();

  void enableListening(const Device::FullAddressSettings&);
  void disableListening(const Device::FullAddressSettings&);

  QQuickItem* item() const noexcept;

  qreal x() const noexcept;
  qreal y() const noexcept;
  QString address() const noexcept;
  const QString& type() const noexcept;

  const Device::FullAddressSettings& addressSettings() const noexcept;

Q_SIGNALS:
  void removeMe();

public Q_SLOTS:
  void setAddress(QString);
  void setAddress(const Device::FullAddressSettings&);


protected:
  virtual void setAddressImpl(const Device::FullAddressSettings&) = 0;
  virtual void setValue(const State::Message& m) = 0;

  void sendMessage(const State::Address& m, const ossia::value& v);
  Context& m_ctx;

  RemoteUI::WidgetListData* m_factory{};
  QQuickItem* m_item{};
  QString m_addrText;
  Device::FullAddressSettings m_addr;
  QMetaObject::Connection m_connection;
};
}
