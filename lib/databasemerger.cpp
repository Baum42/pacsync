#include "databasecontroller.h"
#include "databasemerger.h"
#include "packagedatabase.h"

#include <QFile>

DatabaseMerger::DatabaseMerger(QObject *parent) :
	QObject(parent),
	_js(new QJsonSerializer(this)),
	_log()
{}

bool DatabaseMerger::mergeDb(QString dbPath)
{
	try {
		_log.clear();

		QFile currentFile(DatabaseController::instance()->currentPath());
		QFile otherFile(dbPath);
		if(!currentFile.open(QIODevice::ReadWrite))
			throw DatabaseException(currentFile.errorString());
		if(!otherFile.open(QIODevice::ReadOnly))
			throw DatabaseException(otherFile.errorString());

		PackageDatabase pacDbCurrent = _js->deserializeFrom<PackageDatabase>(&currentFile);
		PackageDatabase pacDbOther = _js->deserializeFrom<PackageDatabase>(&otherFile);
		otherFile.close();

		//packages: keep install on conflict
		foreach (auto pacInfo, pacDbOther.packages) {
			if(!pacDbCurrent.packages.contains(pacInfo.name))
				pacDbCurrent.packages[pacInfo.name] = pacInfo;
			else if(pacInfo.removed != pacDbCurrent.packages[pacInfo.name].removed)
				pacDbCurrent.packages[pacInfo.name].removed = false;
		}

		//unlearPackages: keep current on conflict
		foreach (auto unclearPac, pacDbOther.unclearPackages) {
			if(!pacDbCurrent.unclearPackages.contains(unclearPac.name))
				pacDbCurrent.unclearPackages[unclearPac.name] = unclearPac;
			else if(!unclearPac.equals(pacDbCurrent.unclearPackages[unclearPac.name]))
				_log.append({tr("unclear package"),  unclearPac.name});
		}


		//mode: keep current on conflict
		if(pacDbOther.globalMode != pacDbCurrent.globalMode)
			_log.append({tr("global mode"), QString()});

		//filter: auto rename on conflict
		foreach (auto filter, pacDbOther.filters){
			if(!pacDbCurrent.filters.contains(filter.name))
				pacDbCurrent.filters[filter.name] = filter;
			else if(!filter.equals(pacDbCurrent.filters[filter.name])){
				const auto oldName = filter.name;
				auto idx = 0;
				do
					filter.name = tr("%1-%2").arg(oldName).arg(++idx);
				while(pacDbCurrent.filters.contains(filter.name));
				pacDbCurrent.filters[filter.name] = filter;
				_log.append({tr("filter auto rename"),  tr("%1 -> %2")
							.arg(oldName)
							.arg(filter.name)});
			}
		}

		//extra filter: keep current on conflict
		foreach (auto eFilter, pacDbOther.extraFilters) {
			auto index = pacDbCurrent.extraFilters.indexOf(eFilter);
			if(index == -1)
				pacDbCurrent.extraFilters.append(eFilter);
			else if(!eFilter.equals(pacDbCurrent.extraFilters.at(index)))
				_log.append({tr("extra filter"),  eFilter.regex});
		}

		//settings keep current and log
		if(pacDbCurrent.settings != pacDbOther.settings)
			_log.append({tr("settings"), QString()});

		currentFile.seek(0);
		_js->serializeTo<PackageDatabase>(&currentFile, pacDbCurrent);
		currentFile.close();
		return true;
	} catch(QException &e) {
		qWarning() << "Failed to merge with error" << e.what();
		return false;
	}
}

QList<QPair<QString, QString> > DatabaseMerger::log() const
{
	return _log;
}
