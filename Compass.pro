CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(qlockbuttonplugin)
TEMPLATE    = lib

HEADERS     = qcompass.h
SOURCES     = qcompass.cpp
RESOURCES   = icons.qrc
LIBS        += -L.

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer gui multimedia svg
} else {
    CONFIG += designer gui multimedia svg
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(qcompass/qcompass.pri)
