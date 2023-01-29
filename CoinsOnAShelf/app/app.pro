QT       += core gui opengl charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
LIBS += -lglut -lGLU
CONFIG += c++17
TARGET = App

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algoritambaza.cpp \
    algoritmi_studentski_projekti/coinsonashelf.cpp \
    algoritmi_studentski_projekti/disk.cpp \
    algoritmi_studentski_projekti/gap.cpp \
    animacijanit.cpp \
    main.cpp \
    mainwindow.cpp \
    oblastcrtanja.cpp \
    oblastcrtanjaopengl.cpp \
    pomocnefunkcije.cpp \
    timemeasurementthread.cpp

HEADERS += \
    algoritambaza.h \
    algoritmi_studentski_projekti/coinsonashelf.h \
    algoritmi_studentski_projekti/disk.h \
    algoritmi_studentski_projekti/gap.h \
    animacijanit.h \
    config.h \
    mainwindow.h \
    oblastcrtanja.h \
    oblastcrtanjaopengl.h \
    pomocnefunkcije.h \
    timemeasurementthread.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    input_files/radiuses1.txt \
    input_files/radiuses2.txt \
    input_files/radiuses3.txt \

INSTALLS    += target
