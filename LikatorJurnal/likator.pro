#-------------------------------------------------
#
# Project created by QtCreator 2020-05-23T13:56:50
#
#-------------------------------------------------

QT       += core gui sql serialport
QT += widgets
QT += network
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
target.path = $$[QT_INSTALL_EXAMPLES]/charts/barchart
TARGET = likator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    CoreApp.cpp \
    CoreGui.cpp \
    MenuController.cpp \
    addcatmaster.cpp \
    addmaster.cpp \
    catadd.cpp \
    catchange.cpp \
    catdell.cpp \
    catmaster.cpp \
    catservice.cpp \
    customlineedit.cpp \
    delegate.cpp \
    dellcatmaster.cpp \
    device.cpp \
    firstdevice.cpp \
    humaninfo.cpp \
    insertwork.cpp \
    jurnal.cpp \
    main.cpp \
    mainwindow.cpp \
    master.cpp \
    masterchange.cpp \
    masterupdate.cpp \
    mydb.cpp \
    mymodelsql.cpp \
    politicdiscont.cpp \
    prizcode.cpp \
    service.cpp \
    servicedell.cpp \
    setting.cpp \
    timetable.cpp \
    window.cpp \
    woreff.cpp \
    yslygiinsert.cpp


HEADERS  += \
    CoreApp.h \
    CoreGui.h \
    MenuController.h \
    addcatmaster.h \
    addmaster.h \
    catadd.h \
    catchange.h \
    catdell.h \
    catmaster.h \
    catservice.h \
    customlineedit.h \
    delegate.h \
    dellcatmaster.h \
    device.h \
    firstdevice.h \
    humaninfo.h \
    insertwork.h \
    jurnal.h \
    mainwindow.h \
    master.h \
    masterchange.h \
    masterupdate.h \
    mydb.h \
    mymodelsql.h \
    politicdiscont.h \
    prizcode.h \
    service.h \
    servicedell.h \
    setting.h \
    timetable.h \
    window.h \
    woreff.h \
    yslygiinsert.h


FORMS    += \
    addcatmaster.ui \
    addmaster.ui \
    catadd.ui \
    catchange.ui \
    catdell.ui \
    catmaster.ui \
    catservice.ui \
    dellcatmaster.ui \
    firstdevice.ui \
    humaninfo.ui \
    insertwork.ui \
    jurnal.ui \
    mainwindow.ui \
    master.ui \
    masterchange.ui \
    masterupdate.ui \
    politicdiscont.ui \
    prizcode.ui \
    service.ui \
    servicedell.ui \
    setting.ui \
    timetable.ui \
    woreff.ui \
    yslygiinsert.ui

