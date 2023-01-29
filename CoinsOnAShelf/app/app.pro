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
#    algoritmi_sa_vezbi/ga00_demoiscrtavanja.cpp \
#    algoritmi_sa_vezbi/ga01_brisucaprava.cpp \
#    algoritmi_sa_vezbi/ga02_3discrtavanje.cpp \
#    algoritmi_sa_vezbi/ga03_konveksniomotac.cpp \
#    algoritmi_sa_vezbi/ga04_konveksniomotac3d.cpp \
#    algoritmi_sa_vezbi/ga05_preseciduzi.cpp \
#    algoritmi_sa_vezbi/ga06_dcel.cpp \
#    algoritmi_sa_vezbi/ga06_dceldemo.cpp \
#    algoritmi_sa_vezbi/ga07_triangulation.cpp \
#    algoritmi_sa_vezbi/ga08_delaunay_trinagulation.cpp \
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
#    algoritmi_sa_vezbi/ga00_demoiscrtavanja.h \
#    algoritmi_sa_vezbi/ga01_brisucaprava.h \
#    algoritmi_sa_vezbi/ga02_3discrtavanje.h \
#    algoritmi_sa_vezbi/ga03_konveksniomotac.h \
#    algoritmi_sa_vezbi/ga04_konveksni3dDatastructures.h \
#    algoritmi_sa_vezbi/ga04_konveksniomotac3d.h \
#    algoritmi_sa_vezbi/ga05_datastructures.h \
#    algoritmi_sa_vezbi/ga05_preseciduzi.h \
#    algoritmi_sa_vezbi/ga06_dcel.h \
#    algoritmi_sa_vezbi/ga06_dceldemo.h \
#    algoritmi_sa_vezbi/ga07_datastructures.h \
#    algoritmi_sa_vezbi/ga07_triangulation.h \
#    algoritmi_sa_vezbi/ga08_delaunay_triangulation.h \
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
