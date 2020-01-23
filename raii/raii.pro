TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    raii.cpp \
    item.cpp

HEADERS += \
    raii.h \
    item.h
