#ifndef JEWELRYSTAFFMANAGER_H
#define JEWELRYSTAFFMANAGER_H

#include <QDialog>
#include "ui_jewelrystaffmanager.h"
#include "StaffManager.h"


class jewelryStaffManager : public QDialog
{
	Q_OBJECT

	enum TABLEITEM
	{
		TABLEITEM_id,
		TABLEITEM_name,
		TABLEITEM_gender,
		TABLEITEM_paperworkID,
		TABLEITEM_fromDate,
		TABLEITEM_post,
		TABLEITEM_warehouse
	};
public:
	jewelryStaffManager(QWidget *parent = 0);
	~jewelryStaffManager();

private:
	Ui::jewelryStaffManagerClass ui;

private:
	void updateUIFromData();
	void setTableItem(int row , const StaffManager::StaffManagerItem& item);

private slots:
	void on_pbQuit_clicked();
	void on_pbDelete_clicked();
	void on_pbEdit_clicked();
	void on_pbAdd_clicked();
};

#endif // JEWELRYSTAFFMANAGER_H
