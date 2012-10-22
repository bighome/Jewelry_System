#include "jewelrystaffmanageradd.h"
#include "WarehouseInfo.h"

jewelryStaffManagerAdd::jewelryStaffManagerAdd(QWidget *parent)
	: QDialog(parent)
	, m_id(0)
{
	init();
}

jewelryStaffManagerAdd::jewelryStaffManagerAdd(int id , QWidget *parent)
: QDialog(parent)
, m_id(id)
{
	init();
	m_staffManagerItem = StaffManager::getInstance().getStaffManagerItemByID(m_id);
	updateDataFromUI();
}

jewelryStaffManagerAdd::~jewelryStaffManagerAdd()
{

}

StaffManager::StaffManagerItem jewelryStaffManagerAdd::getStaffManagerItem()
{
	return m_staffManagerItem;
}

void jewelryStaffManagerAdd::init()
{
	ui.setupUi(this);
	QMap<int , WarehouseInfo::WarehouseInfoItem>& warehouseInfoItemMap = WarehouseInfo::getInstance().getWarehouseInfoMap();
	for (QMap<int , WarehouseInfo::WarehouseInfoItem>::iterator i = warehouseInfoItemMap.begin() ; i != warehouseInfoItemMap.end() ; i++)
	{
		WarehouseInfo::WarehouseInfoItem& item = *i;
		ui.cbWarehouse->addItem(item.m_warehouseInfo , item.m_id);
	}
}

void jewelryStaffManagerAdd::on_cbWarehouse_currentIndexChanged(int)
{
	
}

void jewelryStaffManagerAdd::on_pbOK_clicked()
{
	updateUIFromData();
	if (m_id)
	{
		StaffManager::getInstance().updateItem(m_staffManagerItem);
	}
	else
	{
		StaffManager::getInstance().addNewItem(m_staffManagerItem);
	}
	accept();
}

void jewelryStaffManagerAdd::on_pbCancel_clicked()
{
	reject();
}

void jewelryStaffManagerAdd::updateUIFromData()
{
	m_staffManagerItem.m_name = ui.leName->text();
	m_staffManagerItem.m_gender = ui.cbGender->currentIndex();
	m_staffManagerItem.m_paperworkid = ui.lePaperworkID->text();
	m_staffManagerItem.m_fromDate = ui.dateTimeEdit->dateTime();
	m_staffManagerItem.m_post = ui.cbPost->currentText();
	m_staffManagerItem.m_password = ui.lePassword->text();
	m_staffManagerItem.m_warehouseID = ui.cbWarehouse->itemData(ui.cbWarehouse->currentIndex()).toInt();
}

void jewelryStaffManagerAdd::updateDataFromUI()
{
	ui.leName->setText(m_staffManagerItem.m_name);
	ui.cbGender->setCurrentIndex(m_staffManagerItem.m_gender);
	ui.lePaperworkID->setText(m_staffManagerItem.m_paperworkid);
	ui.dateTimeEdit->setDateTime(m_staffManagerItem.m_fromDate);

	int index = ui.cbPost->findText(m_staffManagerItem.m_post);
	if (index >= 0)
	{
		ui.cbPost->setCurrentIndex(index);
	}
	ui.lePassword->setText(m_staffManagerItem.m_password);
	ui.cbWarehouse->setCurrentIndex(ui.cbWarehouse->findData(m_staffManagerItem.m_warehouseID));
}

