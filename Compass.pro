QT          += widgets uiplugin

CONFIG += c++11

QTDIR_build {
# This is only for the Qt build. Do not use externally. We mean it.
PLUGIN_TYPE = designer
PLUGIN_CLASS_NAME = CompassPlugin
load(qt_plugin)
CONFIG += install_ok
} else {
CONFIG      += plugin
TEMPLATE    = lib
TARGET = $$qtLibraryTarget($$TARGET)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

}

HEADERS     = compassplugin.h \
    qcompass.h
SOURCES     = compassplugin.cpp \
    qcompass.cpp
#!

RESOURCES += \
    icons.qrc

include (compass/compass.pri)
