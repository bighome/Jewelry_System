#pragma once
#include "CommodityInfo.h"
#include "StaffManager.h"
#include <QList>
#include "jewelrydatabaselayer_global.h"
#include "VIPManager.h"
#include "WarehouseManager.h"

class JEWELRYDATABASELAYER_EXPORT SaleManager
{
public:
	class SaleItem
	{
	public:
		SaleItem():m_tradeDiscounts(1){}
		class CommodityItem
		{
		public:
			CommodityInfo::CommodityInfoItem m_commodityInfoItem;
			int m_saleCount;
			WarehouseManager::WarehouseManagerItem m_warehouseItem;
			float m_amount;
		};
		QList<SaleManager::SaleItem::CommodityItem> m_commodityList;
		StaffManager::StaffManagerItem m_staffItem;
		QString m_payment;
		float m_tradeDiscounts;
		VIPManager::VIPManagerItem m_vipItem;
		QString m_saleID;
	};

public:
	SaleManager(void);
	~SaleManager(void);

	bool saled(const SaleItem& item);
	//QString lastID();

private:
	QString m_lastID;
};
