#include "jewelrywarehouseinformation.h"
#include "WarehouseInfo.h"
#include "WarehouseManager.h"
#include "CommodityInfo.h"
#include "jewelrywarehouseadd.h"
#include <QMessageBox>

jewelryWarehouseInformation::jewelryWarehouseInformation(QWidget *parent)
	: QDialog()
{
	ui.setupUi(this);
//#ifdef NDEBUG 
//	this->setWindowFlags(Qt::WindowStaysOnTopHint);
//#endif
//	setWindowState(Qt::WindowFullScreen);
	updateUIfromDatabase();
}

jewelryWarehouseInformation::~jewelryWarehouseInformation()
{

}

void jewelryWarehouseInformation::updateUIfromDatabase()
{
	WarehouseManager& warehouseManager = WarehouseManager::getInstance();
	warehouseManager.updateFromDatabase();
	WarehouseInfo& warehouseInfo = WarehouseInfo::getInstance();
	warehouseInfo.updateDataFromDatabase();
	CommodityInfo& commodityInfo = CommodityInfo::getInstance();
	commodityInfo.updateDataFromDatabase();

	QMap<int , WarehouseInfo::WarehouseInfoItem>& warehouseInfoItemMap = warehouseInfo.getWarehouseInfoMap();
	int row = 0;
	ui.tableWidget->setRowCount(warehouseInfoItemMap.count());
	for (QMap<int , WarehouseInfo::WarehouseInfoItem>::iterator i = warehouseInfoItemMap.begin() ; i != warehouseInfoItemMap.end() ; i++ , row++)
	{
		const WarehouseInfo::WarehouseInfoItem& warehouseInfoItem = *i;
		QTableWidgetItem* tableItem = NULL;
		{
			tableItem = new QTableWidgetItem(QString::number(warehouseInfoItem.m_id));
			ui.tableWidget->setItem(row , TABLEITEM_ID , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(warehouseInfoItem.m_warehouseInfo);
			ui.tableWidget->setItem(row , TABLEITEM_NAME , tableItem);
		}
	}

	//QList<WarehouseManager::WarehouseManagerItem>& warehouseManagerItemList = warehouseManager.getWarehouseManagerItemList();
	//int row = 0;
	//ui.tableWidget->setRowCount(warehouseManagerItemList.count());
	//for (QList<WarehouseManager::WarehouseManagerItem>::iterator i = warehouseManagerItemList.begin() ;
	//	i != warehouseManagerItemList.end() ; i++ , row++)
	//{
	//	WarehouseManager::WarehouseManagerItem& warehouseManagerItem = *i;
	//	QTableWidgetItem* tableItem = NULL;
	//	CommodityInfo::CommodityInfoItem commodityInfoItem = commodityInfo.getCommodityInfoItemByID(warehouseManagerItem.m_commodityID);
	//	{
	//		tableItem = new QTableWidgetItem(QString::number(warehouseManagerItem.m_id));
	//		ui.tableWidget->setItem(row , TABLEITEM_ID , tableItem);
	//	}
	//	{
	//		WarehouseInfo::WarehouseInfoItem item = warehouseInfo.getWarehouseInfoItemByID(warehouseManagerItem.m_id);
	//		tableItem = new QTableWidgetItem(item.m_warehouseInfo);
	//		ui.tableWidget->setItem(row , TABLEITEM_NAME , tableItem);
	//	}
	//}
}

void jewelryWarehouseInformation::on_pbAddWarehouse_clicked()
{
	jewelryWarehouseAdd add(this);
	if (add.exec())
	{
		updateUIfromDatabase();
	}
}

void jewelryWarehouseInformation::on_pbEditWarehouseInfo_clicked()
{
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		WarehouseInfo::WarehouseInfoItem item;
		item.m_id = ui.tableWidget->item(row , TABLEITEM_ID)->text().toInt();
		item.m_warehouseInfo = ui.tableWidget->item(row , TABLEITEM_NAME)->text();
		jewelryWarehouseAdd add(this , item);
		if (add.exec())
		{
			updateUIfromDatabase();
		}
	}
	else
	{
		QMessageBox::information(this , tr("系统消息") , tr("未选中需要修改条目"));
	}
}

void jewelryWarehouseInformation::on_pbQuit_clicked()
{
	close();
}

void jewelryWarehouseInformation::on_pbDelete_clicked()
{
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		WarehouseInfo& warehouseInfo = WarehouseInfo::getInstance();
		int id = ui.tableWidget->item(row , TABLEITEM_ID)->text().toInt();
		if(warehouseInfo.deleteItem(id))
			updateUIfromDatabase();
	}
}