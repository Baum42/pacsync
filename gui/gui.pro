TEMPLATE = app

QT       += core gui widgets

TARGET = pacsync
VERSION = $$PACSYNCVER

#RC_ICONS += ./icons/pacsync.ico
QMAKE_TARGET_COMPANY = "Baum42"
QMAKE_TARGET_PRODUCT = $$TARGET
QMAKE_TARGET_DESCRIPTION = "Pac-Sync"
QMAKE_TARGET_COPYRIGHT = "Felix Barz & Mike Zeller"

ICON = main.icns
QMAKE_TARGET_BUNDLE_PREFIX = de.baum42

DEFINES += "TARGET=\\\"$$TARGET\\\""
DEFINES += "VERSION=\\\"$$VERSION\\\""
DEFINES += "COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\""
DEFINES += "DISPLAY_NAME=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\""
DEFINES += "BUNDLE=\"\\\"$$QMAKE_TARGET_BUNDLE_PREFIX\\\"\""

DEFINES += QT_DEPRECATED_WARNINGS

include(vendor/vendor.pri)

HEADERS += \
	editpackagesdialog.h \
    traycontrol.h

SOURCES += \
		main.cpp \
	editpackagesdialog.cpp \
    traycontrol.cpp

FORMS += \
	editpackagesdialog.ui

unix {
	target.path = $$[QT_INSTALL_BINS]
	INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lpacsync
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lpacsync
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lpacsync

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

RESOURCES += \
	pacsync_gui.qrc
