#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
//	QApplication::setApplicationName(QStringLiteral(TARGET));
//	QApplication::setApplicationVersion(QStringLiteral(VERSION));
//	QApplication::setOrganizationName(QStringLiteral(COMPANY));
//	QApplication::setOrganizationDomain(QStringLiteral(BUNDLE_PREFIX));
//	QApplication::setApplicationDisplayName(QStringLiteral(APPNAME));
//	QApplication::setWindowIcon(QIcon(QStringLiteral(":/icons/main.ico")));

	MainWindow w;
	w.show();

	return a.exec();
}
