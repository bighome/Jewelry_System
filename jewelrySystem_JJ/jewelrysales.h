#ifndef JEWELRYSALES_H
#define JEWELRYSALES_H

#include <QDialog>
#include "ui_jewelrysales.h"
#include <QKeyEvent>
#include <QList>
#include <QMessageBox>
#include "CommodityInfo.h"
#include "WarehouseManager.h"
#include "StaffManager.h"
#include "SaleManager.h"

class jewelrySingleProductDiscount;
class jewelryTradeDiscount;
class jewelryChangeUnitPrice;
class jewelryCommodityInquires;
class jewelryVIPManagerDialog;
class jewelrySettlement;
class jewelryTradingPopup;
class jewelryWholeAmount;
class jewelryLogin;
class jewelryGoodsFiles;


class jewelrySales : public QDialog
{
	Q_OBJECT

	enum TABLEHEADER
	{
		TABLEHEADER_ID = 0,
		TABLEHEADER_CERTIFICATEID,
		TABLEHEADER_UNIT,
		TABLEHEADER_NAME,
		TABLEHEADER_TYPE,
		TABLEHEADER_PRICE,
		TABLEHEADER_GEMPRICE,
		TABLEHEADER_JOBPRICE,
		TABLEHEADER_ROUNDNUMBERS,
		TABLEHEADER_MAINGEMKARAT,
		TABLEHEADER_ASSISTANTGEMKARAT,
		TABLEHEADER_GRADE,
		TABLEHEADER_COLOR,
		TABLEHEADER_GOLDWEIGHT,
		TABLEHEADER_GROSSWEIGHT,
		TABLEHEADER_COUNT,
		TABLEHEADER_DISCOUNTS,
		TABLEHEADER_AMOUNT,
		TABLEHEADER_STOCKNUM
	};

public:
  jewelrySales(QWidget *parent);
	~jewelrySales();

private:
	void keyPressEvent(QKeyEvent *e);
	void init();

private:
	jewelrySingleProductDiscount* m_singleProductDiscount;
	jewelryTradeDiscount* m_tradeDiscount;
	jewelryChangeUnitPrice* m_changeUnitPrice;
	jewelryCommodityInquires* m_commodityInquires;
	jewelryVIPManagerDialog* m_VIPManagerDialog;
	jewelrySettlement* m_settlement;
	jewelryTradingPopup* m_tradingPopup;
	jewelryWholeAmount* m_wholeAmount;
	jewelryLogin* m_login;
  jewelryGoodsFiles* m_goodsGiles;

  static bool s_tableWidgetBool;
  static int s_tableWidgetItemRows;
 static QTableWidgetItem* m_tableWidgetItem;


public slots:
	void slotScanningBarcode(QString barcodeID);//扫描条码
	void slotswholeAmount();
	void slotsLogin();

	void slotleBarcodeReturnPressed();
	void slotlePaidUpReturnPressed();
	void slotlePaidUpTextChanged(const QString&);
  void slotleClose();
  void slotsTableWidgetItem(QTableWidgetItem *);

protected:
	void showEvent(QShowEvent *event);

private:
	void addNewCommudity(const CommodityInfo::CommodityInfoItem& item);
	void calculateAmountMoney();
	void clearAll();

	void updateSalersInfo();
	void updateWarehouseInfo();
	void completionTransaction();
  //单品折扣
  void oneDiscount(int row);
  //更改单价
  void modifyPrice(int row);

	SaleManager::SaleItem updateDataFromUI();

private:
	Ui::jewelrySalesClass ui;
	//WarehouseManager m_warehouseManager;
	SaleManager m_saleManager;
	VIPManager::VIPManagerItem m_vipManagerItem;
	//SaleManager::SaleItem m_currentSaleItem;

private slots:
  void on_pushButton_15_clicked();
	void on_tableWidget_clicked(const QModelIndex &);
};

#endif // JEWELRYSALES_H
