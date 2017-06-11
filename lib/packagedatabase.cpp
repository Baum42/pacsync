#include "packagedatabase.h"




PackageInfo::PackageInfo(QString name, bool conflict) :
	name(name),
	conflict(conflict)
{

}

bool PackageInfo::operator ==(const PackageInfo &other) const
{
	return this->name == other.name;
}

PackageDatabase::PackageDatabase() :
	mode(BlackList),
	packages()
{

}

void PackageDatabase::parseHarderFromJson(QJsonSerializer *s)
{
	for(auto it = _pkg.constBegin(); it != _pkg.constEnd(); it++)
		packages.insert(it.key(), s->deserialize<PackageInfo>(it.value().toObject()));

	_pkg = QJsonObject();
}

void PackageDatabase::parseHarderToJson(QJsonSerializer *s)
{
	for(auto it = packages.constBegin(); it != packages.constEnd(); it++)
		_pkg.insert(it.key(), s->serialize<PackageInfo>(it.value()));
}
