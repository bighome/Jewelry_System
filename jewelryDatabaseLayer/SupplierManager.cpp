#include "SupplierManager.h"
#include "sqlquery.h"
#include <QMessageBox>
#include <QApplication>

SupplierManager* SupplierManager::s_instance = NULL;

SupplierManager::SupplierManager(void)
{
	updateDataFromDatabase();
}

SupplierManager::~SupplierManager(void)
{
}

SupplierManager& SupplierManager::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new SupplierManager;
	}
	return *s_instance;
}

void SupplierManager::updateDataFromDatabase()
{
	SqlQuery& query = SqlQuery::getInstance();
	if (query.query("call selectSuppliermanager"))
	{
		int rowCount = query.rowCount();
		int columnCount = query.columnCount();
		for (int row = 0 ; row < rowCount ; row++)
		{
			SupplierManagerItem item;
			for (int column = 0 ; column < columnCount ; column++)
			{
				QVariant v = query.value(row , column);
				QString fieldName = query.fieldName(column);
				if (fieldName == "id")
				{
					item.m_id = v.toInt();
				}
				else if (fieldName == "supplierName")
				{
					item.m_supplierName = v.toString();
				}
				else if (fieldName == "contactor")
				{
					item.m_contactor = v.toString();
				}
				else if (fieldName == "phone")
				{
					item.m_phone = v.toString();
				}
				else if (fieldName == "mobilePone")
				{
					item.m_mobilePone = v.toString();
				}
				else if (fieldName == "fax")
				{
					item.m_fax = v.toString();
				}
				else if (fieldName == "email")
				{
					item.m_email = v.toString();
				}
				else if (fieldName == "zipCode")
				{
					item.m_zipCode = v.toString();
				}
				else if (fieldName == "address")
				{
					item.m_address = v.toString();
				}
			}
			m_idMapItem[item.m_id] = item;
		}
	}
	else
	{
		QMessageBox::warning(qApp->activeWindow() , QObject::tr("系统消息") , query.lastError());
	}
}

SupplierManager::SupplierManagerItem SupplierManager::getSupplierManagerItemByID(int id)
{
	SupplierManager::SupplierManagerItem item;
	if (m_idMapItem.contains(id))
	{
		item = m_idMapItem[id];
	}
	return item;
}

bool SupplierManager::updateDatabase(const SupplierManagerItem& item)
{
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call updateSuppliermanager(%1,'%2','%3','%4','%5','%6','%7','%8','%9')").arg(item.m_id).arg(item.m_supplierName).arg(item.m_contactor).arg(item.m_phone)
																			.arg(item.m_mobilePone).arg(item.m_fax).arg(item.m_email).arg(item.m_zipCode).arg(item.m_address);
	if (!query.query(sql))
	{
		QMessageBox::warning(qApp->activeWindow() , QObject::tr("系统消息") , query.lastError());
		return false;
	}
	m_idMapItem[item.m_id] = item;
	return true;
}

bool SupplierManager::insertNewItem(const SupplierManagerItem& item)
{
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call insertSuppliermanager('%1','%2','%3','%4','%5','%6','%7','%8')").arg(item.m_supplierName).arg(item.m_contactor).arg(item.m_phone)
		.arg(item.m_mobilePone).arg(item.m_fax).arg(item.m_email).arg(item.m_zipCode).arg(item.m_address);
	if (query.query(sql))
	{
		updateDataFromDatabase();
		return true;
	}
	QMessageBox::warning(qApp->activeWindow() , QObject::tr("系统消息") , query.lastError());
	return false;
}

QMap<int , SupplierManager::SupplierManagerItem>& SupplierManager::getSupplierManagerMap()
{
	return m_idMapItem;
}


