QT += core gui widgets sql charts printsupport

CONFIG += c++11

TARGET = Atelier_Connexion
TEMPLATE = app

SOURCES += \
    authen.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    employe.cpp \
    connection.cpp

HEADERS += \
    authen.h \
    login.h \
    mainwindow.h \
    employe.h \
    connection.h

FORMS += \
    authen.ui \
    mainwindow.ui

# Pour éviter les warnings sur l'encodage
DEFINES += QT_DEPRECATED_WARNINGS
