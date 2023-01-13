QT       += core gui
QT       +=network
QT       +=axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    adddialog.cpp \
    control.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    registerwidget.cpp \
    smtp.cpp \
    student.cpp

HEADERS += \
    adddialog.h \
    control.h \
    login.h \
    mainwindow.h \
    registerwidget.h \
    smtp.h \
    student.h

FORMS += \
    adddialog.ui \
    login.ui \
    mainwindow.ui \
    registerwidget.ui

CONFIG +=resources_big
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc \
    res.qrc

DISTFILES +=
