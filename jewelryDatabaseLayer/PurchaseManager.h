#pragma once
#include <QMap>
#include <QString>
#include "jewelrydatabaselayer_global.h"

class JEWELRYDATABASELAYER_EXPORT PurchaseManager
{
public:
	class PurchaseManagerItem
	{
	public:
		PurchaseManagerItem():m_id(0),m_supplierID(0),m_commodityPrice(0),m_commodityCount(0),m_staffID(0),m_warehouseID(0){}

		int m_id;
		int m_supplierID;
		QString m_commodityID;
		float m_commodityPrice;
		int m_commodityCount;
		int m_staffID;
		int m_warehouseID;
	};

public:
	~PurchaseManager(void);
	static PurchaseManager& getInstance();
	void updateDataFromDatabase();
	bool updateDatabase(const PurchaseManager::PurchaseManagerItem& item);
	bool insertNewItem(const PurchaseManager::PurchaseManagerItem& item);

	QMap<int , PurchaseManagerItem>& getPurchaseManagerItemMap();
	PurchaseManager::PurchaseManagerItem getPurchaseManagerItemByID(int id);

private:
	PurchaseManager(void);

private:
	static PurchaseManager* s_instance;
	QMap<int , PurchaseManagerItem> m_idMapItem;
};
