#include "jewelrysupplierinformation.h"
#include "SupplierManager.h"
#include "jewelrysupplierinformationedit.h"

jewelrySupplierInformation::jewelrySupplierInformation(QWidget *parent)
	: QDialog()
{
	ui.setupUi(this);
	updateUIFromDatabase();
}

jewelrySupplierInformation::~jewelrySupplierInformation()
{

}

void jewelrySupplierInformation::updateUIFromDatabase()
{
	SupplierManager& supplierManager = SupplierManager::getInstance();
	const QMap<int , SupplierManager::SupplierManagerItem>& supplierManagerMap = supplierManager.getSupplierManagerMap();
	ui.tableWidget->setRowCount(supplierManagerMap.count());
	int row = 0;
	for (QMap<int , SupplierManager::SupplierManagerItem>::const_iterator i = supplierManagerMap.begin() ; i != supplierManagerMap.end() ; i++ , row++)
	{
		const SupplierManager::SupplierManagerItem& supplierManagerItem = *i;
		QTableWidgetItem* item = NULL;
		{
			item = new QTableWidgetItem(QString::number(supplierManagerItem.m_id));
			ui.tableWidget->setItem(row ,TABLEITEM_id , item);
		}
		{
			item = new QTableWidgetItem((supplierManagerItem.m_supplierName));
			ui.tableWidget->setItem(row ,TABLEITEM_supplierName , item);
		}
		{
			item = new QTableWidgetItem((supplierManagerItem.m_contactor));
			ui.tableWidget->setItem(row ,TABLEITEM_contactor , item);
		}
		{
			item = new QTableWidgetItem((supplierManagerItem.m_phone));
			ui.tableWidget->setItem(row ,TABLEITEM_phone , item);
		}
		{
			item = new QTableWidgetItem((supplierManagerItem.m_mobilePone));
			ui.tableWidget->setItem(row ,TABLEITEM_mobilePone , item);
		}
		{
			item = new QTableWidgetItem((supplierManagerItem.m_fax));
			ui.tableWidget->setItem(row ,TABLEITEM_fax , item);
		}
		{
			item = new QTableWidgetItem((supplierManagerItem.m_email));
			ui.tableWidget->setItem(row ,TABLEITEM_email , item);
		}
		{
			item = new QTableWidgetItem((supplierManagerItem.m_address));
			ui.tableWidget->setItem(row ,TABLEITEM_address , item);
		}
		{
			item = new QTableWidgetItem((supplierManagerItem.m_zipCode));
			ui.tableWidget->setItem(row ,TABLEITEM_zipCode , item);
		}
	}
	ui.tableWidget->setCurrentCell(0 , 0);
}

void jewelrySupplierInformation::on_pbAdd_clicked()
{
	jewelrySupplierInformationEdit edit(this);
	if (edit.exec())
	{
		updateUIFromDatabase();
	}
}

void jewelrySupplierInformation::on_pbEdit_clicked()
{
	SupplierManager::SupplierManagerItem item;
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		item.m_id = ui.tableWidget->item(row , TABLEITEM_id)->text().toInt();
		item.m_supplierName = ui.tableWidget->item(row , TABLEITEM_supplierName)->text();
		item.m_contactor = ui.tableWidget->item(row , TABLEITEM_contactor)->text();
		item.m_phone = ui.tableWidget->item(row , TABLEITEM_phone)->text();
		item.m_mobilePone = ui.tableWidget->item(row , TABLEITEM_mobilePone)->text();
		item.m_fax = ui.tableWidget->item(row , TABLEITEM_fax)->text();
		item.m_email = ui.tableWidget->item(row , TABLEITEM_email)->text();
		item.m_address = ui.tableWidget->item(row , TABLEITEM_address)->text();
		item.m_zipCode = ui.tableWidget->item(row , TABLEITEM_zipCode)->text();
		jewelrySupplierInformationEdit edit(this , item);
		if (edit.exec())
		{
			updateUIFromDatabase();
		}
	}
}

SupplierManager::SupplierManagerItem jewelrySupplierInformation::getCurrentSupplierManagerItem()
{
	SupplierManager::SupplierManagerItem supplierManagerItem;
	SupplierManager& supplierManager = SupplierManager::getInstance();
	int currentRow = ui.tableWidget->currentRow();
	if (currentRow > -1)
	{
		QTableWidgetItem* item = ui.tableWidget->item(currentRow , TABLEITEM_id);
		if (item)
		{
			int id = item->text().toInt();
			supplierManagerItem = supplierManager.getSupplierManagerItemByID(id);
		}
	}
	return supplierManagerItem;
}


void jewelrySupplierInformation::on_pbQuit_clicked()
{
	close();
}