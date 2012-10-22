#ifndef JEWELRYWAREHOUSEMANAGER_H
#define JEWELRYWAREHOUSEMANAGER_H

#include <QDialog>
#include "ui_jewelrywarehousemanager.h"

class jewelryWarehouseManager : public QDialog
{
	Q_OBJECT
	enum TABLEITEM
	{
		TABLEITEM_warehouseID,
		TABLEITEM_warehouseName,
		TABLEITEM_commodityID,
		TABLEITEM_commodityType,
		TABLEITEM_commodityName,
		TABLEITEM_commodityPrice,
		TABLEITEM_commodityDiscounts,
		TABLEITEM_commodityUnit,
		TABLEITEM_stockNum
	};

public:
	jewelryWarehouseManager(QWidget *parent);
	~jewelryWarehouseManager();

private:
	void updateUIFromDatabase();
	void updateTableWidget();

private:
	Ui::jewelryWarehouseManagerClass ui;
	int m_warehouseID;

private slots:
	void on_cbWarehouse_currentIndexChanged(int);
	void on_pbSure_clicked();
};

#endif // JEWELRYWAREHOUSEMANAGER_H
