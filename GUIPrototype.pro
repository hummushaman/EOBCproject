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
    generatereport.cpp \
    numpatientsentry.cpp \
    occupancyrateentry.cpp \
    waittimesentry.cpp

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
    area.h \
    generatereport.h \
    numpatientsentry.h \
    occupancyrateentry.h \
    waittimesentry.h

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
