#pragma once
#include <QString>
#include <QMap>
#include "jewelrydatabaselayer_global.h"

class JEWELRYDATABASELAYER_EXPORT WarehouseInfo
{
public:
	class WarehouseInfoItem
	{
	public:
		WarehouseInfoItem():m_id(0){}
		int m_id;
		QString m_warehouseInfo;
	};

public:
	~WarehouseInfo(void);
	static WarehouseInfo& getInstance();
	WarehouseInfo::WarehouseInfoItem getWarehouseInfoItemByID(int id);
	QMap<int , WarehouseInfo::WarehouseInfoItem>& getWarehouseInfoMap();
	void updateDataFromDatabase();
	bool updateDatabase(const WarehouseInfoItem& item);
	bool addDataToDatabase(const WarehouseInfoItem& item);
	bool deleteItem(int id);

private:
	WarehouseInfo(void);

private:
	static WarehouseInfo* s_instance;
	QMap<int , WarehouseInfoItem> m_idMapItem;
};
