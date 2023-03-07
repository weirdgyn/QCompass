#include "qcompassplugin.h"
#include "qcompass/qcompass.h"

QCompassPlugin::QCompassPlugin(QObject *parent) : QObject(parent) {}

void QCompassPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
  if (initialized)
    return;

  initialized = true;
}

bool QCompassPlugin::isInitialized() const { return initialized; }

QWidget *QCompassPlugin::createWidget(QWidget *parent) {
  return new QCompass(parent);
}

QString QCompassPlugin::name() const { return QStringLiteral("QCompass"); }

QString QCompassPlugin::group() const {
  return QStringLiteral("Custom widgets");
}

QIcon QCompassPlugin::icon() const { return QIcon(QLatin1String(":/images/compass.ico")); }

QString QCompassPlugin::toolTip() const { return QString(); }

QString QCompassPlugin::whatsThis() const { return QString(); }

bool QCompassPlugin::isContainer() const { return false; }

QString QCompassPlugin::domXml() const {
  return "<ui language=\"c++\" displayname=\"Compass\">\n"
         " <widget class=\"QCompass\" name=\"compass\">\n"
         "  <property name=\"geometry\">\n"
         "   <rect>\n"
         "    <x>0</x>\n"
         "    <y>0</y>\n"
         "    <width>600</width>\n"
         "    <height>48</height>\n"
         "   </rect>\n"
         "  </property>\n"
         "  <property name=\"toolTip\" >\n"
         "   <string>Compass</string>\n"
         "  </property>\n"
         "  <property name=\"whatsThis\" >\n"
         "   <string>A heading/compass indicator to use inside applications.</string>\n"
         "  </property>\n"
         " </widget>\n"
         "</ui>\n";
}

QString QCompassPlugin::includeFile() const {
  return QStringLiteral("qcompass/qcompass.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qcompassplugin, QCompassPlugin)
#endif // QT_VERSION < 0x050000
