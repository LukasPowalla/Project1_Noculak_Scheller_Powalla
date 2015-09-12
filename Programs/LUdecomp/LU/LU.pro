TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += C:\_user\Lukas\Uni\Armadillon\armadillo-5\armadillo-5.500.2\include
SOURCES += main.cpp
LIBS += -L C:\Windows
LIBS += -llibblas -lliblapack
