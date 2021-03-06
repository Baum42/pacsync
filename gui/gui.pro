TEMPLATE = app

QT += core gui widgets

TARGET = paxchange
VERSION = $$PAXCHANGEVER

RC_ICONS += ./icons/paxchange.ico
QMAKE_TARGET_COMPANY = "Baum42"
QMAKE_TARGET_PRODUCT = $$TARGET
QMAKE_TARGET_DESCRIPTION = "Paxchange"
QMAKE_TARGET_COPYRIGHT = "Felix Barz & Mike Zeller"

ICON = ./icons/paxchange.icns
QMAKE_TARGET_BUNDLE_PREFIX = de.baum42

DEFINES += "TARGET=\\\"$$TARGET\\\""
DEFINES += "VERSION=\\\"$$VERSION\\\""
DEFINES += "COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\""
DEFINES += "DISPLAY_NAME=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\""
DEFINES += "BUNDLE=\"\\\"$$QMAKE_TARGET_BUNDLE_PREFIX\\\"\""

HEADERS += \
	traycontrol.h \
	contentdialog.h \
	packagemodel.h \
	settingsdialog.h \
	consoleoperator.h \
	widgets/editpackageswidget.h \
	widgets/globalfilterwidget.h \
	wizard/databasewizard.h \
	wizard/dbselectionpage.h \
	wizard/dbpathpage.h \
	wizard/dbwidgetpage.h \
	widgets/filterswidget.h \
	widgets/extrafilterswidget.h \
	widgets/unclearpackageswidget.h \
	dbmergerdialog.h

SOURCES += \
	main.cpp \
	traycontrol.cpp \
	contentdialog.cpp \
	packagemodel.cpp \
	settingsdialog.cpp \
	consoleoperator.cpp \
	widgets/editpackageswidget.cpp \
	widgets/globalfilterwidget.cpp \
	wizard/databasewizard.cpp \
	wizard/dbselectionpage.cpp \
	wizard/dbpathpage.cpp \
	wizard/dbwidgetpage.cpp \
	widgets/filterswidget.cpp \
	widgets/extrafilterswidget.cpp \
	widgets/unclearpackageswidget.cpp \
	dbmergerdialog.cpp

FORMS += \
	settingsdialog.ui \
	widgets/editpackageswidget.ui \
	widgets/globalfilterwidget.ui \
	wizard/dbselectionpage.ui \
	wizard/dbpathpage.ui \
	widgets/filterswidget.ui \
	widgets/extrafilterswidget.ui \
	widgets/unclearpackageswidget.ui \
	dbmergerdialog.ui

RESOURCES += \
	paxchange_gui.qrc

TRANSLATIONS += paxchange_gui_de.ts \
	paxchange_gui_template.ts

DISTFILES += \
	application-x-paxchange-database.xml \
	paxchange.desktop \
	$$TRANSLATIONS

unix {
	target.path = $$[QT_INSTALL_BINS]
	qpmx_ts_target.path = $$[QT_INSTALL_TRANSLATIONS]
	qpmx_ts_target.files += paxchange_gui_template.ts
	INSTALLS += target qpmx_ts_target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lpaxchange
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lpaxchange
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lpaxchange

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

!ReleaseBuild:!DebugBuild:!system(qpmx -d $$shell_quote($$_PRO_FILE_PWD_) --qmake-run init $$QPMX_EXTRA_OPTIONS $$shell_quote($$QMAKE_QMAKE) $$shell_quote($$OUT_PWD)): error(qpmx initialization failed. Check the compilation log for details.)
else: include($$OUT_PWD/qpmx_generated.pri)
