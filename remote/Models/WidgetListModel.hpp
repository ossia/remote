#pragma once
#include <QDebug>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <WidgetKind.hpp>
namespace RemoteUI
{
/** An instance of this class represents a type of widget that can be instantiated.
 * There are two components:
 * - the main component which is put on CentralItemModel
 * - And the static component which is shown in the widget list
 */
class WidgetListData : public QObject
{
  Q_OBJECT

  Q_ENUM(WidgetKind)
  Q_PROPERTY(WidgetKind widgetKind READ widgetKind NOTIFY widgetKindChanged)
  Q_PROPERTY(QString name READ name NOTIFY nameChanged)
  Q_PROPERTY(QString prettyName READ prettyName NOTIFY prettyNameChanged)
  Q_PROPERTY(QString dragImageSource READ dragImageSource NOTIFY dragImageSourceChanged)
  Q_PROPERTY(QQmlComponent* component READ component)
  Q_PROPERTY(QQmlComponent* exampleComponent READ exampleComponent)
public:
  WidgetListData(
      WidgetKind kind,
      QString name,
      QString prettyName,
      QString dragImageSource,
      QUrl comp,
      QUrl exampleComp,
      QQmlApplicationEngine& eng)
      : m_kind{kind}
      , m_name{name}
      , m_prettyName{prettyName}
      , m_dragImageSource{dragImageSource}
      , m_component{&eng, comp}
      , m_exampleComponent{&eng, exampleComp}
  {
    auto e = m_component.errorString();
    if (!e.isEmpty())
      qDebug() << "Error while creating" << name << ": " << e;
  }

  ~WidgetListData();

  QString name() const
  {
    return m_name;
  }

  QString dragImageSource() const
  {
    return m_dragImageSource;
  }

  const QQmlComponent* component() const
  {
    return &m_component;
  }
  QQmlComponent* component()
  {
    return &m_component;
  }

  QString prettyName() const
  {
    return m_prettyName;
  }

  const QQmlComponent* exampleComponent() const
  {
    return &m_exampleComponent;
  }
  QQmlComponent* exampleComponent()
  {
    return &m_exampleComponent;
  }

  WidgetKind widgetKind() const
  {
    return m_kind;
  }

Q_SIGNALS:
  void nameChanged(QString name);

  void prettyNameChanged(QString prettyName);

  void dragImageSourceChanged(QString dragImageSource);

  void widgetKindChanged(WidgetKind widgetKind);

private:
  WidgetKind m_kind;
  QString m_name;
  QString m_prettyName;
  QString m_dragImageSource;
  QQmlComponent m_component;
  QQmlComponent m_exampleComponent;
};

//! Register new widgets in this class
struct WidgetListModel
{
  WidgetListModel(QQmlApplicationEngine& engine);
  QList<RemoteUI::WidgetListData*> componentList;
  QList<QObject*> objectList;
};
}
