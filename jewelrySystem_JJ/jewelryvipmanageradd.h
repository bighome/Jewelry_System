#ifndef JEWELRYVIPMANAGERADD_H
#define JEWELRYVIPMANAGERADD_H

#include <QDialog>
#include "ui_jewelryvipmanageradd.h"
#include <VIPManager.h>

class jewelryVIPManagerAdd : public QDialog
{
	Q_OBJECT

public:
	jewelryVIPManagerAdd(QWidget *parent = 0);
	jewelryVIPManagerAdd(int vipID , QWidget *parent = 0);
	~jewelryVIPManagerAdd();
	VIPManager::VIPManagerItem getVIPManagerItem();

private:
	void updateDataFromUI();
	void updateUIFromData(const VIPManager::VIPManagerItem& managerItem);

private:
	Ui::jewelryVIPManagerAddClass ui;

private slots:
	void on_pbCancel_clicked();
	void on_pbOK_clicked();

private:
	VIPManager::VIPManagerItem m_VIPManagerItem;
	int m_vipID;
};

#endif // JEWELRYVIPMANAGERADD_H
