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

class GUIItem : public QObject
{
  Q_OBJECT
  friend struct SetSliderAddress;
  friend struct SetCheckboxAddress;
  friend struct SetLineEditAddress;
  friend struct SetRGBAddress;

public:
  GUIItem(Context& ctx, QQuickItem* it);
  ~GUIItem();

  QQuickItem* item() const
  {
    return m_item;
  }

  void enableListening(const Device::FullAddressSettings&);
  void disableListening(const Device::FullAddressSettings&);
  qreal x() const;
  qreal y() const;

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

  QQuickItem* m_item;
  Device::FullAddressSettings m_addr;
  QMetaObject::Connection m_connection;
};
}
