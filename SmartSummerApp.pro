QT       += core gui sql charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    databasemanager.cpp \
    abonne.cpp \
    activite.cpp \
    inscription.cpp \
    abonnedao.cpp \
    activitedao.cpp \
    inscriptiondao.cpp \
    gestioninscriptionswidget.cpp \
    dashboardwidget.cpp \
    arduinocommunication.cpp

HEADERS += \
    mainwindow.h \
    databasemanager.h \
    abonne.h \
    activite.h \
    inscription.h \
    abonnedao.h \
    activitedao.h \
    inscriptiondao.h \
    gestioninscriptionswidget.h \
    dashboardwidget.h \
    arduinocommunication.h

# Nettoyage personnalisé
QMAKE_CLEAN += -r

FORMS += \
    mainwindow.ui \
    dashboardwidget.ui \
    gestioninscriptionswidget.ui