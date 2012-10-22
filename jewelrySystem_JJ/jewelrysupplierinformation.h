#ifndef JEWELRYSUPPLIERINFORMATION_H
#define JEWELRYSUPPLIERINFORMATION_H

#include <QDialog>
#include "ui_jewelrysupplierinformation.h"
#include <QString>
#include <QMap>
#include "SupplierManager.h"

class jewelrySupplierInformation : public QDialog
{
	Q_OBJECT
	enum TABLEITEM
	{
		TABLEITEM_id,
		TABLEITEM_supplierName,
		TABLEITEM_contactor,
		TABLEITEM_phone,
		TABLEITEM_mobilePone,
		TABLEITEM_fax,
		TABLEITEM_email,
		TABLEITEM_address,
		TABLEITEM_zipCode
	};
public:
	jewelrySupplierInformation(QWidget *parent);
	~jewelrySupplierInformation();
	SupplierManager::SupplierManagerItem getCurrentSupplierManagerItem();

private:
	void updateUIFromDatabase();

private:
	Ui::jewelrySupplierInformationClass ui;
	int m_id;

private slots:
	void on_pbQuit_clicked();
	void on_pbEdit_clicked();
	void on_pbAdd_clicked();
};

#endif // JEWELRYSUPPLIERINFORMATION_H
