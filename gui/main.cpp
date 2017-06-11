#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include "traycontrol.h"
#include "pluginloader.h"
#include "databasewizard.h"

static void setupParser(QCommandLineParser &parser);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setApplicationName(QStringLiteral(TARGET));
	QApplication::setApplicationVersion(QStringLiteral(VERSION));
	QApplication::setOrganizationName(QStringLiteral(COMPANY));
	QApplication::setOrganizationDomain(QStringLiteral(BUNDLE));
	QApplication::setApplicationDisplayName(QStringLiteral(DISPLAY_NAME));
	QApplication::setWindowIcon(QIcon(QStringLiteral(":/icons/main.svg")));
	QApplication::setQuitOnLastWindowClosed(false);

	QCommandLineParser parser;
	setupParser(parser);
	parser.process(a);

	try {
		PluginLoader::loadPlugin(parser.value("p"));
	} catch(PluginLoadException &e) {
		qCritical() << e.what();
		return EXIT_FAILURE;
	}

	return DatabaseWizard::run();

	TrayControl tray;
	return a.exec();
}

static void setupParser(QCommandLineParser &parser)
{
	parser.addVersionOption();
	parser.addHelpOption();

	parser.addOption({
						 {"p", "pacin"},
						 "Explicitly select the plugin to be loaded",
						 "plugin"
					 });
}
