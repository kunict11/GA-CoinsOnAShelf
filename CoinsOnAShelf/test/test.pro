QT += testlib core opengl charts
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17 qt testcase warn_on depend_includepath
TARGET = test
TEMPLATE = app

INCLUDEPATH += ../app/

SOURCES += \
    tst_coinsonashelftest.cpp \
    ../app/algoritambaza.cpp \
    ../app/animacijanit.cpp \
    ../app/algoritmi_studentski_projekti/coinsonashelf.cpp \
    ../app/algoritmi_studentski_projekti/disk.cpp \
    ../app/algoritmi_studentski_projekti/gap.cpp \
    ../app/oblastcrtanja.cpp \

HEADERS += \
    ../app/algoritambaza.h \
    ../app/animacijanit.h \
    ../app/algoritmi_studentski_projekti/coinsonashelf.h \
    ../app/algoritmi_studentski_projekti/coinsonashelf.h \
    ../app/algoritmi_studentski_projekti/disk.h \
    ../app/algoritmi_studentski_projekti/gap.h \
    ../app/oblastcrtanja.h \


DESTDIR = ../bin
