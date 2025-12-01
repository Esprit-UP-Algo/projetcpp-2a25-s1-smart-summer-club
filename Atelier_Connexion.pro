QT       += core gui widgets sql charts printsupport

CONFIG += c++11

SOURCES += \
    main.cpp \
    connection.cpp \
    login.cpp \
    mainwindow.cpp \
    employe.cpp

HEADERS += \
    connection.h \
    login.h \
    mainwindow.h \
    employe.h

FORMS += \
    mainwindow.ui

# Pour éviter des soucis de chemin
INCLUDEPATH += .
