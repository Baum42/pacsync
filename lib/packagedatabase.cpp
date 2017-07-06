#include "packagedatabase.h"

PackageInfo::PackageInfo(QString name, bool removed) :
	name(name),
	removed(removed)
{}

bool PackageInfo::isValid() const
{
	return !name.isNull();
}

bool PackageInfo::operator ==(const PackageInfo &other) const
{
	return name == other.name;
}

bool PackageInfo::equals(const PackageInfo &other) const
{
	return name == other.name &&
			removed == other.removed;
}

UnclearPackageInfo::UnclearPackageInfo(QString name, QString hostName, QStringList filterNames) :
	PackageInfo(name),
	hostName(hostName),
	filterNames(filterNames)
{}

bool UnclearPackageInfo::operator ==(const UnclearPackageInfo &other) const
{
	return ((PackageInfo)*this) == (PackageInfo)other;
}

bool UnclearPackageInfo::equals(const UnclearPackageInfo &other) const
{
	return PackageInfo::equals(other) &&
			hostName == other.hostName &&
			filterNames == other.filterNames;
}

FilterInfo::FilterInfo(const QString &name, const QString &plugin) :
	name(name),
	plugin(plugin),
	mode(Ask),
	pluginFilters(),
	regex()
{}

bool FilterInfo::operator ==(const FilterInfo &other) const
{
	return name == other.name;
}

bool FilterInfo::equals(const FilterInfo &other) const
{
	return name == other.name &&
			plugin == other.plugin &&
			mode == other.mode &&
			pluginFilters == other.pluginFilters &&
			regex == other.regex;
}

ExtraFilter::ExtraFilter(QString regex, FilterInfo::Mode mode) :
	regex(regex),
	mode(mode)
{}

bool ExtraFilter::operator ==(const ExtraFilter &other) const
{
	return regex == other.regex;
}

bool ExtraFilter::equals(const ExtraFilter &other) const
{
	return regex == other.regex &&
			mode == other.mode;
}

PackageDatabase::PackageDatabase() :
	packages(),
	unclearPackages(),
	globalMode(FilterInfo::Ask),
	filters(),
	extraFilters(),
	settings()
{}
