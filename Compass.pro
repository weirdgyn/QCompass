CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(qcompassplugin)
TEMPLATE    = lib

HEADERS     = qcompassplugin.h
SOURCES     = qcompassplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L.

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer gui
} else {
    CONFIG += designer gui
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(qcompass/qcompass.pri)
