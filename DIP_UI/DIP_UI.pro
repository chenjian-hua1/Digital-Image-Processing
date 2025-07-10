QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bitplaneform.cpp \
    dip.cpp \
    filterform.cpp \
    imgform.cpp \
    main.cpp \
    mainwindow.cpp \
    rotateform.cpp \
    scaleform.cpp \
    teamform.cpp \
    videoform.cpp

HEADERS += \
    DIP_Struct.h \
    bitplaneform.h \
    dip.h \
    filterform.h \
    imgform.h \
    mainwindow.h \
    rotateform.h \
    scaleform.h \
    teamform.h \
    videoform.h

FORMS += \
    bitplaneform.ui \
    filterform.ui \
    imgform.ui \
    mainwindow.ui \
    rotateform.ui \
    scaleform.ui \
    teamform.ui \
    videoform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += charts core gui multimedia multimediawidgets
