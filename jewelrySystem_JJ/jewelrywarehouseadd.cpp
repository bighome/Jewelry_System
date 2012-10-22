#include "jewelrywarehouseadd.h"
#include "WarehouseInfo.h"

jewelryWarehouseAdd::jewelryWarehouseAdd(QWidget *parent)
	: QDialog()
{
	ui.setupUi(this);
}

jewelryWarehouseAdd::jewelryWarehouseAdd(QWidget *parent , const WarehouseInfo::WarehouseInfoItem& item)
: QDialog(parent)
{
	ui.setupUi(this);
	ui.leID->setText(QString::number(item.m_id));
	ui.leWarehouse->setText(item.m_warehouseInfo);
}

jewelryWarehouseAdd::~jewelryWarehouseAdd()
{

}


void jewelryWarehouseAdd::on_pbOK_clicked()
{
	WarehouseInfo& warehouseInfo = WarehouseInfo::getInstance();
	QString warehouse = ui.leWarehouse->text();
	bool b = false;
	if (warehouse.count())
	{
		WarehouseInfo::WarehouseInfoItem item;
		item.m_warehouseInfo = warehouse;
		if (ui.leID->text().count())
		{
			item.m_id = ui.leID->text().toInt();
			b = warehouseInfo.updateDatabase(item);
		}
		else
		{
			b = warehouseInfo.addDataToDatabase(item);
		}
		if (b)
		{
			accept();
		}
	}
}

void jewelryWarehouseAdd::on_pbCancel_clicked()
{
	reject();
}