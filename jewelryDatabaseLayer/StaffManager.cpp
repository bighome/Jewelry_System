#include "StaffManager.h"
#include "sqlquery.h"


StaffManager* StaffManager::s_instance = NULL;

StaffManager::StaffManager(void)
{
	updateDatabase();
}

StaffManager::~StaffManager(void)
{
}

StaffManager& StaffManager::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new StaffManager;
	}
	return *s_instance;
}

bool StaffManager::updateItem(const StaffManager::StaffManagerItem& item)
{
	/*        IN id_p INTEGER(11),1
	IN name_p VARCHAR(20),2
	IN gender_p BOOLEAN,3
	IN paperworkid_p VARCHAR(20),4
	IN post_p VARCHAR(20),5
	IN password_p VARCHAR(20),6
	IN warehouseID_p INTEGER(11)*/
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call updateStaffManager(%1,'%2',%3,'%4','%5','%6',%7)").arg(item.m_id)
				.arg(item.m_name).arg(item.m_gender).arg(item.m_paperworkid).arg(item.m_post).arg(item.m_password).arg(item.m_warehouseID);
	if (query.query(sql))
	{
		m_idMapItem[item.m_id] = item;
		return true;
	}
	return false;
}

bool StaffManager::addNewItem(const StaffManager::StaffManagerItem& item)
{
	/*        IN name_p VARCHAR(20),1
	IN gender_p BOOLEAN,2
	IN paperworkid_p VARCHAR(20),3
	IN post_p VARCHAR(20),4
	IN password_p VARCHAR(20),5
	IN warehouseID_p INTEGER(11)*/
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call insertStaffManager('%1',%2,'%3','%4','%5',%6)")
		.arg(item.m_name).arg(item.m_gender).arg(item.m_paperworkid).arg(item.m_post).arg(item.m_password).arg(item.m_warehouseID);
	if (query.query(sql))
	{
		updateDatabase();
		return true;
	}
	return false;
}

bool StaffManager::deleteItem(int id)
{
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call deleteStaffManager").arg(id);
	if (query.query(sql))
	{
		m_idMapItem.remove(id);
		return true;
	}
	return false;
}


StaffManager::StaffManagerItem StaffManager::getStaffManagerItemByID(int id)
{
	StaffManager::StaffManagerItem item;
	if (m_idMapItem.contains(id))
	{
		item = m_idMapItem[id];
	}
	return item;
}

QMap<int , StaffManager::StaffManagerItem>& StaffManager::getStaffManagerItemMap()
{
	return m_idMapItem;
}

void StaffManager::updateDatabase()
{
	SqlQuery& query = SqlQuery::getInstance();
	if (query.query("call selectStaffManager"))
	{
		m_idMapItem.clear();
		int rowCount = query.rowCount();
		int  columnCount = query.columnCount();
		for (int row = 0 ; row < rowCount ; row++)
		{
			StaffManager::StaffManagerItem item;
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
				else if (field == "paperworkid")
				{
					item.m_paperworkid = v.toString();
				}
				else if (field == "photo")
				{
					item.m_photo = v.toBitArray();
				}
				else if (field == "fromDate")
				{
					item.m_fromDate = v.toDateTime();
				}
				else if (field == "post")
				{
					item.m_post = v.toString();
				}
				else if (field == "password")
				{
					item.m_password = v.toString();
				}
				else if (field == "warehouseID")
				{
					item.m_warehouseID = v.toInt();
				}
			}
			m_idMapItem[item.m_id] = item;
		}
	}
}
