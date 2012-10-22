#ifndef JEWELRYMEMBERSHIPCARDNUMBER_H
#define JEWELRYMEMBERSHIPCARDNUMBER_H

#include <QDialog>
#include "ui_jewelryVIPManagerDialog.h"
#include "VIPManager.h"

class jewelryVIPManagerDialog : public QDialog
{
	Q_OBJECT
	enum TABLEITEM
	{
		TABLEITEM_id,
		TABLEITEM_name,
		TABLEITEM_gender,
		TABLEITEM_paperworkID,
		TABLEITEM_phone,
		TABLEITEM_address,
		TABLEITEM_cardType,
		TABLEITEM_consumptionSum,
		TABLEITEM_integration,
		TABLEITEM_createDatetime
	};
public:
	jewelryVIPManagerDialog(QWidget *parent = 0);
	~jewelryVIPManagerDialog();
	VIPManager::VIPManagerItem getCurrentVIPItem();

private slots:
	void on_pbDelete_clicked();
	void on_pbQuit_clicked();
	void on_pbEdit_clicked();
	void on_pbAdd_clicked();

private:
	void updateUIFromData();
	void setTableWidgetItem(int row , VIPManager::VIPManagerItem& item);

private:
	Ui::jewelryVIPManagerDialogClass ui;
	//VIPManager& m_vipManager;
	VIPManager::VIPManagerItem m_currentVIPItem;
};

#endif // JEWELRYMEMBERSHIPCARDNUMBER_H
