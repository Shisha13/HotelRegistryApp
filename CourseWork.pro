#-------------------------------------------------
#
# Project created by QtCreator 2019-04-04T22:02:03
#
#-------------------------------------------------

QT       += core gui\
         xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseWork
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Logic/room.cpp \
    Logic/model.cpp \
    Logic/delegate.cpp \
    Controls/dateseditdialog.cpp \
    Controls/calendarwidget.cpp \
    Controls/roomDataList.cpp \
    Controls/addpersonsdialog.cpp \
    Controls/roomseditdialog.cpp \
    Logic/filterproxymodel.cpp

HEADERS += \
        mainwindow.h \
    model.h \
    Logic/room.h \
    Logic/model.h \
    Logic/delegate.h \
    Controls/dateseditdialog.h \
    calendarwidget.h \
    Controls/calendarwidget.h \
    Controls/roomDataList.h \
    Controls/addpersonsdialog.h \
    Controls/roomseditdialog.h \
    Logic/filterproxymodel.h

FORMS += \
        mainwindow.ui \
    Controls/dateseditdialog.ui \
    Controls/addpersonsdialog.ui \
    Controls/roomseditdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
