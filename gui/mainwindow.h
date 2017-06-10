#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QCheckBox>
#include <QStringListModel>
#include "packagemanagerplugin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
	Q_OBJECT

public:
	explicit MainWindow(PackageManagerPlugin *plugin, QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void reloadPackages();

	void on_addButton_clicked();
	void on_removeButton_clicked();
	void on_clearAllButton_clicked();

private:
	Ui::MainWindow *_ui;
	PackageManagerPlugin *_plugin;
	QList<QCheckBox*> _boxes;

	QStringListModel *_pkgModel;

	void setupFilters();
};

#endif // MAINWINDOW_H
