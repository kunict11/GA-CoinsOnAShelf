CONFIG += c++17
TEMPLATE = subdirs

OTHER_FILES += \
    app/app.pro \
    test/test.pro

SUBDIRS += \
    app \
    test \

test.depends = app


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
