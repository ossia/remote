#pragma once
#include <Models/GUIItem.hpp>
#include <Models/WidgetAddressSetup.hpp>

namespace RemoteUI
{

template <typename Fun>
auto apply_to_address(
    const ossia::value& v, const ossia::domain& d, const ossia::unit_t& u,
    Fun&& f)
  -> typename Fun::return_type
{
  using return_type = typename Fun::return_type;
  if (v.valid())
  {
    return ossia::apply_nonnull(
          [&](const auto& v) -> return_type {
      if (d)
      {
        return ossia::apply_nonnull(
              [&](const auto& dom) -> return_type {
          if (u)
          {
            return ossia::apply_nonnull(
                  [&](const auto& ds) -> return_type {
              return ossia::apply_nonnull(
                    [&](const auto& u) -> return_type {
                return f(v, dom, u);
              }, ds);
            },
            u.v);
          }
          else
          {
            return f(v, dom, unused_t {});
          }
        },
        d.v);
      }
      else
      {
        if (u)
        {
          return ossia::apply_nonnull(
                [&](const auto& ds) -> return_type {
            return ossia::apply_nonnull(
                  [&](const auto& u) -> return_type {
              return f(v, unused_t {}, u); }, ds);
          },
          u.v);
        }
        else
        {
          return f(v, unused_t {}, unused_t {});
        }
      }
    },
    v);
  }

  if constexpr(!std::is_same_v<return_type, void>)
      return {};
}

// AddressSettings or FullAddressSettings
template <typename Addr, typename Fun>
auto apply_to_address(
    const Addr& addr,
    Fun&& f)
{
  return apply_to_address(
        addr.value, addr.domain.get(), addr.unit.get(),
        std::forward<Fun>(f));
}

class Slider
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_valueChanged(qreal r)
  {
    sendMessage(m_addr.address, (float)r);
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override
  {
    apply_to_address(addr, SetSliderAddress {*this, addr});
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
  void on_valueChanged(bool b)
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
  void on_valueChanged(QString str)
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
  void on_valueChanged()
  {
    sendMessage(m_addr.address, ossia::impulse{});
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override
  {
    m_connection = QObject::connect(
          item(), SIGNAL(clicked()), this, SLOT(on_valueChanged()));
  }
  void setValue(const State::Message& m)
  {
  }
};

class RGBSlider
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_rgba8Changed(const QVariantList& lst)
  {
    std::array<float, 4> val{
      lst[0].toFloat()
          , lst[1].toFloat()
          , lst[2].toFloat()
          , lst[3].toFloat()
    };
    val = ossia::rgba8{ossia::rgba{val}}.dataspace_value;
    sendMessage(m_addr.address, val);
  }
  void on_argb8Changed(const QVariantList& lst)
  {
    std::array<float, 4> val{
      lst[0].toFloat()
          , lst[1].toFloat()
          , lst[2].toFloat()
          , lst[3].toFloat()
    };
    val = ossia::argb8{ossia::rgba{val}}.dataspace_value;
    sendMessage(m_addr.address, val);
  }
  void on_rgbaChanged(const QVariantList& lst)
  {
    std::array<float, 4> val{
      lst[0].toFloat()
          , lst[1].toFloat()
          , lst[2].toFloat()
          , lst[3].toFloat()
    };
    sendMessage(m_addr.address, val);
  }
  void on_argbChanged(const QVariantList& lst)
  {
    std::array<float, 4> val{
      lst[0].toFloat()
          , lst[1].toFloat()
          , lst[2].toFloat()
          , lst[3].toFloat()
    };
    val = ossia::argb{ossia::rgba{val}}.dataspace_value;
    sendMessage(m_addr.address, val);
  }

  void on_rgbChanged(const QVariantList& lst)
  {
    std::array<float, 3> val{
      lst[0].toFloat()
          , lst[1].toFloat()
          , lst[2].toFloat()
    };
    sendMessage(m_addr.address, val);
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override
  {
    apply_to_address(addr, SetRGBAddress {*this, addr});
  }
  void setValue(const State::Message& m) override
  {
  }
};
}
