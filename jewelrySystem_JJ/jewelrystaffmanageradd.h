#ifndef JEWELRYSTAFFMANAGERADD_H
#define JEWELRYSTAFFMANAGERADD_H

#include <QDialog>
#include "ui_jewelrystaffmanageradd.h"
#include "StaffManager.h"

class jewelryStaffManagerAdd : public QDialog
{
	Q_OBJECT

public:
	jewelryStaffManagerAdd(QWidget *parent = 0);
	jewelryStaffManagerAdd(int id , QWidget *parent = 0);
	~jewelryStaffManagerAdd();
	StaffManager::StaffManagerItem getStaffManagerItem();

private:
	Ui::jewelryStaffManagerAddClass ui;
	StaffManager::StaffManagerItem m_staffManagerItem;
	int m_id;

private:
	void init();
	void updateUIFromData();
	void updateDataFromUI();

private slots:
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
	void on_cbWarehouse_currentIndexChanged(int);
};

#endif // JEWELRYSTAFFMANAGERADD_H
