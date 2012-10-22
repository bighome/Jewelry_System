#pragma once

#include "jewelrydatabaselayer_global.h"
#include <QString>
#include <QMap>
#include <QDateTime>

class JEWELRYDATABASELAYER_EXPORT VIPManager
{
public:
	class VIPManagerItem
	{
	public:
		VIPManagerItem():m_consumptionSum(0),m_integration(0){}
		int m_id;
		QString m_name;
		bool m_gender;//man is true
		QString m_paperworkID;
		QString m_phone;
		QString m_address;
		QString m_cardType;
		float m_consumptionSum;
		int m_integration;
		QDateTime m_createDatetime;
	};
public:
	~VIPManager(void);
	static VIPManager& getInsance();
	bool addNewItem(const VIPManager::VIPManagerItem& item);
	bool updateItem(const VIPManager::VIPManagerItem& item);
	bool deleteItem(int id);
	VIPManager::VIPManagerItem getVIPManagerItemByID(int vipID);
	QMap<int , VIPManager::VIPManagerItem>& getVIPManagerItemMap();
	void updateDatabase();

private:
	VIPManager(void);

private:
	QMap<int , VIPManagerItem> m_idMapItem;

private:
	static VIPManager* s_instance;
};
