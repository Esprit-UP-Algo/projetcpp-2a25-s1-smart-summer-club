QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app
CONFIG += c++11

SOURCES += \
    main.cpp \
    connection.cpp \
    mainwindow.cpp \
    employe.cpp

HEADERS += \
    connection.h \
    mainwindow.h \
    employe.h

FORMS += \
    mainwindow.ui
