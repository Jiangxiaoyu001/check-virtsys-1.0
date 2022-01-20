QT      += core gui xml
QT      +=  charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += console
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/check_virtsts_genernalwindow.cpp \
    src/check_virtsys_aboutdialog.cpp \
    src/check_virtsys_basewindow.cpp \
    src/check_virtsys_detailedwindow.cpp \
    src/check_virtsys_manager.cpp \
    src/check_virtsys_nrcpuusagewindow.cpp \
    src/check_virtsys_thread.cpp \
    src/check_virtsys_virtsysdatainfo.cpp \
    src/check_virtsys_virtsysdomainwindow.cpp \
    src/check_virtsys_virtsysnetworkwindow.cpp \
    src/check_virtsys_window.cpp \
    src/check_virtsys_xml.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/check_virtsys.cpp
HEADERS += \
    src/check_virtsts_genernal.h \
    src/check_virtsts_genernalwindow.h \
    src/check_virtsys_aboutdialog.h \
    src/check_virtsys_basewindow.h\
    src/check_virtsys_detailedwindow.h \
    src/check_virtsys_manager.h \
    src/check_virtsys_nrcpuusagewindow.h \
    src/check_virtsys_thread.h \
    src/check_virtsys_virtsysdatainfo.h \
    src/check_virtsys_virtsysdomainwindow.h \
    src/check_virtsys_virtsysnetworkwindow.h \
    src/check_virtsys_window.h \
    src/check_virtsys_xml.h \
    src/mainwindow.h \
    src/check_virtsys.h \
    src/test.h
FORMS += \
    src/mainwindow.ui

# created an app for Makefile
TEMPLATE= app
# the specified dir of app build
DESTDIR =./

TARGET=check-virtsys
# Default rules for deployment.


unix:!android: {
    target.path = /usr/bin
    INSTALLS += target
    resource.path= /usr/share/qss
    resource.files = src/resource/QListWidget.qss
    !isEmpty(resource.path): {
        INSTALLS +=resource
    }
    desktop.path= /usr/share/applications/
    desktop.files = data/check-virtsys.desktop
    INSTALLS +=desktop
}


RESOURCES += \
    src/resource/resource.qrc

unix:!macx: LIBS += -lvirt -ldl



DISTFILES += \
    src/dealxml.py \
    src/resource/listwid \
    src/virsysInfo.py \
    src/xml.go
