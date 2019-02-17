#pragma once

#include <Models/WidgetAddressSetup.hpp>
#include <Models/WidgetListModel.hpp>
#include <RemoteContext.hpp>
namespace RemoteUI
{

// Type to widget
struct AddressItemFactory
{
  using return_type = GUIItem*;
  Context& m_ctx;


  GUIItem* createItem(const QString& name) const
  {
    auto w = m_ctx.widgets[name];
    auto comp = w->component();
    auto obj = (QQuickItem*)comp->create(m_ctx.engine.rootContext());
    return w->widgetFactory()(m_ctx, w, obj);
  }

  template <typename T, typename D, typename U>
  GUIItem* operator()(const T&, const D&, const U&) const
  {
    std::cerr << "TODO: " << typeid(T).name() << " ... " << typeid(D).name() << " ... " << typeid(U).name() << std::endl;
    return nullptr;
  }

  template <typename D, typename U>
  GUIItem* operator()(float, const D&, const U&) const
  {
    return createItem("HSlider");
  }

  template <typename D, typename U>
  GUIItem* operator()(int, const D&, const U&) const
  {
    return createItem("HSlider");
  }

  template <typename D, typename U>
  GUIItem* operator()(ossia::impulse, const D&, const U&) const
  {
    return createItem("Button");
  }

  template <typename D, typename U>
  GUIItem* operator()(bool, const D&, const U&) const
  {
    return createItem("Switch");
  }
  template <typename D, typename U>
  GUIItem* operator()(const std::string& v, const D&, const U&) const
  {
    return createItem("LineEdit");
  }
  template <typename D, typename U>
  GUIItem* operator()(char , const D&, const U&) const
  {
    return createItem("LineEdit");
  }
  template <std::size_t N, typename D, typename U>
  GUIItem* operator()(std::array<float, N> arr , const D&, const U&) const
  {
    return nullptr; //createItem("LineEdit");
  }

  template <typename D>
  GUIItem* operator()(std::array<float, 4> arr , const D&, const ossia::rgba_u&) const
  {
    return createItem("RGBSlider");
  }
  template <typename D>
  GUIItem* operator()(std::array<float, 4> arr , const D&, const ossia::rgba8_u&) const
  {
    return createItem("RGBSlider");
  }
  template <typename D>
  GUIItem* operator()(std::array<float, 4> arr , const D&, const ossia::argb_u&) const
  {
    return createItem("RGBSlider");
  }
  template <typename D>
  GUIItem* operator()(std::array<float, 4> arr , const D&, const ossia::argb8_u&) const
  {
    return createItem("RGBSlider");
  }
  template <typename D>
  GUIItem* operator()(std::array<float, 3> arr , const D&, const ossia::rgb_u&) const
  {
    return createItem("RGBSlider");
  }

  template <typename D>
  GUIItem* operator()(const std::vector<ossia::value>& arr , const D&, const ossia::rgba_u&) const
  {
    return createItem("RGBSlider");
  }
  template <typename D>
  GUIItem* operator()(const std::vector<ossia::value>& arr , const D&, const ossia::rgba8_u&) const
  {
    return createItem("RGBSlider");
  }
  template <typename D>
  GUIItem* operator()(const std::vector<ossia::value>& arr , const D&, const ossia::argb_u&) const
  {
    return createItem("RGBSlider");
  }
  template <typename D>
  GUIItem* operator()(const std::vector<ossia::value>& arr , const D&, const ossia::argb8_u&) const
  {
    return createItem("RGBSlider");
  }
  template <typename D>
  GUIItem* operator()(const std::vector<ossia::value>&, const D&, const ossia::rgb_u&) const
  {
    return createItem("RGBSlider");
  }

  template <typename D>
  GUIItem* operator()(std::array<float, 3> arr , const D&, const ossia::hsv_u&) const
  {
    return createItem("HSVSlider");
  }

  template <typename D>
  GUIItem* operator()(const std::vector<ossia::value>&, const D&, const ossia::hsv_u&) const
  {
    return createItem("HSVSlider");
  }


  template <typename D, typename U>
  GUIItem* operator()(std::array<float, 2> arr , const D&, const U&) const
  {
    return createItem("XYPad");
  }

  template <typename D>
  GUIItem* operator()(std::array<float, 2> arr , const D&, const ossia::cartesian_2d_u&) const
  {
    return createItem("XYPad");
  }
  template <typename D>
  GUIItem* operator()(std::array<float, 2> arr , const D&, const ossia::polar_u&) const
  {
    return createItem("XYPad");
  }

  template <typename D>
  GUIItem* operator()(const std::vector<ossia::value>& arr , const D&, const ossia::cartesian_2d_u&) const
  {
    return createItem("XYPad");
  }
  template <typename D>
  GUIItem* operator()(const std::vector<ossia::value>& arr , const D&, const ossia::polar_u&) const
  {
    return createItem("Joystick");
  }

  template <typename D, typename U>
  GUIItem* operator()(const std::vector<ossia::value>& c, const D&, const U&) const
  {
    switch(c.size())
    {
      case 2:
        if(c[0].target<float>() && c[1].target<float>())
          return createItem("XYPad");
    }
    return nullptr; //createItem("LineEdit");
  }
  GUIItem* operator()(const unused_t&, const unused_t&, const unused_t&) const
  {
    return createItem("Container");
  }

};

GUIItem* createItem(const Device::AddressSettings& settings, Context& ctx);
}
