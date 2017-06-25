TEMPLATE = lib

QT += jsonserializer
QT -= gui

TARGET = pacsync
VERSION = $$PACSYNCVER

DEFINES += PACSYNC_LIBRARY

!custom_standard_plg: DEFINES += PS_STD_PLG=\\\"\\\"

include(vendor/vendor.pri)

HEADERS += \
	packagemanagerplugin.h \
	pluginloader.h \
	exception.h \
	databasecontroller.h \
	packagedatabase.h \
	operationqueue.h \
	libpacsync_global.h \
	dbsettings.h \
	comboboxconfig.h

SOURCES += \
	packagemanagerplugin.cpp \
	pluginloader.cpp \
	exception.cpp \
	databasecontroller.cpp \
	packagedatabase.cpp \
	operationqueue.cpp \
	dbsettings.cpp \
	comboboxconfig.cpp

unix {
	target.path = $$[QT_INSTALL_LIBS]
	INSTALLS += target
}
