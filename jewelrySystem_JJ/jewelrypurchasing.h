//²É¹º½ø»õ

#ifndef JEWELRYPURCHASING_H
#define JEWELRYPURCHASING_H

#include <QDialog>
#include "ui_jewelrypurchasing.h"

class jewelrySupplierInformation;

class jewelryPurchasing : public QDialog
{
	Q_OBJECT
	enum TABLEITEM
	{
		TABLEITEM_ID,
		TABLEITEM_supplierID,
		TABLEITEM_supplierName,
		TABLEITEM_purchaserName,
		TABLEITEM_commodityBarcode,
		TABLEITEM_commodityName,
		TABLEITEM_commodityType,
		TABLEITEM_commodityUnit,
		TABLEITEM_stockCount,
		TABLEITEM_commodityPrice,
		TABLEITEM_commodityMark
	};
public:
	jewelryPurchasing(QWidget *parent);
	~jewelryPurchasing();

private:
	void updateUIFromDatabase();

private:
	Ui::jewelryPurchasingClass ui;
	jewelrySupplierInformation* m_supplierInfo;

private slots:
	void on_pbAdd_EXCEL_clicked();
	void on_pbQuit_clicked();
	void on_pbQueryStaff_clicked();
	void on_pbQueryWarehouse_clicked();
	void on_pbCommodityName_clicked();
	void on_pbQuery_clicked();
	void on_pbEdit_clicked();
	void on_pbAdd_clicked();
};

#endif // JEWELRYPURCHASING_H
