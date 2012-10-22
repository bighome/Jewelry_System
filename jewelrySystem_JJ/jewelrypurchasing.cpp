#include "jewelrypurchasing.h"
#include "jewelrysupplierinformation.h"
#include "WarehouseManager.h"
#include "WarehouseInfo.h"
#include "PurchaseManager.h"
#include "CommodityInfo.h"
#include "StaffManager.h"
#include <QMessageBox>
#include "jewelrypurchasingadd.h"
#include "jewelrypurchasingaddexcel.h"

jewelryPurchasing::jewelryPurchasing(QWidget *parent)
	: QDialog()
	, m_supplierInfo(NULL)
{
	ui.setupUi(this);
	//wondows TOP

#ifdef NDEBUG 
	this->setWindowFlags(Qt::WindowStaysOnTopHint);
#endif
	setWindowState(Qt::WindowFullScreen);
	updateUIFromDatabase();
}

jewelryPurchasing::~jewelryPurchasing()
{

}


void jewelryPurchasing::on_pbAdd_clicked()
{
	jewelryPurchasingAdd add(this);
	if (add.exec())
	{
		updateUIFromDatabase();
	}
}

void jewelryPurchasing::on_pbEdit_clicked()
{
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		PurchaseManager::PurchaseManagerItem item;
		item.m_id = ui.tableWidget->item(row , TABLEITEM_ID)->text().toInt();
		jewelryPurchasingAdd add(this , item);
		if (add.exec())
		{
			updateUIFromDatabase();
		}
	}
}

void jewelryPurchasing::on_pbQuery_clicked()
{
	if (m_supplierInfo == NULL)
	{
		m_supplierInfo = new jewelrySupplierInformation(this);
	}
	if(m_supplierInfo->exec())
	{
		SupplierManager::SupplierManagerItem item = m_supplierInfo->getCurrentSupplierManagerItem();
	}
}

void jewelryPurchasing::updateUIFromDatabase()
{
	WarehouseInfo& warehouseInfo = WarehouseInfo::getInstance();
	warehouseInfo.updateDataFromDatabase();
	PurchaseManager& purchaseManager = PurchaseManager::getInstance();
	purchaseManager.updateDataFromDatabase();
	CommodityInfo& commodityInfo = CommodityInfo::getInstance();
	commodityInfo.updateDataFromDatabase();
	StaffManager& staffManager = StaffManager::getInstance();
	staffManager.updateDatabase();
	SupplierManager& supplierManager = SupplierManager::getInstance();
	supplierManager.updateDataFromDatabase();
	WarehouseManager& warehouseManager = WarehouseManager::getInstance();

	QMap<int , PurchaseManager::PurchaseManagerItem>& purchaseManagerItemMap = purchaseManager.getPurchaseManagerItemMap();
	ui.tableWidget->setRowCount(purchaseManagerItemMap.count());
	int row = 0;
	for (QMap<int , PurchaseManager::PurchaseManagerItem>::iterator i = purchaseManagerItemMap.begin() ; i != purchaseManagerItemMap.end() ; i++ , row++)
	{
		PurchaseManager::PurchaseManagerItem& purchaseManagerItem  = *i;
		CommodityInfo::CommodityInfoItem commodityInfoItem = commodityInfo.getCommodityInfoItemByID(purchaseManagerItem.m_commodityID);
		StaffManager::StaffManagerItem staffManagerItem = staffManager.getStaffManagerItemByID(purchaseManagerItem.m_staffID);
		SupplierManager::SupplierManagerItem supplierManagerItem = supplierManager.getSupplierManagerItemByID(purchaseManagerItem.m_supplierID);
		WarehouseManager::WarehouseManagerItem warehouseManagerItem = warehouseManager.getWarehouseManagerItem(purchaseManagerItem.m_staffID , purchaseManagerItem.m_commodityID);
		QTableWidgetItem* tableItem = NULL;
		{
			tableItem = new QTableWidgetItem(QString::number(purchaseManagerItem.m_id));
			ui.tableWidget->setItem(row , TABLEITEM_ID , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(QString::number(supplierManagerItem.m_id));
			ui.tableWidget->setItem(row , TABLEITEM_supplierID , tableItem);
		}
		{
			tableItem = new QTableWidgetItem((supplierManagerItem.m_supplierName));
			ui.tableWidget->setItem(row , TABLEITEM_supplierName , tableItem);
		}
		{
			tableItem = new QTableWidgetItem((staffManagerItem.m_name));
			ui.tableWidget->setItem(row , TABLEITEM_purchaserName , tableItem);
		}
		{
			tableItem = new QTableWidgetItem((commodityInfoItem.m_id));
			ui.tableWidget->setItem(row , TABLEITEM_commodityBarcode , tableItem);
		}
		{
			tableItem = new QTableWidgetItem((commodityInfoItem.m_commodityName));
			ui.tableWidget->setItem(row , TABLEITEM_commodityName , tableItem);
		}
		{
			tableItem = new QTableWidgetItem((commodityInfoItem.m_commodityType));
			ui.tableWidget->setItem(row , TABLEITEM_commodityType , tableItem);
		}
		{
			tableItem = new QTableWidgetItem((commodityInfoItem.m_commodityUnit));
			ui.tableWidget->setItem(row , TABLEITEM_commodityUnit , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(QString::number(purchaseManagerItem.m_commodityPrice , 'f' , 4));
			ui.tableWidget->setItem(row , TABLEITEM_commodityPrice , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(QString::number(purchaseManagerItem.m_commodityCount));
			ui.tableWidget->setItem(row , TABLEITEM_stockCount , tableItem);
		}
		{
			tableItem = new QTableWidgetItem((commodityInfoItem.m_mark));
			ui.tableWidget->setItem(row , TABLEITEM_commodityMark , tableItem);
		}
	}
}

void jewelryPurchasing::on_pbCommodityName_clicked()
{
}

void jewelryPurchasing::on_pbQueryWarehouse_clicked()
{

}

void jewelryPurchasing::on_pbQueryStaff_clicked()
{

}

void jewelryPurchasing::on_pbQuit_clicked()
{
	close();
}

void jewelryPurchasing::on_pbAdd_EXCEL_clicked()
{
	jewelryPurchasingAddExcel adds(this);
  if (adds.exec())
  {
    updateUIFromDatabase();
  }
}