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
			QString m_certificateNumbers;//֤����
			QString m_commodityName;
			QString m_commodityType;
			QString m_commodityUnit;//��λ
			float m_commodityPrice;//���ۻ�����
			float m_commodityJobPrice;//������
			float m_commodityGemPrice;//��ʯ�۸��ؽ�
			float m_commodityRoundNumbers;//��ָȦ��
			float m_commodityMainGemKarat;//����ʯ������
			float m_commodityAssistantGemKarat;//����ʯ������
			QString m_commodityGrade;//�ȼ�
			QString m_commodityColor;//��ɫ
			float m_commodityGoldWeight;//����
			float m_commodityGrossWeight;//������
			float m_commodityDiscounts;//��Ʒ�̶��ۿۣ�Ĭ��Ϊһ
      float m_commodityCost;//��Ʒ����
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
