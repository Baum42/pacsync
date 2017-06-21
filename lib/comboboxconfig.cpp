#include "comboboxconfig.h"

ComboboxConfig::ComboboxConfig(QStringList displayNames, QList<QVariant> values, QVariant defaultValue) :
	displayNames(displayNames),
	values(values),
	defaultValue(defaultValue)
{}

QVariant ComboboxConfig::getValue(const QString &key) const
{
	auto idx = displayNames.indexOf(key);
	if(idx == -1)
		return {};
	else
		return values[idx];
}

QString ComboboxConfig::getKey(const QVariant &value) const
{
	auto idx = values.indexOf(value);
	if(idx == -1)
		return {};
	else
		return displayNames[idx];
}
