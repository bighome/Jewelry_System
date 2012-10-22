#include "jewelrystaffmanager.h"
#include "jewelrystaffmanageradd.h"
#include "WarehouseInfo.h"

jewelryStaffManager::jewelryStaffManager(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	updateUIFromData();
}

jewelryStaffManager::~jewelryStaffManager()
{

}

void jewelryStaffManager::updateUIFromData()
{
	StaffManager& staffManager = StaffManager::getInstance();
	QMap<int , StaffManager::StaffManagerItem>& staffManagerItemMap= staffManager.getStaffManagerItemMap();
	ui.tableWidget->setRowCount(staffManagerItemMap.count());
	int row = 0;
	for (QMap<int , StaffManager::StaffManagerItem>::iterator i = staffManagerItemMap.begin() ;
		i != staffManagerItemMap.end() ; i++ , row++)
	{
		StaffManager::StaffManagerItem& staffManagerItem = *i;
		setTableItem(row , staffManagerItem);
	}
}

void jewelryStaffManager::setTableItem(int row , const StaffManager::StaffManagerItem& staffManagerItem)
{
	QTableWidgetItem* item = NULL;
	{
		item = new QTableWidgetItem(QString::number(staffManagerItem.m_id));
		ui.tableWidget->setItem(row , TABLEITEM_id , item);
	}
	{
		item = new QTableWidgetItem(staffManagerItem.m_name);
		ui.tableWidget->setItem(row , TABLEITEM_name , item);
	}
	{
		QString str = tr("Å®");
		if (staffManagerItem.m_gender)
		{
			str = tr("ÄÐ");
		}
		item = new QTableWidgetItem(str);
		ui.tableWidget->setItem(row , TABLEITEM_gender , item);
	}
	{
		item = new QTableWidgetItem(staffManagerItem.m_paperworkid);
		ui.tableWidget->setItem(row , TABLEITEM_paperworkID , item);
	}
	{
		item = new QTableWidgetItem(staffManagerItem.m_fromDate.toString());
		ui.tableWidget->setItem(row , TABLEITEM_fromDate , item);
	}
	{
		item = new QTableWidgetItem(staffManagerItem.m_post);
		ui.tableWidget->setItem(row , TABLEITEM_post , item);
	}
	{
		WarehouseInfo& info = WarehouseInfo::getInstance();
		WarehouseInfo::WarehouseInfoItem warehouseInfoItem = info.getWarehouseInfoItemByID(staffManagerItem.m_warehouseID);
		item = new QTableWidgetItem(warehouseInfoItem.m_warehouseInfo);
		ui.tableWidget->setItem(row , TABLEITEM_warehouse , item);
	}
}


void jewelryStaffManager::on_pbAdd_clicked()
{
	jewelryStaffManagerAdd add;
	if (add.exec())
	{
		updateUIFromData();
	}
}

void jewelryStaffManager::on_pbEdit_clicked()
{
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		jewelryStaffManagerAdd add(ui.tableWidget->item(row , TABLEITEM_id)->text().toInt());
		if (add.exec())
		{
			updateUIFromData();
		}
	}
}

void jewelryStaffManager::on_pbDelete_clicked()
{
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		StaffManager::getInstance().deleteItem(ui.tableWidget->item(row , TABLEITEM_id)->text().toInt());
	}
}

void jewelryStaffManager::on_pbQuit_clicked()
{
	close();
}