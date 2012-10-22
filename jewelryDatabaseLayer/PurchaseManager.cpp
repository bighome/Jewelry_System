#include "PurchaseManager.h"
#include "sqlquery.h"
#include "WarehouseManager.h"

PurchaseManager* PurchaseManager::s_instance = NULL;

PurchaseManager::PurchaseManager(void)
{
	updateDataFromDatabase();
}

PurchaseManager::~PurchaseManager(void)
{
}

PurchaseManager& PurchaseManager::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new PurchaseManager;
	}
	return *s_instance;
}

void PurchaseManager::updateDataFromDatabase()
{
	SqlQuery& query = SqlQuery::getInstance();
	if (query.query("call selectPurchaseManager"))
	{
		m_idMapItem.clear();
		int rowCount = query.rowCount();
		int columnCount = query.columnCount();
		for (int row = 0 ; row < rowCount ; row++)
		{
			PurchaseManagerItem item;
			for (int column = 0 ; column < columnCount ; column++)
			{
				QVariant v = query.value(row , column);
				QString fieldName = query.fieldName(column);
				if (fieldName == "id")
				{
					item.m_id = v.toInt();
				}
				else if (fieldName == "supplierID")
				{
					item.m_supplierID = v.toInt();
				}
				else if (fieldName == "commodityID")
				{
					item.m_commodityID = v.toString();
				}
				else if (fieldName == "purchasePrice")
				{
					item.m_commodityPrice = v.toFloat();
				}
				else if (fieldName == "commodityCount")
				{
					item.m_commodityCount = v.toInt();
				}
				else if (fieldName == "staffID")
				{
					item.m_staffID = v.toInt();
				}
				else if (fieldName == "warehouseID")
				{
					item.m_warehouseID = v.toInt();
				}
			}
			m_idMapItem[item.m_id] = item;
		}
	}
}

QMap<int , PurchaseManager::PurchaseManagerItem>& PurchaseManager::getPurchaseManagerItemMap()
{
	return m_idMapItem;
}

PurchaseManager::PurchaseManagerItem PurchaseManager::getPurchaseManagerItemByID(int id)
{
	PurchaseManagerItem item;
	if (m_idMapItem.contains(id))
	{
		item = m_idMapItem[id];
	}
	return item;
}

bool PurchaseManager::updateDatabase(const PurchaseManager::PurchaseManagerItem& item)
{
	/*CREATE DEFINER = 'root'@'localhost' PROCEDURE `insertPurchasemanager`(
	IN supplierID_p INTEGER(11),
	IN commodityID_p VARCHAR(40),
	IN warehouseID_p INTEGER(11),
	IN staffID_p INTEGER(11),
	IN commodityCount_p INTEGER(11),
	IN purchasePrice_p FLOAT(9,4)
	)*/

	bool b = false;
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call updatePurchasemanager(%1,'%2',%3,%4,%5,%6,%7)")
		.arg(item.m_id).arg(item.m_supplierID).arg(item.m_commodityID).arg(item.m_warehouseID)
		.arg(item.m_staffID).arg(item.m_commodityCount).arg(item.m_commodityPrice , 0 ,'f' , 4);
	if (query.query(sql))
	{
		m_idMapItem[item.m_id] = item;
		b = true;
	}
	return b;
}

bool PurchaseManager::insertNewItem(const PurchaseManager::PurchaseManagerItem& item)
{
	/*CREATE DEFINER = 'root'@'localhost' PROCEDURE `updatePurchasemanager`(
	IN id_p INTEGER(11),
	IN supplierID_p INTEGER(11),
	IN commodityID_p VARCHAR(40),
	IN warehouseID_p INTEGER(11),
	IN staffID_p INTEGER(11),
	IN commodityCount_p INTEGER(11),
	IN purchasePrice_p FLOAT(9,4)
	)*/
	bool b = false;
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call insertPurchasemanager(%1,'%2',%3,%4,%5,%6)")
		.arg(item.m_supplierID).arg(item.m_commodityID).arg(item.m_warehouseID).arg(item.m_staffID)
		.arg(item.m_commodityCount).arg(item.m_commodityPrice , 0 ,'f' , 4);
	if (query.query(sql))
	{
		WarehouseManager& warehouseManager = WarehouseManager::getInstance();
		WarehouseManager::WarehouseManagerItem warehouseManagerItem = warehouseManager.getWarehouseManagerItem(item.m_warehouseID , item.m_commodityID);
		QString procedure;
		if (warehouseManagerItem.m_commodityID.count() == 0)
		{
			procedure = "insertWarehouseManager";
		}
		else
			procedure = "updateWarehouseManage";
		QString sql = QString("call %1(%2 , '%3' , %4)").arg(procedure).arg(item.m_warehouseID).arg(item.m_commodityID).arg(item.m_commodityCount);
		query.query(sql);
		warehouseManager.updateFromDatabase();
		updateDataFromDatabase();
		b = true;
	}
	return b;
}

