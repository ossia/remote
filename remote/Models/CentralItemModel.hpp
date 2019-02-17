#ifndef CENTRALITEMMODEL_H
#define CENTRALITEMMODEL_H

#include <QObject>
#include <QQuickItem>

#include <Device/Address/AddressSettings.hpp>
#include <Models/WidgetListModel.hpp>
#include <RemoteContext.hpp>

class QQmlApplicationEngine;

namespace RemoteUI
{
class GUIItem;
class ContainerItem;

//! Data model for the control surface: just a list of widgets
class CentralItemModel : public QObject
{
  Q_OBJECT
public:
  explicit CentralItemModel(Context&, QObject* parent = 0);

public Q_SLOTS:
  void load(QUrl path);
  void save(QUrl path);

  void on_itemCreated(QString data, qreal x, qreal y, QQuickItem* parent);
  void on_addressCreated(QString data, qreal x, qreal y, QQuickItem* parent);

  void addItem(GUIItem* item);
  void removeItem(GUIItem* item);

  void addContainer(ContainerItem* item);
  void removeContainer(ContainerItem* item);
private:
  void loadItem(QString type, Device::FullAddressSettings address, qreal x, qreal y, optional<int32_t> parent, QObject* parentItem);
  void setup(QQuickItem& obj, qreal x, qreal y, QObject* parent);

  Context& m_ctx;
  QList<GUIItem*> m_guiItems;
  QList<ContainerItem*> m_containers;
};
}
#endif // CENTRALITEMMODEL_H
