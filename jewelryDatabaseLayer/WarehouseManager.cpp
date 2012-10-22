#include "WarehouseManager.h"
#include "sqlquery.h"

WarehouseManager* WarehouseManager::s_instance = NULL;

WarehouseManager::WarehouseManager(void)
{
	updateFromDatabase();
}

WarehouseManager::~WarehouseManager(void)
{
}

WarehouseManager& WarehouseManager::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new WarehouseManager;
	}
	return *s_instance;
}

WarehouseManager::WarehouseManagerItem WarehouseManager::getWarehouseManagerItem(int warehoseID , QString commodityID)
{
	WarehouseManagerItem tem;
	for (QList<WarehouseManagerItem>::iterator i = m_warehouseManagerItemList.begin() ; i != m_warehouseManagerItemList.end() ; i++)
	{
		const WarehouseManagerItem& item = *i;
		if (item.m_id == warehoseID && item.m_commodityID == commodityID)
		{
			tem = item;
			break;
		}
	}
	return tem;
}

QList<WarehouseManager::WarehouseManagerItem>& WarehouseManager::getWarehouseManagerItemList()
{
	return m_warehouseManagerItemList;
}

void WarehouseManager::updateFromDatabase()
{
	SqlQuery& query = SqlQuery::getInstance();
	if (query.query("call selectWarehouseManager"))
	{
		m_warehouseManagerItemList.clear();
		int rowCount = query.rowCount();
		int columnCount = query.columnCount();
		for (int row = 0 ; row < rowCount ; row++)
		{
			WarehouseManager::WarehouseManagerItem item;
			for (int column = 0 ; column < columnCount ; column++)
			{
				QVariant v = query.value(row , column);
				const QString field = query.fieldName(column);
				if (field == "id")
				{
					item.m_id = v.toInt();
				}
				else if (field == "commodityCount")
				{
					item.m_commodityCount = v.toInt();
				}
				else if (field == "commodityID")
				{
					item.m_commodityID = v.toString();
				}
			}
			m_warehouseManagerItemList << item;
		}
	}
}
