QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    gestion_materielle.cpp \
    main.cpp \
    mainwindow.cpp
    gestion_materielle.cpp
HEADERS += \
    database.h \
    gestion_materielle.h \
    mainwindow.h
    gestion_materielle.h
FORMS += \
    mainwindow.ui
    gestion_materielle.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
