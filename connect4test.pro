QT += testlib
QT -= gui

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_idk.cpp\
    gamemanager.cpp\

HEADERS+= \
    gamemanager.h