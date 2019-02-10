// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "CentralItemModel.hpp"

#include "WidgetListModel.hpp"
#include "Items.hpp"
#include <Device/Node/DeviceNode.hpp>

#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>

#include <Models/NodeModel.hpp>
#include <Models/WidgetAddressSetup.hpp>
#include <WebSocketClient.hpp>
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
    QQmlProperty(obj, "parent")
        .write(QVariant::fromValue((QObject*)m_ctx.centralItem));
    return w->widgetFactory()(m_ctx, obj);
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
  template <typename D, typename U>
  GUIItem* operator()(const std::vector<ossia::value>& c, const D&, const U&) const
  {
    return nullptr; //createItem("LineEdit");
  }
};

CentralItemModel::CentralItemModel(Context& ctx, QObject* parent)
    : QObject(parent), m_ctx {ctx}
{
  connect(
      ctx.centralItem, SIGNAL(createObject(QString, qreal, qreal)), this,
      SLOT(on_itemCreated(QString, qreal, qreal)));
  connect(
      ctx.centralItem, SIGNAL(createAddress(QString, qreal, qreal)), this,
      SLOT(on_addressCreated(QString, qreal, qreal)));
}


QQuickItem* CentralItemModel::create(const QString& c)
{
  auto comp = m_ctx.widgets[c]->component();
  auto obj = (QQuickItem*)comp->create(m_ctx.engine.rootContext());
  QQmlProperty(obj, "parent")
      .write(QVariant::fromValue((QObject*)m_ctx.centralItem));
  return obj;
}

void CentralItemModel::on_itemCreated(QString widgetName, qreal x, qreal y)
{
  auto it = m_ctx.widgets.find(widgetName);
  if (it != m_ctx.widgets.end())
  {
    WidgetListData& widget = *(*it);
    QQmlComponent& comp = *widget.component();

    // Create the object
    auto obj = (QQuickItem*)comp.create(m_ctx.engine.rootContext());
    if (obj)
    {
      QQmlProperty(obj, "parent")
          .write(QVariant::fromValue((QObject*)m_ctx.centralItem));

      // Put its center where the mouse is
      QQmlProperty(obj, "x").write(x - obj->width() / 2.);
      QQmlProperty(obj, "y").write(y - obj->height() / 2.);

      addItem(widget.widgetFactory()(m_ctx, obj));
    }
    else
    {
      qDebug() << "Error: object " << widgetName << "could not be created";
    }
  }
}

void CentralItemModel::on_addressCreated(QString data, qreal x, qreal y)
{
  if (auto address = State::Address::fromString(data))
  {
    auto n = Device::try_getNodeFromAddress(m_ctx.nodes.rootNode(), *address);
    if (n)
    {
      auto as = n->target<Device::AddressSettings>();
      if (as && as->value.valid())
      {
        // We try to create a relevant component according to the type of the
        // value.
        auto item = apply_to_address(*as, AddressItemFactory {m_ctx});


        if (item)
        {
          item->setAddress(
              Device::FullAddressSettings::make<
                  Device::FullAddressSettings::as_child>(*as, *address));

          auto obj = item->item();
          // Put its center where the mouse is
          QQmlProperty(obj, "x").write(x - obj->width() / 2.);
          QQmlProperty(obj, "y").write(y - obj->height() / 2.);

          addItem(item);
        }
      }
    }
  }
}

void CentralItemModel::addItem(GUIItem* item)
{
  m_guiItems.push_back(item);

  connect(
      item, &GUIItem::removeMe, this,
      [=] {
        m_guiItems.removeOne(item);
        item->deleteLater();
      },
      Qt::QueuedConnection);
}

void CentralItemModel::removeItem(GUIItem* item)
{
  // TODO
}
}
