#pragma once
#include <Device/Address/AddressSettings.hpp>
#include <State/ValueConversion.hpp>

#include <ossia/network/domain/domain.hpp>

#include <QQmlProperty>
#include <QQuickItem>

#include <Models/GUIItem.hpp>

namespace RemoteUI
{

struct SetSliderAddress
{
  using return_type = void;
  GUIItem& item;
  const Device::FullAddressSettings& address;

  template <typename D, typename U>
  void operator()(State::impulse c, const D&, const U&)
  {
  }

  template <typename D, typename U>
  void operator()(bool c, const D&, const U&)
  {
    QQmlProperty(item.item(), "from").write(0.);
    QQmlProperty(item.item(), "to").write(1.);
    QQmlProperty(item.item(), "slider.stepSize").write(1);
    QQmlProperty(item.item(), "slider.value").write((qreal)c);
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item, SLOT(on_valueChanged(qreal)));
  }

  template <typename D, typename U>
  void operator()(int i, const D&, const U&)
  {
    QQmlProperty(item.item(), "from").write((qreal)0);
    QQmlProperty(item.item(), "to").write((qreal)127);
    QQmlProperty(item.item(), "slider.stepSize").write(1);
    QQmlProperty(item.item(), "slider.value").write((qreal)i);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item,
        SLOT(on_valueChanged(qreal)));
  }

  template <typename U>
  void operator()(int i, const ossia::domain_base<int>& d, const U& u)
  {
    if (d.min)
      QQmlProperty(item.item(), "from").write((qreal)*d.min);

    if (d.max)
      QQmlProperty(item.item(), "to").write((qreal)*d.max);

    QQmlProperty(item.item(), "slider.stepSize").write(1);
    QQmlProperty(item.item(), "slider.value").write((qreal)i);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item,
        SLOT(on_valueChanged(qreal)));
  }

  template <typename D, typename U>
  void operator()(float f, const D&, const U&)
  {
    QQmlProperty(item.item(), "from").write(0.);
    QQmlProperty(item.item(), "to").write(1.);

    QQmlProperty(item.item(), "slider.value").write((qreal)f);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item,
        SLOT(on_valueChanged(qreal)));
  }

  template <typename U>
  void operator()(float f, const ossia::domain_base<float>& d, const U& u)
  {
    if (d.min)
      QQmlProperty(item.item(), "from").write((qreal)*d.min);

    if (d.max)
      QQmlProperty(item.item(), "to").write((qreal)*d.max);

    QQmlProperty(item.item(), "slider.value").write((qreal)f);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item,
        SLOT(on_valueChanged(qreal)));
  }

  template <typename D, typename U>
  void operator()(char c, const D&, const U&)
  {
    /*
    QQmlProperty(item.item(), "min_chars").write(1);
    QQmlProperty(item.item(), "max_chars").write(1);
    QQmlProperty(item.item(), "value").write(c);
    */
  }

  template <typename D, typename U>
  void operator()(const std::string& s, const D&, const U&)
  {
    /*
    QQmlProperty(item.item(), "value").write(QString::fromStdString(s));
    */
  }

  template <std::size_t N, typename D, typename U>
  void operator()(std::array<float, N> c, const D&, const U&)
  {
    QQmlProperty(item.item(), "from").write(0.);
    QQmlProperty(item.item(), "to").write(1.);

    QQmlProperty(item.item(), "slider.value").write(0.);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item,
        SLOT(on_valueChanged(qreal)));
  }

  template <typename D>
  void operator()(std::array<float, 4> c, const D&, const ossia::rgba8_u&)
  {
    QQmlProperty(item.item(), "from").write(0);
    QQmlProperty(item.item(), "to").write(255);

    QQmlProperty(item.item(), "slider.value").write(0); //TODO

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item,
        SLOT(on_valueChanged(qreal)));
  }

  template <typename D>
  void operator()(std::array<float, 4> c, const D&, const ossia::argb8_u&)
  {
    QQmlProperty(item.item(), "from").write(0);
    QQmlProperty(item.item(), "to").write(255);

    QQmlProperty(item.item(), "slider.value").write(0); //TODO

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item,
        SLOT(on_valueChanged(qreal)));
  }

  template <typename D, typename U>
  void operator()(const std::vector<ossia::value>& c, const D&, const U&)
  {
    QQmlProperty(item.item(), "from").write(0.);
    QQmlProperty(item.item(), "to").write(1.);

    QQmlProperty(item.item(), "slider.value").write(0.);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(qreal)), &item,
        SLOT(on_valueChanged(qreal)));
  }
};

struct SetCheckboxAddress
{
  using return_type = void;
  GUIItem& item;
  const Device::FullAddressSettings& address;

  void operator()()
  {
  }
  void operator()(State::impulse)
  {
    // Do nothing
    /*
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(toggled()), &item, SLOT(on_impulse()));
        */
  }
  void operator()(bool)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(bool)), &item,
        SLOT(on_valueChanged(bool)));
  }

  void operator()(int i)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(bool)), &item,
        SLOT(on_valueChanged(bool)));
  }

  void operator()(float f)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(bool)), &item,
        SLOT(on_valueChanged(bool)));
  }

  template<typename Arg>
  void operator()(const Arg& c)
  {
  }
};

