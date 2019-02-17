#include "CreateItemFromAddress.hpp"
#include "Items.hpp"

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

  return f(unused_t{},unused_t{},unused_t{});
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

void Slider::setAddressImpl(const Device::FullAddressSettings& addr)
{
  apply_to_address(addr, SetSliderAddress {*this, addr});
}

void Container::setAddressImpl(const Device::FullAddressSettings& addr)
{
}

void Joystick::setAddressImpl(const Device::FullAddressSettings& addr)
{
  apply_to_address(addr, SetJoystickAddress {*this, addr});
}

void XYPad::setAddressImpl(const Device::FullAddressSettings& addr)
{
  apply_to_address(addr, SetXYAddress {*this, addr});
}

void HSVSlider::setAddressImpl(const Device::FullAddressSettings& addr)
{
  apply_to_address(addr, SetHSVAddress {*this, addr});
}

void RGBSlider::setAddressImpl(const Device::FullAddressSettings& addr)
{
  apply_to_address(addr, SetRGBAddress {*this, addr});
}

void PushButton::setAddressImpl(const Device::FullAddressSettings& addr)
{
  m_connection = QObject::connect(
        item(), SIGNAL(clicked()), this, SLOT(on_valueChanged()));
}

void CheckBox::setAddressImpl(const Device::FullAddressSettings& addr)
{
  addr.value.apply(SetCheckboxAddress {*this, addr});
}

GUIItem* createItem(const Device::AddressSettings& as, Context& ctx)
{
  return apply_to_address(as, AddressItemFactory {ctx});
}

}
