#ifndef JEWELRYMAINWINDOW_H
#define JEWELRYMAINWINDOW_H

#include <QMainWindow>
#include "ui_jewelrymainwindow.h"
#include <QPaintEvent>


class jewelryPurchasing;
class jewelryInventory;
class jewelrySales;
class jewelryLogin;
class jewelrySystemSetting;
class jewelryGoodsFiles;
class jewelryVIPManagerDialog;
class jewelrySupplierInformation;
class jewelryWarehouseInformation;
class jewelryCodeSettings;
class jewelryWarehouseManager;
class SqlQuery;
class jewelryUpdate;
class jewelryMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	jewelryMainWindow(QWidget *parent = 0);
	~jewelryMainWindow();

private:
	void init();
	void paintEvent (QPaintEvent *event );
	void setPermissions();

public slots:
	//mainwindow
	void slotsCyywBTN();
	void slotsCgjhBTN();
	void slotsSpxsBTN();
	void slotsKcglBTN();
	void slotsXtgjBTN();
	void slotsCloseSystem();
	void slotsSpdaBTN();
	void slotsHyxxBTN();
	void slotsGysxxBTN();
	void slotsCkxxBTN();
	void slotsCkxxBTN_1();
	void slotsHideBTN();
	void slotsCloseBTN();

	//stackendwidget
	void slotsCgjhBTN_1();
	void slotsCgjhBTN_2();
	void slotsKcglBTN_1();
	void slotsPdBTN();
	void slotsQtxsBTN();
	void slotsQtxsBTN_1();
	void slotsXtszBTN();
	void slotsLoginBTN();
	void slotsPrintLableBTN();

signals:
	void closeqApp();
//private:
//	jewelryPurchasing* m_purchasing;
//	//jewelryInventory* m_invetory;
//	jewelrySales* m_sales;
//	jewelryLogin* m_login;
//	jewelrySystemSetting* m_systemSetting;
//	jewelryGoodsFiles* m_goodsFiles;
//	jewelryVIPManagerDialog* m_memberShipInformation;
//	jewelrySupplierInformation* m_supplierInformation;
//	jewelryWarehouseInformation* m_warehouseInformation;
//	jewelryCodeSettings* m_codeSettings;
//	jewelryWarehouseManager* m_warehouseManager;
private:
	Ui::jewelryMainWindowClass ui;

private slots:
  void on_update_clicked();
	void on_settingsBTN_clicked();
};

#endif // JEWELRYMAINWINDOW_H
