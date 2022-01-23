QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Plants.cpp \
    Sun.cpp \
    Zombies.cpp \
    diy.cpp \
    game_over.cpp \
    login.cpp \
    main.cpp \
    menu.cpp \
    plants_zombies.cpp

HEADERS += \
    Plants.h \
    Sun.h \
    Zombies.h \
    diy.h \
    game_over.h \
    login.h \
    menu.h \
    plants_zombies.h

FORMS += \
    diy.ui \
    game_over.ui \
    login.ui \
    menu.ui \
    plants_zombies.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MAP.qrc
