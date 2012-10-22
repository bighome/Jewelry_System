#include "jewelryVIPManagerDialog.h"
#include "jewelryvipmanageradd.h"
#include <QMessageBox>

jewelryVIPManagerDialog::jewelryVIPManagerDialog(QWidget *parent)
	: QDialog()
{
	ui.setupUi(this);
  setWindowTitle(tr("会员管理"));
	m_currentVIPItem.m_id = 0;
	updateUIFromData();
}

jewelryVIPManagerDialog::~jewelryVIPManagerDialog()
{

}

VIPManager::VIPManagerItem jewelryVIPManagerDialog::getCurrentVIPItem()
{
	return m_currentVIPItem;
}

void jewelryVIPManagerDialog::updateUIFromData()
{
	VIPManager& m_vipManager = VIPManager::getInsance();
	QMap<int , VIPManager::VIPManagerItem>& itemMap = m_vipManager.getVIPManagerItemMap();
	ui.tableWidget->setRowCount(itemMap.count());
	int row = 0;
	for (QMap<int , VIPManager::VIPManagerItem>::iterator i = itemMap.begin() ; i != itemMap.end() ; i++ , row++)
	{
		VIPManager::VIPManagerItem& item = *i;
		setTableWidgetItem(row , item);
	}
}

void jewelryVIPManagerDialog::setTableWidgetItem(int row , VIPManager::VIPManagerItem& item)
{
	QTableWidgetItem* tableItem = NULL;
	{
		tableItem = new QTableWidgetItem(QString::number(item.m_id));
		ui.tableWidget->setItem(row , TABLEITEM_id , tableItem);
	}
	{
		tableItem = new QTableWidgetItem(item.m_name);
		ui.tableWidget->setItem(row , TABLEITEM_name , tableItem);
	}
	{
		QString text = tr("男");
		if (!item.m_gender)
		{
			text = tr("女");
		}
		tableItem = new QTableWidgetItem(text);
		ui.tableWidget->setItem(row , TABLEITEM_gender , tableItem);
	}
	{
		tableItem = new QTableWidgetItem(item.m_paperworkID);
		ui.tableWidget->setItem(row , TABLEITEM_paperworkID , tableItem);
	}
	{
		tableItem = new QTableWidgetItem(item.m_phone);
		ui.tableWidget->setItem(row , TABLEITEM_phone , tableItem);
	}
	{
		tableItem = new QTableWidgetItem(item.m_address);
		ui.tableWidget->setItem(row , TABLEITEM_address , tableItem);
	}
	{
		tableItem = new QTableWidgetItem(item.m_cardType);
		ui.tableWidget->setItem(row , TABLEITEM_cardType , tableItem);
	}
	{
		tableItem = new QTableWidgetItem(QString::number(item.m_consumptionSum , 'f' , 4));
		ui.tableWidget->setItem(row , TABLEITEM_consumptionSum , tableItem);
	}
	{
		tableItem = new QTableWidgetItem(QString::number(item.m_integration));
		ui.tableWidget->setItem(row , TABLEITEM_integration , tableItem);
	}
	{
		tableItem = new QTableWidgetItem(item.m_createDatetime.toString());
		ui.tableWidget->setItem(row , TABLEITEM_createDatetime , tableItem);
	}
}


void jewelryVIPManagerDialog::on_pbAdd_clicked()
{
	jewelryVIPManagerAdd add(this);
	if (add.exec())
	{
		updateUIFromData();
	}
}

void jewelryVIPManagerDialog::on_pbEdit_clicked()
{
	int row = ui.tableWidget->currentRow();
	if (row >= 0)
	{
		int id = ui.tableWidget->item(row , TABLEITEM_id)->text().toInt();
		jewelryVIPManagerAdd add(id , this);
		if (add.exec())
		{
			VIPManager::VIPManagerItem item = add.getVIPManagerItem();
			setTableWidgetItem(row , item);
		}
	}
}

void jewelryVIPManagerDialog::on_pbQuit_clicked()
{
	accept();
}

void jewelryVIPManagerDialog::on_pbDelete_clicked()
{
	if(QMessageBox::question(this , tr("系统消息") , tr("确定删除？") , QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		int row = ui.tableWidget->currentRow();
		if (row >= 0)
		{
			int id = ui.tableWidget->item(row , TABLEITEM_id)->text().toInt();
			if(VIPManager::getInsance().deleteItem(id))
				updateUIFromData();
		}
	}
}