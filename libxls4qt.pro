#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T10:58:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = libxls4qt
TEMPLATE = app

# INCLUDEPATH += C:\\HowToBuildLibiconv_Src\\include

# comment the iconv lib reference for windows
# LIBS += -LC:\\HowToBuildLibiconv_Src\\Release_Win32 -llibiconv


SOURCES += main.cpp\
        mainwindow.cpp \
    libxls/ole.c \
    libxls/xls.c \
    libxls/xlstool.c \
    libxls/cppproxy.cpp

HEADERS  += mainwindow.h \
    libxls/brdb.c.h \
    libxls/brdb.h \
    libxls/config.h \
    libxls/ole.h \
    libxls/xls.h \
    libxls/xlsstruct.h \
    libxls/xlstool.h \
    libxls/xlstypes.h \
    libxls/cppproxy.h

FORMS    += mainwindow.ui

RESOURCES += \
    libxls4qt.qrc
