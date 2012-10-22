#pragma once
#include <QMap>
#include <QString>
#include <QDateTime>
#include <QBitArray>
#include "jewelrydatabaselayer_global.h"

class JEWELRYDATABASELAYER_EXPORT StaffManager
{
public:
	class StaffManagerItem
	{
	public:
		StaffManagerItem():m_warehouseID(0),m_id(0){}
	public:
		int m_id;
		QString m_name;
		bool m_gender;//性别
		QString m_paperworkid;//证件号
		QBitArray m_photo;
		QDateTime m_fromDate;//入职日期
		QString m_post;//职务
		QString m_password;
		int m_warehouseID;
	};
public:
	~StaffManager(void);
	static StaffManager& getInstance();
	bool updateItem(const StaffManager::StaffManagerItem& item);
	bool addNewItem(const StaffManager::StaffManagerItem& item);
	bool deleteItem(int id);
	StaffManager::StaffManagerItem getStaffManagerItemByID(int id);
	QMap<int , StaffManager::StaffManagerItem>& getStaffManagerItemMap();
	void updateDatabase();

private:
	StaffManager(void);

private:
	QMap<int , StaffManagerItem> m_idMapItem;
	StaffManager::StaffManagerItem m_loginItem;
	static StaffManager* s_instance;
};
