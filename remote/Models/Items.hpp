#pragma once
#include <Models/GUIItem.hpp>
#include <Models/WidgetAddressSetup.hpp>

namespace RemoteUI
{


class Slider final
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
  void setAddressImpl(const Device::FullAddressSettings& addr) override;

  void setValue(const State::Message& m) override
  {
  }
};

class CheckBox final
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
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};

class LineEdit final
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
  void setValue(const State::Message& m) override
  {
  }
};

class Label final
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

  void setValue(const State::Message& m) override
  {
    m.value.apply(SetLabelAddress{*this, m_addr});
  }

};

class PushButton final
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
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};

class RGBSlider final
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_rgba8Changed(QColor lst)
  {
    std::array<float, 4> val{
            (float)lst.red()
          , (float)lst.green()
          , (float)lst.blue()
          , (float)lst.alpha()
    };

    sendMessage(m_addr.address, val);
  }
  void on_argb8Changed(QColor lst)
  {
    std::array<float, 4> val{
      (float)lst.alpha()
    , (float)lst.red()
    , (float)lst.green()
    , (float)lst.blue()
    };

    sendMessage(m_addr.address, val);
  }
  void on_rgbaChanged(QColor lst)
  {
    std::array<float, 4> val{
            (float)lst.redF()
          , (float)lst.greenF()
          , (float)lst.blueF()
          , (float)lst.alphaF()
    };
    sendMessage(m_addr.address, val);
  }
  void on_argbChanged(QColor lst)
  {
    std::array<float, 4> val{
            (float)lst.alphaF()
          , (float)lst.redF()
          , (float)lst.greenF()
          , (float)lst.blueF()
    };
    sendMessage(m_addr.address, val);
  }

  void on_rgbChanged(QColor lst)
  {
    std::array<float, 3> val{
      (float)lst.redF()
    , (float)lst.greenF()
    , (float)lst.blueF()
    };
    sendMessage(m_addr.address, val);
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};


class HSVSlider
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_rgba8Changed(QColor lst)
  {
    std::array<float, 4> val{
            (float)lst.red()
          , (float)lst.green()
          , (float)lst.blue()
          , (float)lst.alpha()
    };

    sendMessage(m_addr.address, val);
  }
  void on_argb8Changed(QColor lst)
  {
    std::array<float, 4> val{
      (float)lst.alpha()
    , (float)lst.red()
    , (float)lst.green()
    , (float)lst.blue()
    };

    sendMessage(m_addr.address, val);
  }
  void on_rgbaChanged(QColor lst)
  {
    std::array<float, 4> val{
            (float)lst.redF()
          , (float)lst.greenF()
          , (float)lst.blueF()
          , (float)lst.alphaF()
    };
    sendMessage(m_addr.address, val);
  }
  void on_argbChanged(QColor lst)
  {
    std::array<float, 4> val{
            (float)lst.alphaF()
          , (float)lst.redF()
          , (float)lst.greenF()
          , (float)lst.blueF()
    };
    sendMessage(m_addr.address, val);
  }

  void on_rgbChanged(QColor lst)
  {
    std::array<float, 3> val{
      (float)lst.redF()
    , (float)lst.greenF()
    , (float)lst.blueF()
    };
    sendMessage(m_addr.address, val);
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};


class XYPad
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_xyChanged(QPointF pt)
  {
    std::array<float, 2> val{
            (float)pt.x()
          , (float)pt.y()
    };

    sendMessage(m_addr.address, val);
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};



class Joystick
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

public Q_SLOTS:
  void on_polarChanged(QPointF pt)
  {
    std::array<float, 2> val{
            (float)pt.x()
          , (float)pt.y()
    };

    sendMessage(m_addr.address, val);
  }

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};

class Container
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};

class Leds
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};

class Matrix
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};


class Graph
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:

  struct GraphValueVisitor
  {
    Graph& g;
    void operator()(float v)
    {
      QMetaObject::invokeMethod(g.item(), "pushValue",
              Q_ARG(QVariant, v));
    }
    void operator()(int v)
    {
      QMetaObject::invokeMethod(g.item(), "pushValue",
              Q_ARG(QVariant, v));
    }

    template<typename T>
    void operator()(const T& v) { }

    void operator()() { }
  };


  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
    m.value.apply(GraphValueVisitor{*this});
  }
};

class MultiSlider
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override;
  void setValue(const State::Message& m) override
  {
  }
};


class Scope
        : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:
    void setAddressImpl(const Device::FullAddressSettings& addr) override{}
  void setValue(const State::Message& m) override
  {
  }
};


class DonutSlider
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override{}
  void setValue(const State::Message& m) override
  {
  }
};


class Keyboard
    : public GUIItem
{
  Q_OBJECT
public:
  using GUIItem::GUIItem;

private:
  void setAddressImpl(const Device::FullAddressSettings& addr) override{}
  void setValue(const State::Message& m) override
  {
  }
};

}
