#ifndef PACKAGEMANAGERPLUGIN_H
#define PACKAGEMANAGERPLUGIN_H

#include "lib_global.h"

#include <QObject>

class LIBSHARED_EXPORT PackageManagerPlugin : public QObject
{
public:
	struct FilterInfo {
		QString text;
		QString toolTip;
		bool defaultValue;
	};

	PackageManagerPlugin(QObject *parent = nullptr);

	virtual QList<FilterInfo> extraFilters() = 0;

	virtual QStringList listPackages(QList<bool> extraFilters) = 0;
	virtual void startInstallation(const QStringList &packages, bool noConfirm) = 0;
	virtual void startUninstallation(const QStringList &packages, bool noConfirm) = 0;

signals:
	void operationCompleted(bool success, const QString &message);
	void packagesChanged(const QStringList &added, const QStringList &removed);
};

#endif // PACKAGEMANAGERPLUGIN_H
