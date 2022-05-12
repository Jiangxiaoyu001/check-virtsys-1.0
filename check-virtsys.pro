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
    src/RemoteConnect/main.cpp \
    src/RemoteConnect/remote-connect-mainWindow.cpp \
    src/RemoteConnect/remote-connect-vnc.cpp \
    src/RemoteConnect/rfbclient-manage.cpp \
    src/checkVirsys/check_virtsts_genernal.cpp \
    src/checkVirsys/check_virtsts_genernalwindow.cpp \
    src/checkVirsys/check_virtsys.cpp \
    src/checkVirsys/check_virtsys_aboutdialog.cpp \
    src/checkVirsys/check_virtsys_basewindow.cpp \
    src/checkVirsys/check_virtsys_detailedwindow.cpp \
    src/checkVirsys/check_virtsys_manager.cpp \
    src/checkVirsys/check_virtsys_nrcpuusagewindow.cpp \
    src/checkVirsys/check_virtsys_thread.cpp \
    src/checkVirsys/check_virtsys_virtsysdatainfo.cpp \
    src/checkVirsys/check_virtsys_virtsysdomainwindow.cpp \
    src/checkVirsys/check_virtsys_virtsysnetworkwindow.cpp \
    src/checkVirsys/check_virtsys_window.cpp \
    src/checkVirsys/check_virtsys_xml.cpp \
    src/checkVirsys/mainwindow.cpp \
    src/virCloudManage/main.cpp \
    src/widgets/PopupWidget.cpp \
    src/widgets/ScrollBar.cpp \
    src/widgets/Splitter.cpp \
    src/widgets/framelesswidget.cpp

HEADERS += \
    include/checkVirsys/check_virtsts_genernal.h \
    include/checkVirsys/check_virtsts_genernalwindow.h \
    include/checkVirsys/check_virtsys.h \
    include/checkVirsys/check_virtsys_aboutdialog.h \
    include/checkVirsys/check_virtsys_basewindow.h \
    include/checkVirsys/check_virtsys_detailedwindow.h \
    include/checkVirsys/check_virtsys_manager.h \
    include/checkVirsys/check_virtsys_nrcpuusagewindow.h \
    include/checkVirsys/check_virtsys_thread.h \
    include/checkVirsys/check_virtsys_virtsysdatainfo.h \
    include/checkVirsys/check_virtsys_virtsysdomainwindow.h \
    include/checkVirsys/check_virtsys_virtsysnetworkwindow.h \
    include/checkVirsys/check_virtsys_window.h \
    include/checkVirsys/check_virtsys_xml.h \
    include/checkVirsys/mainwindow.h \
    include/virCloudManage/mainwindow.h \
    include/widgets/framelesswidget.h \
    src/RemoteConnect/remote-connect-mainWindow.h \
    src/RemoteConnect/remote-connect-vnc.h \
    src/RemoteConnect/rfbproto.h \
    src/SRC_autogen/moc_predefs.h \
    src/check_virtsts_genernal.h \
    src/mainwindow.h \
    src/test.h \
    src/widgets/PopupWidget.h \
    src/widgets/ScrollBar.h \
    src/widgets/Splitter.h

FORMS += \
    src/checkVirsys/mainwindow.ui

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
    resource.files =resource/QListWidget.qss
    !isEmpty(resource.path): {
        INSTALLS +=resource
    }
    desktop.path= /usr/share/applications/
    desktop.files = data/check-virtsys.desktop
    INSTALLS +=desktop
}

RC_FILE += \
    resource/ico.rc
RESOURCES += \
    #resource/resource.qrc \

unix:!macx: LIBS += -lvirt -ldl

INCLUDEPATH += \
    include

DISTFILES += \ \
    src/RemoteConnect/CMakeLists.txt

