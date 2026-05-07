#-------------------------------------------------
#
# Project created by QtCreator 2026-02-03T16:03:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SensorSimulator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    GPS/CRMCView.cpp \
    GPS/GLL.cpp \
    GPS/GGA.cpp \
    GPS/ZDA.cpp \
    Server/Server.cpp \
    Server/UDPServer.cpp \
    Server/tcpserver.cpp \
    GPS/IBS.cpp \
    GPS/AIS.cpp \
    GPS/LOG.cpp \
    GPS/AWOS.cpp \
    GPS/MWV.cpp \
    GPS/XDR.cpp \
    GPS/ECHO.cpp \
    GPS/GYRO.cpp \


HEADERS += \
        mainwindow.h \
    GPS/CRMCView.h \
    GPS/GLL.h \
    GPS/GGA.h \
    GPS/ZDA.h \
    Server/Server.h \
    Server/UDPServer.h \
    Server/tcpserver.h \
    GPS/IBS.h \
    GPS/AIS.h \
    GPS/LOG.h \
    GPS/AWOS.h \
    GPS/MWV.h \
    GPS/XDR.h \
    GPS/ECHO.h \
    GPS/GYRO.h \
    Server/tcpserver.h

FORMS += \
        mainwindow.ui \
    GPS/CRMCView.ui \
    GPS/GLL.ui \
    GPS/GGA.ui \
    GPS/ZDA.ui \
    Server/Server.ui \
    Server/UDPServer.ui \
    GPS/IBS.ui \
    GPS/AIS.ui \
    GPS/LOG.ui \
    GPS/AWOS.ui \
    GPS/MWV.ui \
    GPS/XDR.ui \
    GPS/ECHO.ui \
    GPS/GYRO.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
