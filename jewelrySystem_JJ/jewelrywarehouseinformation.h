#ifndef JEWELRYWAREHOUSEINFORMATION_H
#define JEWELRYWAREHOUSEINFORMATION_H

#include <QDialog>
#include "ui_jewelrywarehouseinformation.h"

class jewelryWarehouseInformation : public QDialog
{
	Q_OBJECT
	enum TABLEITEM
	{
		TABLEITEM_ID,
		TABLEITEM_NAME
	};
public:
	jewelryWarehouseInformation(QWidget *parent);
	~jewelryWarehouseInformation();

private:
	void updateUIfromDatabase();

private:
	Ui::jewelryWarehouseInformationClass ui;

private slots:
	void on_pbDelete_clicked();
	void on_pbQuit_clicked();
	void on_pbEditWarehouseInfo_clicked();
	void on_pbAddWarehouse_clicked();
};

#endif // JEWELRYWAREHOUSEINFORMATION_H
