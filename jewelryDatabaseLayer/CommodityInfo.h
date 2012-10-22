#pragma once
#include <QString>
#include "jewelrydatabaselayer_global.h"
#include <QMap>
#include <QList>

class JEWELRYDATABASELAYER_EXPORT CommodityInfo
{
	public:
		class CommodityInfoItem
		{
		public:
			CommodityInfoItem(void) : m_commodityPrice(0) , m_commodityDiscounts(1){}

		public:
			QString m_id;
			QString m_certificateNumbers;//证书编号
			QString m_commodityName;
			QString m_commodityType;
			QString m_commodityUnit;//单位
			float m_commodityPrice;//单价或质量
			float m_commodityJobPrice;//工本费
			float m_commodityGemPrice;//宝石价格（素金）
			float m_commodityRoundNumbers;//戒指圈号
			float m_commodityMainGemKarat;//主宝石克拉数
			float m_commodityAssistantGemKarat;//副宝石克拉数
			QString m_commodityGrade;//等级
			QString m_commodityColor;//颜色
			float m_commodityGoldWeight;//金重
			float m_commodityGrossWeight;//总质量
			float m_commodityDiscounts;//商品固定折扣，默认为一
      float m_commodityCost;//商品进价
			QString m_mark;
		};
public:
	static CommodityInfo& getInstance();
	CommodityInfo::CommodityInfoItem getCommodityInfoItemByID(QString id);
	QMap<QString , CommodityInfo::CommodityInfoItem>& getCommodityInfoItemMap();
	void updateDataFromDatabase();
	bool updateDatabase(const CommodityInfoItem& item);
	bool insertNewItem(const CommodityInfoItem& item);
	bool insertNewItemEXCEL(const CommodityInfoItem& item);
	bool deleteItem(const QString& id);
	~CommodityInfo(void);

private:
	CommodityInfo(void);

private:
	QMap<QString , CommodityInfoItem> m_idMapItem;
	static CommodityInfo* s_instace;
};
