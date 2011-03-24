#-------------------------------------------------
#
# Project created by QtCreator 2011-02-01T13:08:48
#
#-------------------------------------------------

QT       += core gui //need this for the GUI to work
QT       += sql

TARGET = GUIPrototype
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    welcome.cpp \
    addbed.cpp \
    removepatient.cpp \
    viewfacility.cpp \
    assignbed.cpp \
    addpatienttowaitinglist.cpp \
    removepatientfromwaitinglist.cpp \
    viewwaitinglist.cpp \
    adduser.cpp \
    addfacility.cpp \
    map.cpp \
    facility.cpp \
    area.cpp \
    hospital.cpp \
    occupanyratelog.cpp \
    waitinglist.cpp \
    occupancyrateentry.cpp \
    waitinglistentry.cpp \
    waittimeslog.cpp \
    waittimesentry.cpp \
    generatereport.cpp

HEADERS  += login.h \
    welcome.h \
    addbed.h \
    removepatient.h \
    viewfacility.h \
    assignbed.h \
    addpatienttowaitinglist.h \
    removepatientfromwaitinglist.h \
    viewwaitinglist.h \
    adduser.h \
    addfacility.h \
    map.h \
    facility.h \
    area.h \
    hospital.h \
    occupanyratelog.h \
    waitinglist.h \
    occupancyrateentry.h \
    waitinglistentry.h \
    waittimeslog.h \
    waittimesentry.h \
    generatereport.h

FORMS    += login.ui \
    welcome.ui \
    addbed.ui \
    removepatient.ui \
    viewfacility.ui \
    assignbed.ui \
    addpatienttowaitinglist.ui \
    removepatientfromwaitinglist.ui \
    viewwaitinglist.ui \
    adduser.ui \
    addfacility.ui \
    map.ui \
    generatereport.ui
