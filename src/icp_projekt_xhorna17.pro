QT       += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    file_manage.cpp \
    game.cpp \
    game_object.cpp \
    lose_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    replay.cpp \
    step.cpp \
    win_dialog.cpp

HEADERS += \
    file_manage.h \
    game.h \
    game_object.h \
    lose_dialog.h \
    mainwindow.h \
    menu.h \
    replay.h \
    step.h \
    win_dialog.h

FORMS += \
    lose_dialog.ui \
    mainwindow.ui \
    menu.ui \
    win_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    dialogs.qrc \
    game_icons.qrc \
    menu_icon.qrc \
    replay_button_icons.qrc
