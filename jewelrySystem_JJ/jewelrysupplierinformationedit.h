#ifndef JEWELRYSUPPLIERINFORMATIONEDIT_H
#define JEWELRYSUPPLIERINFORMATIONEDIT_H

#include <QDialog>
#include "ui_jewelrysupplierinformationedit.h"
#include "SupplierManager.h"

class jewelrySupplierInformationEdit : public QDialog
{
	Q_OBJECT

public:
	jewelrySupplierInformationEdit(QWidget* parent);
	jewelrySupplierInformationEdit(QWidget* parent , const SupplierManager::SupplierManagerItem& item);
	~jewelrySupplierInformationEdit();

	void updateUIFromData(const SupplierManager::SupplierManagerItem& item);

private:
	void updateDataFromUI(SupplierManager::SupplierManagerItem& item);

private:
	Ui::jewelrySupplierInformationEditClass ui;
	bool m_update;
	int m_id;

private slots:
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
};

#endif // JEWELRYSUPPLIERINFORMATIONEDIT_H
