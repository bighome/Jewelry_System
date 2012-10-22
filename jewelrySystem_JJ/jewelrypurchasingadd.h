#ifndef JEWELRYPURCHASINGADD_H
#define JEWELRYPURCHASINGADD_H

#include <QDialog>
#include "ui_jewelrypurchasingadd.h"
#include "PurchaseManager.h"

class jewelryPurchasingAdd : public QDialog
{
	Q_OBJECT

public:
	jewelryPurchasingAdd(QWidget* parent);
	jewelryPurchasingAdd(QWidget* parent , const PurchaseManager::PurchaseManagerItem& item);
	~jewelryPurchasingAdd();

private:
	void init();
	void updateUIFromData();
	void updateDataFromUI(PurchaseManager::PurchaseManagerItem& item);
	bool updateDatabaseFromUI();
	bool insertNewItem();

private:
	Ui::jewelryPurchasingAddClass ui;
	int m_id;

private slots:
	void on_pbQueryStaff_clicked();
	void on_pbQueryWarehouse_clicked();
	void on_pbCommodityName_clicked();
	void on_pbQuerySupplier_clicked();
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
};

#endif // JEWELRYPURCHASINGADD_H
