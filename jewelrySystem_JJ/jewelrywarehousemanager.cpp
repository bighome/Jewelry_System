#include "jewelrywarehousemanager.h"
#include "SystemSettings.h"
#include "StaffManager.h"
#include "WarehouseManager.h"
#include "WarehouseInfo.h"
#include "CommodityInfo.h"

jewelryWarehouseManager::jewelryWarehouseManager(QWidget *parent)
	: QDialog()
{
	ui.setupUi(this);
	updateUIFromDatabase();
}

jewelryWarehouseManager::~jewelryWarehouseManager()
{

}

void jewelryWarehouseManager::updateUIFromDatabase()
{
	ui.cbWarehouse->clear();
	WarehouseManager& warehouseManager = WarehouseManager::getInstance();
	WarehouseInfo& warehouseInfo = WarehouseInfo::getInstance();
	QMap<int , WarehouseInfo::WarehouseInfoItem>& warehouseInfoItemMap = warehouseInfo.getWarehouseInfoMap();
	for (QMap<int , WarehouseInfo::WarehouseInfoItem>::iterator i = warehouseInfoItemMap.begin() ; 
		i != warehouseInfoItemMap.end() ; i++)
	{
		const WarehouseInfo::WarehouseInfoItem& warehouseInfoItem = *i;
		//WarehouseInfo::WarehouseInfoItem warehouseInfoItem = warehouseInfo.getWarehouseInfoItemByID(warehouseManagerItem.m_id);
		ui.cbWarehouse->addItem(warehouseInfoItem.m_warehouseInfo , warehouseInfoItem.m_id);
	}
	StaffManager& staffManager = StaffManager::getInstance();
	SystemSettings& systemSettings = SystemSettings::getInstance();
	StaffManager::StaffManagerItem staffManagerItem = staffManager.getStaffManagerItemByID(systemSettings.getCurrentStaffID());
	m_warehouseID = staffManagerItem.m_warehouseID;
	int index = ui.cbWarehouse->findData(m_warehouseID);
	if (index >= 0)
	{
		ui.cbWarehouse->setCurrentIndex(index);
	}
	//updateTableWidget();
}

void jewelryWarehouseManager::updateTableWidget()
{
	WarehouseManager& warehouseManager = WarehouseManager::getInstance();
	WarehouseInfo& warehouseInfo = WarehouseInfo::getInstance();
	CommodityInfo& commodityInfo = CommodityInfo::getInstance();

	int row = 0;
	ui.tableWidget->setRowCount(0);
	QList<WarehouseManager::WarehouseManagerItem>& warehouseManagerItemList = warehouseManager.getWarehouseManagerItemList();
	for (QList<WarehouseManager::WarehouseManagerItem>::iterator i = warehouseManagerItemList.begin() ; 
		i != warehouseManagerItemList.end() ; i++ , row++)
	{
		const WarehouseManager::WarehouseManagerItem& warehouseManagerItem = *i;
		if (warehouseManagerItem.m_id == m_warehouseID)
		{
			ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);
			WarehouseInfo::WarehouseInfoItem warehouseInfoItem = warehouseInfo.getWarehouseInfoItemByID(warehouseManagerItem.m_id);
			CommodityInfo::CommodityInfoItem commodityInfoItem = commodityInfo.getCommodityInfoItemByID(warehouseManagerItem.m_commodityID);
			QTableWidgetItem* item = NULL;
			{
				item = new QTableWidgetItem(QString::number(warehouseManagerItem.m_id));
				ui.tableWidget->setItem(row , TABLEITEM_warehouseID , item);
			}
			{
				item = new QTableWidgetItem(warehouseInfoItem.m_warehouseInfo);
				ui.tableWidget->setItem(row , TABLEITEM_warehouseName , item);
			}
			{
				item = new QTableWidgetItem(commodityInfoItem.m_id);
				ui.tableWidget->setItem(row , TABLEITEM_commodityID , item);
			}
			{
				item = new QTableWidgetItem(commodityInfoItem.m_commodityType);
				ui.tableWidget->setItem(row , TABLEITEM_commodityType , item);
			}
			{
				item = new QTableWidgetItem(commodityInfoItem.m_commodityName);
				ui.tableWidget->setItem(row , TABLEITEM_commodityName , item);
			}
			{
				item = new QTableWidgetItem(QString::number(commodityInfoItem.m_commodityPrice , 'f' , 4));
				ui.tableWidget->setItem(row , TABLEITEM_commodityPrice , item);
			}
			{
				item = new QTableWidgetItem(QString::number(commodityInfoItem.m_commodityDiscounts , 'f' , 4));
				ui.tableWidget->setItem(row , TABLEITEM_commodityDiscounts , item);
			}
			{
				item = new QTableWidgetItem((commodityInfoItem.m_commodityUnit));
				ui.tableWidget->setItem(row , TABLEITEM_commodityUnit , item);
			}
			{
				item = new QTableWidgetItem(QString::number(warehouseManagerItem.m_commodityCount));
				ui.tableWidget->setItem(row , TABLEITEM_stockNum , item);
			}
		}
	}
}

void jewelryWarehouseManager::on_pbSure_clicked()
{
	accept();
}

void jewelryWarehouseManager::on_cbWarehouse_currentIndexChanged(int index)
{
	m_warehouseID = ui.cbWarehouse->itemData(index).toInt();
	updateTableWidget();
}