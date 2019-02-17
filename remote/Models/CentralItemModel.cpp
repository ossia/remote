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
#include <score/tools/IdentifierGeneration.hpp>

namespace RemoteUI
{
template <typename Container>
auto makeId(const Container& v) -> int32_t
{
  using namespace std;
  auto ids = make_dynarray(int32_t, std::size_t(v.size()));

  transform(v.begin(), v.end(), ids.begin(), [](const auto& elt) {
    return elt->id();
  });

  return score::id_generator::getNextId(ids);
}

static auto createContainer(Context& m_ctx)
{
  auto w = m_ctx.widgets["Container"];
  auto comp = w->component();
  auto obj = (QQuickItem*)comp->create(m_ctx.engine.rootContext());
  return std::pair{w, obj};
}

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

  auto pages = txt.object()["Pages"].toArray();
  if(pages.empty())
    return;
  auto page = pages[0].toObject();

  for(auto item : m_guiItems)
    delete item;
  m_guiItems.clear();
  for(auto item : m_containers)
    delete item;
  m_containers.clear();



  std::unordered_map<int32_t, std::tuple<ContainerItem*, QRectF>> container_objects;
  const auto containers = page["Containers"].toArray();
  for(const auto& item : containers)
  {
    double x = item["x"].toDouble();
    double y = item["y"].toDouble();
    double z = item["z"].toDouble();
    double width = item["width"].toDouble();
    double height = item["height"].toDouble();

    int32_t id = item["id"].toInt();
    auto parent = fromJsonValue<optional<int32_t>>(item["parent"]);

    auto [w, obj] = createContainer(m_ctx);

    auto object = new ContainerItem{m_ctx, w, obj};
    object->setId(id);
    object->setParentId(parent);
    container_objects[id] = {new ContainerItem{m_ctx, w, obj}, QRectF{x, y, width, height}};
  }

  for(const auto& [id, tpl] : container_objects)
  {
    const auto& [container, rect] = tpl;
    if(auto parent = container->parentId())
    {
      setup(*container->item(), rect.x(), rect.y(), (QObject*)std::get<0>(container_objects[*parent])->item());
    }
    else
    {
      setup(*container->item(), rect.x(), rect.y(), (QObject*)m_ctx.centralItem);
    }
    QQmlProperty(container->item(), "width").write(rect.width());
    QQmlProperty(container->item(), "height").write(rect.height());

    addContainer(container);
  }

  const auto items = page["Items"].toArray();
  for(const auto& item : items)
  {
    double x = item["x"].toDouble();
    double y = item["y"].toDouble();
    auto parent = fromJsonValue<optional<int32_t>>(item["parent"]);
    auto addr = fromJsonObject<Device::FullAddressSettings>(item["settings"]);
    QString type = item["type"].toString();

    QObject* parentItem = m_ctx.centralItem;
    if(parent)
    {
      parentItem = std::get<0>(container_objects[*parent])->item();
    }

    loadItem(std::move(type), std::move(addr), x, y, parent, parentItem);
  }

}

void CentralItemModel::setup(QQuickItem& obj, qreal x, qreal y, QObject* parent)
{
  QQmlProperty(&obj, "parent").write(QVariant::fromValue(parent));
  QQmlProperty(&obj, "x").write(x);
  QQmlProperty(&obj, "y").write(y);
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
        auto container = new ContainerItem{m_ctx, &factory, obj};
        container->setId(makeId(m_containers));
        addContainer(container);
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
          auto container = new ContainerItem{m_ctx, w, obj};
          container->setId(makeId(m_containers));
          addContainer(container);
        }
      }
    }
  }
}

void CentralItemModel::loadItem(QString type, Device::FullAddressSettings address, qreal x, qreal y, optional<int32_t> parent, QObject* parentItem)
{
  auto item = AddressItemFactory {m_ctx}.createItem(type);
  if (item)
  {
    item->setAddress(std::move(address));
    item->setParentId(parent);

    setup(*item->item(), x, y, parentItem);

    addItem(item);
  }
}

void CentralItemModel::addItem(GUIItem* item)
{
  m_guiItems.push_back(item);

  auto it = ossia::find_if(m_containers, [=] (ContainerItem* container) { return container->item() == item->item()->parentItem(); });
  if(it == m_containers.end())
  {
    item->setParentId(ossia::none);
  }
  else
  {
    item->setParentId((*it)->id());
  }

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

  auto it = ossia::find_if(m_containers, [=] (ContainerItem* container) { return container->item() == item->item()->parentItem(); });
  if(it == m_containers.end())
  {
    item->setParentId(ossia::none);
  }
  else
  {
    item->setParentId((*it)->id());
  }

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
