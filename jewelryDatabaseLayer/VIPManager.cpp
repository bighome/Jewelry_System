#include "VIPManager.h"
#include "sqlquery.h"

VIPManager* VIPManager::s_instance = NULL;

VIPManager::VIPManager(void)
{
	updateDatabase();
}

VIPManager::~VIPManager(void)
{
}

VIPManager& VIPManager::getInsance()
{
	if (s_instance == NULL)
	{
		s_instance = new VIPManager;
	}
	return *s_instance;
}

bool VIPManager::addNewItem(const VIPManager::VIPManagerItem& item)
{
	SqlQuery& query = SqlQuery::getInstance();
	//name , gender , paperworkID , phone , address , cardType , consumptionSum , integration
	QString sql = QString("call insertVIPManager('%1',%2,'%3','%4','%5','%6',%7,%8)")
		.arg(item.m_name).arg(item.m_gender).arg(item.m_paperworkID).arg(item.m_phone).arg(item.m_address)
		.arg(item.m_cardType).arg(item.m_consumptionSum).arg(item.m_integration);
	if (query.query(sql))
	{
		updateDatabase();
		return true;
	}
	return false;
}

bool VIPManager::updateItem(const VIPManager::VIPManagerItem& item)
{
	if (m_idMapItem.contains(item.m_id))
	{
		SqlQuery& query = SqlQuery::getInstance();
		QString sql = QString("call updateVIPManager(%1,'%2',%3,'%4','%5','%6','%7',%8,%9)")
			.arg(item.m_id).arg(item.m_name).arg(item.m_gender).arg(item.m_paperworkID).arg(item.m_phone)
			.arg(item.m_address).arg(item.m_cardType).arg(item.m_consumptionSum).arg(item.m_integration);
		if (query.query(sql))
		{
			m_idMapItem[item.m_id] = item;
			return true;
		}
	}
	return false;
}

bool VIPManager::deleteItem(int id)
{
	if (m_idMapItem.contains(id))
	{
		SqlQuery& query = SqlQuery::getInstance();
		QString sql = QString("call deleteVIPManager(%1)").arg(id);
		if (query.query(sql))
		{
			m_idMapItem.remove(id);
			return true;
		}
		else
			return false;
	}
	else
		return true;
	return false;
}

VIPManager::VIPManagerItem VIPManager::getVIPManagerItemByID(int vipID)
{
	VIPManager::VIPManagerItem item;
	if (m_idMapItem.contains(vipID))
	{
		item = m_idMapItem[vipID];
	}
	return item;
}

QMap<int , VIPManager::VIPManagerItem>& VIPManager::getVIPManagerItemMap()
{
	return m_idMapItem;
}

void VIPManager::updateDatabase()
{
	m_idMapItem.clear();
	SqlQuery& query = SqlQuery::getInstance();
	if (query.query("call selectVIPManager"))
	{
		int rowCount = query.rowCount();
		int  columnCount = query.columnCount();
		for (int row = 0 ; row < rowCount ; row++)
		{
			VIPManager::VIPManagerItem item;
			for (int column = 0 ; column < columnCount ; column++)
			{
				QVariant v = query.value(row , column);
				if (v.isNull())
				{
					continue;
				}
				const QString field = query.fieldName(column);
				if (field == "id")
				{
					item.m_id = v.toInt();
				}
				else if (field == "name")
				{
					item.m_name = v.toString();
				}
				else if (field == "gender")
				{
					item.m_gender = v.toBool();
				}
				else if (field == "paperworkID")
				{
					item.m_paperworkID = v.toString();
				}
				else if (field == "phone")
				{
					item.m_phone = v.toString();
				}
				else if (field == "address")
				{
					item.m_address = v.toString();
				}
				else if (field == "cardType")
				{
					item.m_cardType = v.toString();
				}
				else if (field == "consumptionSum")
				{
					item.m_consumptionSum = v.toFloat();
				}
				else if (field == "integration")
				{
					item.m_cardType = v.toInt();
				}
				else if (field == "createDatetime")
				{
					item.m_createDatetime = v.toDateTime();
				}
			}
			m_idMapItem[item.m_id] = item;
		}
	}
}
