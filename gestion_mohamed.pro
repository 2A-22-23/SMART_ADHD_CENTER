QT       += core gui
QT       += charts
QT       += printsupport
QT       += axcontainer


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connectionclass.cpp \
    createaccount.cpp \
    dialog.cpp \
    dialog_mdp.cpp \
    expert.cpp \
    main.cpp \
    mainwindow.cpp \
    mdp.cpp \
    user.cpp \
    verification.cpp

HEADERS += \
    connectionclass.h \
    createaccount.h \
    dialog.h \
    dialog_mdp.h \
    expert.h \
    mainwindow.h \
    mdp.h \
    user.h \
    verification.h

FORMS += \
    createaccount.ui \
    dialog.ui \
    dialog_mdp.ui \
    expert.ui \
    mainwindow.ui \
    mdp.ui \
    verification.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT+=sql
CONFIG+=console
