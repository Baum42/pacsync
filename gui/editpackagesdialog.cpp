#include "editpackagesdialog.h"
#include "ui_editpackagesdialog.h"
#include "pluginloader.h"
#include <QDebug>

EditPackagesDialog::EditPackagesDialog(QWidget *parent) :
	QDialog(parent),
	_ui(new Ui::EditPackagesDialog),
	_plugin(PluginLoader::plugin()),
	_boxes(),
	_pkgModel(new QStringListModel(this)),
	_dbModel(new QStringListModel(this))
{
	_ui->setupUi(this);
	_ui->localPackageListView->setModel(_pkgModel);
	_ui->dbPackageListView->setModel(_dbModel);

	connect(_ui->regexEdit, &QLineEdit::textChanged,
			this, &EditPackagesDialog::reloadPackages);
}

EditPackagesDialog::~EditPackagesDialog()
{
	delete _ui;
}

QStringList EditPackagesDialog::editPackages(QWidget *parent, const QStringList &currentPackages, bool *ok)
{
	EditPackagesDialog dialog(parent);
	dialog._dbModel->setStringList(currentPackages);
	dialog.setupFilters();
	dialog.reloadPackages();

	if(dialog.exec() == QDialog::Accepted) {
		if(ok)
			*ok = true;
		return dialog._dbModel->stringList();
	} else {
		if(ok)
			*ok = false;
		return currentPackages;
	}
}

void EditPackagesDialog::setupFilters()
{
	foreach (auto filter, _plugin->extraFilters()) {
		auto check = new QCheckBox(filter.text, _ui->groupBox);
		check->setToolTip(filter.toolTip);
		check->setChecked(filter.defaultValue);
		connect(check, &QCheckBox::clicked,
				this, &EditPackagesDialog::reloadPackages);
		_ui->checkLayout->addWidget(check);
		_boxes.append(check);
	}

	if(_boxes.isEmpty())
		_ui->groupBox->setVisible(false);
}

void EditPackagesDialog::reloadPackages()
{
	QRegularExpression regex(_ui->regexEdit->text(),
							 QRegularExpression::CaseInsensitiveOption |
							 QRegularExpression::DontCaptureOption |
							 QRegularExpression::DontAutomaticallyOptimizeOption);
	if(regex.isValid()) {
		QList<bool> filters;
		foreach(auto box, _boxes)
			filters.append(box->isChecked());
		auto packages = _plugin->listPackages(filters);
		_pkgModel->setStringList(packages.filter(regex));
	}
}

void EditPackagesDialog::on_addButton_clicked()
{
	auto indexes = _ui->localPackageListView->selectionModel()->selectedIndexes();
	auto targetList = _dbModel->stringList();
	foreach(auto index, indexes) {
		auto pkgName = _pkgModel->data(index, Qt::DisplayRole).toString();//TODO 5.9
		if(!targetList.contains(pkgName))
			targetList.append(pkgName);
	}
	_dbModel->setStringList(targetList);
}

void EditPackagesDialog::on_removeButton_clicked()
{
	auto indexes = _ui->dbPackageListView->selectionModel()->selectedIndexes();
	QList<QPersistentModelIndex> pIndexes;
	foreach(auto index, indexes)
		pIndexes.append(index);
	foreach(auto index, pIndexes)
		_dbModel->removeRow(index.row(), index.parent());
}

void EditPackagesDialog::on_clearAllButton_clicked()
{
	_ui->localPackageListView->clearSelection();
	_ui->dbPackageListView->clearSelection();
}
