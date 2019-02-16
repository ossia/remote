// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "CentralItemModel.hpp"
#include "CreateItemFromAddress.hpp"

#include "WidgetListModel.hpp"
#include "Items.hpp"
#include <Device/Node/DeviceNode.hpp>

#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>

#include <Models/NodeModel.hpp>
#include <WebSocketClient.hpp>

namespace RemoteUI
{

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
  if (auto address = State::parseAddressAccessor(data))
  {
    auto n = Device::try_getNodeFromAddress(m_ctx.nodes.rootNode(), address->address);
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
