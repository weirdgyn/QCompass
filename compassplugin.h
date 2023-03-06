#ifndef COMPASSPLUGIN_H
#define COMPASSPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class CompassPlugin : public QObject, public QDesignerCustomWidgetInterface {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
  Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
  explicit CompassPlugin(QObject *parent = nullptr);

  bool isContainer() const override;
  bool isInitialized() const override;
  QIcon icon() const override;
  QString domXml() const override;
  QString group() const override;
  QString includeFile() const override;
  QString name() const override;
  QString toolTip() const override;
  QString whatsThis() const override;
  QWidget *createWidget(QWidget *parent) override;
  void initialize(QDesignerFormEditorInterface *core) override;

private:
  bool initialized = false;
};

#endif // COMPASSPLUGIN_H
