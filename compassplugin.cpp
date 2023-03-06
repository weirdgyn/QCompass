#include "compassplugin.h"
#include "qcompass/qcompass.h"

CompassPlugin::CompassPlugin(QObject *parent) : QObject(parent) {}

void CompassPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
  if (initialized)
    return;

  initialized = true;
}

bool CompassPlugin::isInitialized() const { return initialized; }

QWidget *CompassPlugin::createWidget(QWidget *parent) {
  return new QCompass(parent);
}

QString CompassPlugin::name() const { return QStringLiteral("QCompass"); }

QString CompassPlugin::group() const {
  return QStringLiteral("Custom widgets");
}

QIcon CompassPlugin::icon() const { return QIcon(QLatin1String(":/images/compass.ico")); }

QString CompassPlugin::toolTip() const { return QString(); }

QString CompassPlugin::whatsThis() const { return QString(); }

bool CompassPlugin::isContainer() const { return false; }

QString CompassPlugin::domXml() const {
  return "<ui language=\"c++\" displayname=\"Compass\">\n"
         " <widget class=\"QCompass\" name=\"compass\">\n"
         "  <property name=\"geometry\">\n"
         "   <rect>\n"
         "    <x>0</x>\n"
         "    <y>0</y>\n"
         "    <width>300</width>\n"
         "    <height>300</height>\n"
         "   </rect>\n"
         "  </property>\n"
         "  <property name=\"toolTip\" >\n"
         "   <string>Compass</string>\n"
         "  </property>\n"
         "  <property name=\"whatsThis\" >\n"
         "   <string>A heading/compassi indicator to use inside applications.</string>\n"
         "  </property>\n"
         " </widget>\n"
         "</ui>\n";
}

QString CompassPlugin::includeFile() const {
  return QStringLiteral("qcompass/qcompass.h");
}