struct SetLineEditAddress
{
  using return_type = void;
  GUIItem& item;
  const Device::FullAddressSettings& address;

  void operator()()
  {
  }
  void operator()(State::impulse)
  {
    // Do nothing
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(toggled()), &item, SLOT(on_impulse()));
  }
  void operator()(bool b)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(textChange(QString)), &item,
        SLOT(on_parsableValueChanged(QString)));
  }

  void operator()(int i)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(textChange(QString)), &item,
        SLOT(on_parsableValueChanged(QString)));
  }

  void operator()(float f)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(textChange(QString)), &item,
        SLOT(on_parsableValueChanged(QString)));
  }

  void operator()(char c)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(textChange(QString)), &item,
        SLOT(on_parsableValueChanged(QString)));
  }
  void operator()(const std::string& s)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(textChange(QString)), &item,
        SLOT(on_valueChanged(QString)));
  }

  template <std::size_t N>
  void operator()(std::array<float, N> c)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(textChange(QString)), &item,
        SLOT(on_parsableValueChanged(QString)));
  }

  void operator()(const std::vector<ossia::value>& c)
  {
    item.m_connection = QObject::connect(
        item.item(), SIGNAL(textChange(QString)), &item,
        SLOT(on_parsableValueChanged(QString)));
  }
};

struct SetLabelAddress
{
  using return_type = void;
  GUIItem& item;
  const Device::FullAddressSettings& address;

  void operator()()
  {
  }
  void operator()(State::impulse)
  {
    // Do nothing
    QQmlProperty(item.item(), "text.text").write("Impulse");
  }
  void operator()(bool b)
  {
    QQmlProperty(item.item(), "text.text")
        .write(QString("Bool: ") + (b ? "true" : "false"));
  }

  void operator()(int i)
  {
    QQmlProperty(item.item(), "text.text")
        .write(QString("Int: ") + QString::number(i));
  }

  void operator()(float f)
  {
    QQmlProperty(item.item(), "text.text")
        .write(QString("Float: ") + QString::number(f));
  }

  void operator()(char c)
  {
    QQmlProperty(item.item(), "text.text").write(QString("Char: ") + QChar(c));
  }
  void operator()(const std::string& s)
  {
    QQmlProperty(item.item(), "text.text")
        .write("String: " + QString::fromStdString(s));
  }

  template <std::size_t N>
  void operator()(std::array<float, N> c)
  {
    QQmlProperty(item.item(), "text.text")
        .write(
            "Array" + QString::fromStdString(ossia::convert<std::string>(c)));
  }

  void operator()(const std::vector<ossia::value>& c)
  {
    QQmlProperty(item.item(), "text.text")
        .write("List" + State::convert::value<QString>(c));
  }
};

struct SetRGBAddress
{
  using return_type = void;
  GUIItem& item;
  const Device::FullAddressSettings& address;

  void operator()()
  {
  }

  template <typename D>
  void operator()(std::array<float, 4> c, const D&, const ossia::rgba8_u&)
  {
    c = ossia::rgba{ossia::rgba8{c}}.dataspace_value;
    QQmlProperty(item.item(), "slider.enableAplha").write(true);
    // QQmlProperty(item.item(), "slider.value").write(QColor() << c[0] << c[1] << c[2] << c[3]);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(QColor)), &item,
        SLOT(on_rgba8Changed(QColor)));
  }

  template <typename D>
  void operator()(std::array<float, 4> c, const D&, const ossia::argb8_u&)
  {
    c = ossia::rgba{ossia::argb8{c}}.dataspace_value;
    QQmlProperty(item.item(), "slider.enableAplha").write(true);
    // QQmlProperty(item.item(), "slider.value").write(QColor() << c[0] << c[1] << c[2] << c[3]);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(QColor)), &item,
        SLOT(on_argb8Changed(QColor)));
  }


  template <typename D>
  void operator()(std::array<float, 4> c, const D&, const ossia::rgba_u&)
  {
    QQmlProperty(item.item(), "slider.enableAplha").write(true);
    // QQmlProperty(item.item(), "slider.value").write(QColor() << c[0] << c[1] << c[2] << c[3]);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(QColor)), &item,
        SLOT(on_rgbaChanged(QColor)));
  }

  template <typename D>
  void operator()(std::array<float, 4> c, const D&, const ossia::argb_u&)
  {
    c = ossia::rgba{ossia::argb{c}}.dataspace_value;
    QQmlProperty(item.item(), "slider.enableAplha").write(true);
    // QQmlProperty(item.item(), "slider.value").write(QColor() << c[0] << c[1] << c[2] << c[3]);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(QColor)), &item,
        SLOT(on_argbChanged(QColor)));
  }

  template <typename D>
  void operator()(std::array<float, 3> c, const D&, const ossia::rgb_u&)
  {
    QQmlProperty(item.item(), "slider.enableAplha").write(true);
    // QQmlProperty(item.item(), "slider.value").write(QColor() << c[0] << c[1] << c[2]);

    item.m_connection = QObject::connect(
        item.item(), SIGNAL(valueChange(QColor)), &item,
        SLOT(on_rgbChanged(QColor)));
  }

  template<typename... Arg>
  void operator()(const Arg&... c)
  {
  }
};
}
