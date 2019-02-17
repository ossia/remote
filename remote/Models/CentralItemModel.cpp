// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "CentralItemModel.hpp"
#include "ContainerItem.hpp"
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
      ctx.centralItem, SIGNAL(createObject(QString, qreal, qreal, QQuickItem*)), this,
      SLOT(on_itemCreated(QString, qreal, qreal, QQuickItem*)));
  connect(
      ctx.centralItem, SIGNAL(createAddress(QString, qreal, qreal, QQuickItem*)), this,
        SLOT(on_addressCreated(QString, qreal, qreal, QQuickItem*)));
}

void CentralItemModel::save(QUrl path)
{
  QJsonArray items;
  for(auto item : m_guiItems)
  {
    items.push_back(item->save());
  }

  QJsonArray containers;
  for(auto item : m_containers)
  {
    containers.push_back(item->save());
  }


  QJsonObject page;
  page["Items"] = items;
  page["Containers"] = containers;
  QJsonArray pages;
  pages.push_back(page);

  QJsonObject root;
  root["Pages"] = pages;

  QByteArray txt = QJsonDocument{root}.toJson();

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


  for(auto item : m_guiItems)
    delete item;
  m_guiItems.clear();
  for(auto item : m_containers)
    delete item;
  m_containers.clear();

  const auto items = txt.object()["Items"].toArray();
  for(const auto& item : items)
  {
    double x = item["x"].toDouble();
    double y = item["y"].toDouble();
    auto addr = fromJsonObject<Device::FullAddressSettings>(item["settings"]);
    QString type = item["type"].toString();

    loadItem(std::move(type), std::move(addr), x, y);
  }

  const auto containers = txt.object()["Containers"].toArray();
  for(const auto& item : containers)
  {
    double x = item["x"].toDouble();
    double y = item["y"].toDouble();

    loadItem("Container", {}, x, y);
  }
}

template<typename T>
static auto setup(T& obj, qreal x, qreal y, QObject* parent)
{
  QQmlProperty(&obj, "parent").write(QVariant::fromValue(parent));
  QQmlProperty(&obj, "x").write(x);
  QQmlProperty(&obj, "y").write(y);
}

static auto createContainer(Context& m_ctx)
{
  auto w = m_ctx.widgets["Container"];
  auto comp = w->component();
  auto obj = (QQuickItem*)comp->create(m_ctx.engine.rootContext());
  return std::pair{w, obj};
}

void CentralItemModel::on_itemCreated(QString type, qreal x, qreal y, QQuickItem* parent)
{
  auto it = m_ctx.widgets.find(type);
  if (it != m_ctx.widgets.end())
  {
    WidgetListData& factory = *(*it);
    QQmlComponent& comp = *factory.component();
    if (auto obj = (QQuickItem*)comp.create(m_ctx.engine.rootContext()))
    {
      // Put its center where the mouse is
      setup(*obj, x - obj->width() / 2., y - obj->height() / 2., parent);
      if(type != "Container")
      {
        addItem(factory.widgetFactory()(m_ctx, &factory, obj));
        return;
      }
      else
      {
        addContainer(new ContainerItem{m_ctx, &factory, obj});
        return;
      }
    }
  }

  qDebug() << "Error: object " << type << "could not be created";
}

void CentralItemModel::on_addressCreated(QString data, qreal x, qreal y, QQuickItem* parent)
{
  if (auto address = State::parseAddressAccessor(data))
  {
    auto n = Device::try_getNodeFromAddress(m_ctx.nodes.rootNode(), address->address);
    if (n)
    {
      auto as = n->target<Device::AddressSettings>();
      if (as)
      {
        if(as->value.valid())
        {
          // We try to create a relevant component according to the type of the
          // value.
          auto item = createItem(*as, m_ctx);

          if (item)
          {
            item->setAddress(
                Device::FullAddressSettings::make<
                    Device::FullAddressSettings::as_child>(*as, *address));

            auto obj = item->item();
            setup(*obj, x - obj->width() / 2., y - obj->height() / 2., parent);

            addItem(item);
          }
        }
        else
        {
          auto [w, obj] = createContainer(m_ctx);
          setup(*obj, x - obj->width() / 2., y - obj->height() / 2., parent);
          addContainer(new ContainerItem{m_ctx, w, obj});
        }
      }
    }
  }
}

void CentralItemModel::loadItem(QString type, Device::FullAddressSettings address, qreal x, qreal y)
{
  // We try to create a relevant component according to the type of the
  // value.
  if(type != "Container")
  {
    auto item = AddressItemFactory {m_ctx}.createItem(type);
    if (item)
    {
      item->setAddress(std::move(address));

      auto obj = item->item();

      setup(*obj, x, y, (QObject*)m_ctx.centralItem);

      addItem(item);
    }
  }
  else
  {
    auto [w, obj] = createContainer(m_ctx);
    setup(*obj, x, y, (QObject*)m_ctx.centralItem);

    addContainer(new ContainerItem{m_ctx, w, obj});
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



void CentralItemModel::addContainer(ContainerItem* item)
{
  m_containers.push_back(item);

  connect(
      item, &ContainerItem::removeMe, this,
      [=] {
        m_containers.removeOne(item);
        item->deleteLater();
      },
      Qt::QueuedConnection);
}

void CentralItemModel::removeContainer(ContainerItem* item)
{
  // TODO
}
}
