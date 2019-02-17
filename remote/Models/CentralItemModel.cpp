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
#include <QJsonDocument>

#include <Models/NodeModel.hpp>
#include <WebSocketClient.hpp>

namespace RemoteUI
{

CentralItemModel::CentralItemModel(Context& ctx, QObject* parent)
    : QObject(parent), m_ctx {ctx}
{
  connect(ctx.centralItem, SIGNAL(load(QUrl)),
          this, SLOT(load(QUrl)));
  connect(ctx.centralItem, SIGNAL(save(QUrl)),
          this, SLOT(save(QUrl)));
  connect(
      ctx.centralItem, SIGNAL(createObject(QString, qreal, qreal)), this,
      SLOT(on_itemCreated(QString, qreal, qreal)));
  connect(
      ctx.centralItem, SIGNAL(createAddress(QString, qreal, qreal)), this,
        SLOT(on_addressCreated(QString, qreal, qreal)));
}

void CentralItemModel::save(QUrl path)
{
  QJsonArray arr;
  for(auto item : m_guiItems)
  {
    QJsonObject obj;
    obj["x"] = item->x();
    obj["y"] = item->y();
    obj["settings"] = toJsonObject(item->addressSettings());
    obj["type"] = item->type();
    arr.push_back(obj);
  }

  QJsonObject main;
  main["Items"] = arr;
  QByteArray txt = QJsonDocument{main}.toJson();

  QFile f(path.toLocalFile());
  if(f.open(QIODevice::WriteOnly))
    f.write(txt);
}
void CentralItemModel::load(QUrl path)
{
  QFile f(path.toLocalFile());
  if(!f.open(QIODevice::ReadOnly))
    return;

  const auto txt = QJsonDocument::fromJson(f.readAll());
  if(!txt.isObject())
    return;

  const auto items = txt.object()["Items"].toArray();
  if(items.isEmpty())
    return;

  for(auto item : m_guiItems)
    delete item;
  m_guiItems.clear();

  for(const auto& item : items)
  {
    double x = item["x"].toDouble();
    double y = item["y"].toDouble();
    auto addr = fromJsonObject<Device::FullAddressSettings>(item["settings"]);
    QString type = item["type"].toString();

    loadItem(std::move(type), std::move(addr), x, y);
  }
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
    WidgetListData& factory = *(*it);
    QQmlComponent& comp = *factory.component();

    // Create the object
    auto obj = (QQuickItem*)comp.create(m_ctx.engine.rootContext());
    if (obj)
    {
      QQmlProperty(obj, "parent")
          .write(QVariant::fromValue((QObject*)m_ctx.centralItem));

      // Put its center where the mouse is
      QQmlProperty(obj, "x").write(x - obj->width() / 2.);
      QQmlProperty(obj, "y").write(y - obj->height() / 2.);

      addItem(factory.widgetFactory()(m_ctx, &factory, obj));
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

void CentralItemModel::loadItem(QString type, Device::FullAddressSettings address, qreal x, qreal y)
{
  // We try to create a relevant component according to the type of the
  // value.
  auto item = AddressItemFactory {m_ctx}.createItem(type);
  if (item)
  {
    item->setAddress(std::move(address));

    auto obj = item->item();

    QQmlProperty(obj, "x").write(x);
    QQmlProperty(obj, "y").write(y);

    addItem(item);
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
