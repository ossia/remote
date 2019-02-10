#pragma once
#include <Models/GUIItem.hpp>
#include <Models/WidgetAddressSetup.hpp>

namespace RemoteUI
{

template <typename Fun>
void apply_to_address(
    const ossia::value& v, const ossia::domain& d, const ossia::unit_t& u,
    Fun&& f)
{
  if (v.valid())
  {
    ossia::apply_nonnull(
        [&](const auto& v) {
          if (d)
          {
            ossia::apply_nonnull(
                [&](const auto& dom) {
                  if (u)
                  {
                    ossia::apply_nonnull(
                        [&](const auto& ds) {
                          ossia::apply_nonnull(
                              [&](const auto& u) { f(v, dom, u); }, ds);
                        },
                        u.v);
                  }
                  else
                  {
                    f(v, dom, unused_t {});
                  }
                },
                d.v);
          }
          else
          {
            if (u)
            {
              ossia::apply_nonnull(
                  [&](const auto& ds) {
                    ossia::apply_nonnull(
                        [&](const auto& u) { f(v, unused_t {}, u); }, ds);
                  },
                  u.v);
            }
            else
            {
              f(v, unused_t {}, unused_t {});
            }
          }
        },
        v);
  }
}

class Slider
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_intValueChanged(qreal r)
  {
    sendMessage(m_addr.address, (int) r);
  }
  void on_floatValueChanged(qreal r)
  {
    sendMessage(m_addr.address, (float)r);
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override
  {
    apply_to_address(
        addr.value, addr.domain.get(), addr.unit.get(),
        SetSliderAddress {*this, addr});
  }

  void setValue(const State::Message& m)
  {
  }
};

class CheckBox
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_boolValueChanged(bool b)
  {
    sendMessage(m_addr.address, b);
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override
  {
    addr.value.apply(SetCheckboxAddress {*this, addr});
  }
  void setValue(const State::Message& m)
  {
  }
};

class LineEdit
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_parsableValueChanged(QString str)
  {
    if (auto val = State::parseValue(str.toStdString()))
    {
      sendMessage(m_addr.address, *val);
    }
  }
  void on_stringValueChanged(QString str)
  {
    sendMessage(m_addr.address, str.toStdString());
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override
  {
    addr.value.apply(SetLineEditAddress {*this, addr});
  }
  void setValue(const State::Message& m)
  {
  }
};

class Label
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override
  {
    addr.value.apply(SetLabelAddress {*this, addr});
  }

  void setValue(const State::Message& m)
  {
    m.value.apply(SetLabelAddress{*this, m_addr});
  }

};

class PushButton
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_impulse()
  {
    sendMessage(m_addr.address, ossia::impulse{});
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override
  {
    m_connection = QObject::connect(
        item(), SIGNAL(clicked()), this, SLOT(on_impulse()));
  }
  void setValue(const State::Message& m)
  {
  }
};

}
