#ifndef JEWELRYWAREHOUSEADD_H
#define JEWELRYWAREHOUSEADD_H

#include <QDialog>
#include "ui_jewelrywarehouseadd.h"
#include "WarehouseInfo.h"

class jewelryWarehouseAdd : public QDialog
{
	Q_OBJECT

public:
	jewelryWarehouseAdd(QWidget *parent);
	jewelryWarehouseAdd(QWidget *parent , const WarehouseInfo::WarehouseInfoItem& item);
	~jewelryWarehouseAdd();

private:
	Ui::jewelryWarehouseAddClass ui;

private slots:
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
};

#endif // JEWELRYWAREHOUSEADD_H
