#include "WarehouseInfo.h"
#include "sqlquery.h"
#include <QMessageBox>
#include <QApplication>

WarehouseInfo* WarehouseInfo::s_instance = NULL;

WarehouseInfo::WarehouseInfo(void)
{
	updateDataFromDatabase();
}

WarehouseInfo::~WarehouseInfo(void)
{
}

WarehouseInfo& WarehouseInfo::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new WarehouseInfo;
	}
	return *s_instance;
}

WarehouseInfo::WarehouseInfoItem WarehouseInfo::getWarehouseInfoItemByID(int id)
{
	WarehouseInfo::WarehouseInfoItem item;
	if (m_idMapItem.contains(id))
	{
		item = m_idMapItem[id];
	}
	return item;
}

QMap<int , WarehouseInfo::WarehouseInfoItem>& WarehouseInfo::getWarehouseInfoMap()
{
	return m_idMapItem;
}

void WarehouseInfo::updateDataFromDatabase()
{
	SqlQuery& query = SqlQuery::getInstance();
	if (query.query("call selectWarehouseInfo"))
	{
		m_idMapItem.clear();
		int rowCount = query.rowCount();
		int columnCount = query.columnCount();
		for (int row = 0 ; row < rowCount ; row++)
		{
			WarehouseInfo::WarehouseInfoItem item;
			for (int column = 0 ; column < columnCount ; column++)
			{
				QVariant v = query.value(row , column);
				QString fieldName = query.fieldName(column);
				if (fieldName == "id")
				{
					item.m_id = v.toInt();
				}
				else if (fieldName == "warehouseinfo")
				{
					item.m_warehouseInfo = v.toString();
					//item.m_warehouseInfo = QString::fromUtf8(v.toByteArray());
				}
			}
			m_idMapItem[item.m_id] = item;
		}
	}
}

bool WarehouseInfo::updateDatabase(const WarehouseInfo::WarehouseInfoItem& item)
{
	bool b = false;
	SqlQuery& query = SqlQuery::getInstance();
	if (item.m_id == 0 || item.m_warehouseInfo.isEmpty())
	{
		QMessageBox::warning(qApp->activeWindow() , QObject::tr("系统消息") , QObject::tr("更新失败。id = %1 , 仓库：%2").arg(item.m_id).arg(item.m_warehouseInfo));
	}
	else
	{
		QString sql = QString("call updateWarehouseInfo(%1 , '%2')").arg(item.m_id).arg(item.m_warehouseInfo);
		if (query.query(sql))
		{
			b = true;
		}
	}
	return b;
}

bool WarehouseInfo::addDataToDatabase(const WarehouseInfo::WarehouseInfoItem& item)
{
	bool b = false;
	SqlQuery& query = SqlQuery::getInstance();
	if (item.m_warehouseInfo.isEmpty())
	{
		QMessageBox::warning(qApp->activeWindow() , QObject::tr("系统消息") , QObject::tr("更新失败。id = %1 , 仓库：%2").arg(item.m_warehouseInfo));
	}
	else
	{
		QString sql = QString("call insertWarehouseInfo('%1')").arg(item.m_warehouseInfo);
		if (query.query(sql))
		{
			b = true;
		}
	}
	return b;
}

bool WarehouseInfo::deleteItem(int id)
{
	QString sql = QString("call deleteWarehouseInfo('%1')").arg(id);
	SqlQuery& query = SqlQuery::getInstance();
	if (query.query(sql))
	{
		m_idMapItem.remove(id);
		return true;
	}
	return false;
}

