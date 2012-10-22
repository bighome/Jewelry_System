#pragma once
#include <QMap>
#include <QString>
#include "jewelrydatabaselayer_global.h"

class JEWELRYDATABASELAYER_EXPORT WarehouseManager
{
public:
	class WarehouseManagerItem
	{
	public:
		WarehouseManagerItem(): m_id(0),m_commodityCount(0){}

	public:
		int m_id;
		int m_commodityCount;
		QString m_commodityID;
	};
public:
	~WarehouseManager(void);
	static WarehouseManager& getInstance();
	void updateFromDatabase();
	WarehouseManager::WarehouseManagerItem getWarehouseManagerItem(int warehoseID , QString commodityID);
	QList<WarehouseManager::WarehouseManagerItem>& getWarehouseManagerItemList();

private:
	WarehouseManager(void);

private:
	static WarehouseManager* s_instance;
	QList<WarehouseManagerItem> m_warehouseManagerItemList;
};
