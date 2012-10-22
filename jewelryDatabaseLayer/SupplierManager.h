#pragma once
#include <QMap>
#include <QString>
#include <QObject>
#include "jewelrydatabaselayer_global.h"

class JEWELRYDATABASELAYER_EXPORT SupplierManager
{
public:
	class SupplierManagerItem
	{
	public:
		SupplierManagerItem():m_id(0){}
		int m_id;
		QString m_supplierName;
		QString m_contactor;
		QString m_phone;
		QString m_mobilePone;
		QString m_fax;
		QString m_email;
		QString m_zipCode;
		QString m_address;
	};

public:
	~SupplierManager(void);
	static SupplierManager& getInstance();
	SupplierManager::SupplierManagerItem getSupplierManagerItemByID(int id);
	bool updateDatabase(const SupplierManagerItem& item);
	bool insertNewItem(const SupplierManagerItem& item);
	QMap<int , SupplierManager::SupplierManagerItem>& getSupplierManagerMap();
	void updateDataFromDatabase();

private:
	SupplierManager(void);

private:
	static SupplierManager* s_instance;
	QMap<int , SupplierManagerItem> m_idMapItem;

};
