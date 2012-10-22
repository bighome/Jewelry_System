#include "jewelrygoodsfiles.h"
#include "jewelrygoodsfilesadd.h"
#include "CommodityInfo.h"

jewelryGoodsFiles::jewelryGoodsFiles(QWidget *parent)
{
	ui.setupUi(this);
	updateUIFromDatabase();
}

jewelryGoodsFiles::~jewelryGoodsFiles()
{
	
}


void jewelryGoodsFiles::on_pbAdd_clicked()
{
	jewelryGoodsFilesAdd add(this);
	if (add.exec())
	{
		updateUIFromDatabase();
	}
}

void jewelryGoodsFiles::on_pbEdit_clicked()
{
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		jewelryGoodsFilesAdd add(this , ui.tableWidget->item(row , TABLEITEM_id)->text());
		if (add.exec())
		{
			updateUIFromDatabase();
		}
	}
}

void jewelryGoodsFiles::on_pbQuit_clicked()
{
	close();
}

void jewelryGoodsFiles::updateUIFromDatabase()
{
	CommodityInfo& commodityInfo = CommodityInfo::getInstance();
	QMap<QString , CommodityInfo::CommodityInfoItem>& commodityInfoItemMap = commodityInfo.getCommodityInfoItemMap();
	ui.tableWidget->setRowCount(commodityInfoItemMap.count());
	int row = 0;
	for (QMap<QString , CommodityInfo::CommodityInfoItem>::iterator i = commodityInfoItemMap.begin() ; i != commodityInfoItemMap.end() ; i++ , row++)
	{
		CommodityInfo::CommodityInfoItem& commodityInfoItem = *i;
		QTableWidgetItem* tableItem = NULL;
		{
			tableItem = new QTableWidgetItem(commodityInfoItem.m_id);
			ui.tableWidget->setItem(row , TABLEITEM_id , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(commodityInfoItem.m_commodityType);
			ui.tableWidget->setItem(row , TABLEITEM_commodityType , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(commodityInfoItem.m_commodityName);
			ui.tableWidget->setItem(row , TABLEITEM_commodityName , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(commodityInfoItem.m_commodityUnit);
			ui.tableWidget->setItem(row , TABLEITEM_commodityUnit , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(QString::number(commodityInfoItem.m_commodityPrice , 'f' , 4));
			ui.tableWidget->setItem(row , TABLEITEM_commodityPrice , tableItem);
		}
		{
			tableItem = new QTableWidgetItem(QString::number(commodityInfoItem.m_commodityDiscounts , 'f' , 4));
			ui.tableWidget->setItem(row , TABLEITEM_commodityDiscounts , tableItem);
		}
	}
}

void jewelryGoodsFiles::on_pbDelete_clicked()
{
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		QString commodityID = ui.tableWidget->item(row , TABLEITEM_id)->text();
		CommodityInfo& commodityInfo = CommodityInfo::getInstance();
		if (commodityInfo.deleteItem(commodityID))
		{
			updateUIFromDatabase();
		}
	}
}