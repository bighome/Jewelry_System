#include "jewelrypurchasingadd.h"
#include "WarehouseManager.h"
#include "WarehouseInfo.h"
#include "CommodityInfo.h"
#include "StaffManager.h"
#include "SupplierManager.h"
#include <QMessageBox>
#include "jewelrysupplierinformation.h"
#include "jewelrygoodsfiles.h"
#include "jewelurprintf.h"

jewelryPurchasingAdd::jewelryPurchasingAdd(QWidget* parent)
: QDialog(parent)
, m_id(0)
{
	ui.setupUi(this);
	init();
}

jewelryPurchasingAdd::jewelryPurchasingAdd(QWidget* parent , const PurchaseManager::PurchaseManagerItem& item)
: QDialog(parent)
{
	ui.setupUi(this);
	init();
	m_id = item.m_id;
	setWindowTitle(windowTitle() + QString(":采购编号").arg(m_id));
	updateUIFromData();
}

jewelryPurchasingAdd::~jewelryPurchasingAdd()
{

}

void jewelryPurchasingAdd::init()
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
	warehouseManager.updateFromDatabase();
	QMap<int , WarehouseInfo::WarehouseInfoItem>& warehouseInfoItemMap = warehouseInfo.getWarehouseInfoMap();
	for (QMap<int , WarehouseInfo::WarehouseInfoItem>::iterator i = warehouseInfoItemMap.begin() ; i != warehouseInfoItemMap.end() ; i++)
	{
		WarehouseInfo::WarehouseInfoItem& warehouseInfoItem = *i;
		ui.cbWarehouseName->addItem(warehouseInfoItem.m_warehouseInfo , warehouseInfoItem.m_id);
	}
	QMap<QString , CommodityInfo::CommodityInfoItem>& commodityInfoItemMap = commodityInfo.getCommodityInfoItemMap();
	for (QMap<QString , CommodityInfo::CommodityInfoItem>::iterator i = commodityInfoItemMap.begin() ; i != commodityInfoItemMap.end() ; i++)
	{
		CommodityInfo::CommodityInfoItem& item = *i;
		ui.cbCommodityName->addItem(item.m_commodityName , item.m_id);
	}
	QMap<int , StaffManager::StaffManagerItem>& staffManagerItemMap = staffManager.getStaffManagerItemMap();
	for (QMap<int , StaffManager::StaffManagerItem>::iterator i = staffManagerItemMap.begin() ; i != staffManagerItemMap.end() ; i++)
	{
		StaffManager::StaffManagerItem& item = *i;
		ui.cbPurchaseName->addItem(item.m_name , item.m_id);
	}
	QMap<int , SupplierManager::SupplierManagerItem>& supplierManagerItemMap = supplierManager.getSupplierManagerMap();
	for (QMap<int , SupplierManager::SupplierManagerItem>::iterator i = supplierManagerItemMap.begin() ; i != supplierManagerItemMap.end() ; i++)
	{
		SupplierManager::SupplierManagerItem& item = *i;
		ui.cbSupplierName->addItem(item.m_supplierName , item.m_id);
	}
}

void jewelryPurchasingAdd::updateUIFromData()
{
	PurchaseManager& purchaseManager = PurchaseManager::getInstance();
	PurchaseManager::PurchaseManagerItem item = purchaseManager.getPurchaseManagerItemByID(m_id);
	int index = ui.cbWarehouseName->findData(item.m_warehouseID);
	if (index >= 0)
	{
		ui.cbWarehouseName->setCurrentIndex(index);
	}
	index = ui.cbSupplierName->findData(item.m_supplierID);
	if (index >= 0)
	{
		ui.cbSupplierName->setCurrentIndex(index);
	}
	index = ui.cbPurchaseName->findData(item.m_staffID);
	if (index >= 0)
	{
		ui.cbPurchaseName->setCurrentIndex(item.m_staffID);
	}
	index = ui.cbCommodityName->findData(item.m_commodityID);
	if (index >= 0)
	{
		ui.cbCommodityName->setCurrentIndex(index);
	}
	ui.spCommodityCount->setValue(item.m_commodityCount);
	ui.dbCommodityPrice->setValue(item.m_commodityPrice);
}

void jewelryPurchasingAdd::updateDataFromUI(PurchaseManager::PurchaseManagerItem& item)
{
	item.m_supplierID = ui.cbSupplierName->itemData(ui.cbSupplierName->currentIndex()).toInt();
	item.m_commodityID = ui.cbCommodityName->itemData(ui.cbCommodityName->currentIndex()).toString();
	item.m_warehouseID = ui.cbWarehouseName->itemData(ui.cbWarehouseName->currentIndex()).toInt();
	item.m_staffID = ui.cbPurchaseName->itemData(ui.cbPurchaseName->currentIndex()).toInt();
	item.m_commodityCount = ui.spCommodityCount->value();
	item.m_commodityPrice = ui.dbCommodityPrice->value();
}


void jewelryPurchasingAdd::on_pbOK_clicked()
{
	bool b = false;
	if (m_id == 0)
	{
		b = insertNewItem();
	} 
	else
	{
		b = updateDatabaseFromUI();
	}
	if(b)
		accept();
}

void jewelryPurchasingAdd::on_pbCancel_clicked()
{
	reject();
}

bool jewelryPurchasingAdd::updateDatabaseFromUI()
{
	bool b = false;
	if (ui.spCommodityCount->value() == 0 || ui.dbCommodityPrice->value() < 1)
	{
		QMessageBox::information(this , tr("系统消息") , tr("数据不符合规范"));
		return b;
	}
	else
	{
		PurchaseManager& purchaseManager = PurchaseManager::getInstance();
		PurchaseManager::PurchaseManagerItem item;
		updateDataFromUI(item);
		item.m_id = m_id;
		if(purchaseManager.updateDatabase(item))
		{
			b = true;
			QMessageBox::information(this , tr("系统消息") , tr("添加采购数据完成"));
			jewelurPrintf::getInstance().setPrintCoad("" , 
				CommodityInfo::getInstance().getCommodityInfoItemByID(item.m_commodityID).m_certificateNumbers , item.m_commodityCount);
		}
	}
	return b;
}

bool jewelryPurchasingAdd::insertNewItem()
{
	bool b = false;
	if (ui.spCommodityCount->value() == 0 || ui.dbCommodityPrice->value() < 1)
	{
		return b;
	}
	else
	{
		PurchaseManager& purchaseManager = PurchaseManager::getInstance();
		PurchaseManager::PurchaseManagerItem item;
		updateDataFromUI(item);
		if(purchaseManager.insertNewItem(item))
		{
			b = true;
			QMessageBox::information(this , tr("系统消息") , tr("添加采购数据完成"));
			jewelurPrintf::getInstance().setPrintCoad("" , 
				CommodityInfo::getInstance().getCommodityInfoItemByID(item.m_commodityID).m_certificateNumbers , item.m_commodityCount);
		}
	}
	return b;
}


void jewelryPurchasingAdd::on_pbQuerySupplier_clicked()
{
	jewelrySupplierInformation info(this);
	info.exec();
}

void jewelryPurchasingAdd::on_pbCommodityName_clicked()
{
	jewelryGoodsFiles goods(this);
	goods.exec();
}

void jewelryPurchasingAdd::on_pbQueryWarehouse_clicked()
{

}

void jewelryPurchasingAdd::on_pbQueryStaff_clicked()
{

}