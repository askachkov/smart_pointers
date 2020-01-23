TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    item.cpp

HEADERS += \
    shared_ptr.h \
    weak_ptr.h \
    item.h
