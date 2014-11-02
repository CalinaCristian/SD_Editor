#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T21:16:48
#
#-------------------------------------------------

QT       += core gui

CONFIG   += console \
		qt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sd_editor
TEMPLATE = app

INCLUDEPATH += src \
			include \
			backend_src

SOURCES += src/main.cpp\
		src/mainwindow.cpp\
		src/SpacePressEater.cpp

HEADERS  += include/mainwindow.h\
		 include/SpacePressEater.h

FORMS    += include/mainwindow.ui

OBJECTS_DIR = build/
UI_DIR = build/
MOC_DIR = build/

LIBS += backend_src/lib-backend.so
PRE_TARGETDEPS += backend_src/lib-backend.so
