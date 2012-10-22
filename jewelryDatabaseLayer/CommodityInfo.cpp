#include "CommodityInfo.h"
#include "sqlquery.h"
#include <QDebug>

CommodityInfo* CommodityInfo::s_instace = NULL;

CommodityInfo::CommodityInfo(void)
{
	s_instace = this;
	updateDataFromDatabase();
}

CommodityInfo::~CommodityInfo(void)
{
}

void CommodityInfo::updateDataFromDatabase()
{

	SqlQuery& query = SqlQuery::getInstance();
	if(query.query("call selectCommodityInfo"))
	{
		m_idMapItem.clear();
    int tepm = query.rowCount();
    int temp = query.columnCount();
		for (int row = 0 ; row < query.rowCount() ; row++)
		{
			CommodityInfoItem item;
			for (int column = 0 ; column < query.columnCount() ; column++)
			{
				QVariant v = query.value(row , column);
				const QString field = query.fieldName(column);
        qDebug()<< field;
				if (field == "id")
				{
					item.m_id = v.toString();
				}
				else if (field == "commodityType")
				{
					item.m_commodityType = v.toString();
				}
				else if (field == "commodityName")
				{
					item.m_commodityName = v.toString();
				}
				else if (field == "commodityUnit")
				{
					item.m_commodityUnit = v.toString();
				}
				else if (field == "commodityPrice")
				{
					item.m_commodityPrice = v.toFloat();
				}
				else if (field == "commodityDiscounts")
				{
					item.m_commodityDiscounts = v.toFloat();
				}
				else if (field == "commodityJobPrice")
				{
					item.m_commodityJobPrice = v.toFloat();
				}
				else if (field == "commodityGemPrice")
				{
					item.m_commodityGemPrice = v.toFloat();
				}
				else if (field == "commodityRoundNumbers")
				{
					item.m_commodityRoundNumbers  = v.toFloat();
				}
				else if (field == "commodityMainGemKarat")
				{
					item.m_commodityMainGemKarat = v.toFloat();
				}
				else if (field == "commodityAssistantGemKarat")
				{
					item.m_commodityAssistantGemKarat = v.toFloat();
				}
				else if (field == "commodityGrade")
				{
					item.m_commodityGrade = v.toString();
				}
				else if (field == "commodityColor")
				{
					item.m_commodityColor  = v.toString();
				}
				else if (field == "commodityGoldWeight")
				{
					item.m_commodityGoldWeight = v.toFloat();
				}
				else if (field == "commodityGrossWeight")
				{
					item.m_commodityGrossWeight = v.toFloat();
				}
				else if (field == "commodityCertificateID")
				{
					item.m_certificateNumbers = v.toString();
				}
        else if (field =="commodityCost")
        {
          item.m_commodityCost = v.toFloat();
        }
				else if (field == "mark")
				{
					item.m_mark = v.toString();
				}
			}
			m_idMapItem[item.m_id] = item;
		}
	}
}

CommodityInfo::CommodityInfoItem CommodityInfo::getCommodityInfoItemByID(QString id)
{
	CommodityInfo::CommodityInfoItem item;
	if (m_idMapItem.contains(id))
	{
		item = m_idMapItem[id];
	}
	return item;
}

QMap<QString , CommodityInfo::CommodityInfoItem>& CommodityInfo::getCommodityInfoItemMap()
{
	return m_idMapItem;
}

CommodityInfo& CommodityInfo::getInstance()
{
	if (!s_instace)
	{
		s_instace = new CommodityInfo;
	}
	return *s_instace;
}

bool CommodityInfo::updateDatabase(const CommodityInfo::CommodityInfoItem& item)
{
	/*CREATE DEFINER = 'root'@'localhost' PROCEDURE `updateCommodityInfo`(
	IN id_p VARCHAR(40),
	IN commodityType_p VARCHAR(40),
	IN commodityName_p VARCHAR(40),
	IN commodityUnit_p VARCHAR(40),
	IN commodityPrice_p FLOAT(9,4),
	IN commodityDiscounts_p FLOAT(9,4)
	)*/
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call updateCommodityInfo('%1','%2','%3','%4',%5,%6)").arg(item.m_id).arg(item.m_commodityType)
					.arg(item.m_commodityName).arg(item.m_commodityUnit).arg(item.m_commodityPrice , 0 , 'f' , 4).arg(item.m_commodityDiscounts);
	if (query.query(sql))
	{
		m_idMapItem[item.m_id] = item;
		return true;
	}
	return false;
}

bool CommodityInfo::insertNewItem(const CommodityInfo::CommodityInfoItem& item)
{
	/*CREATE DEFINER = 'root'@'localhost' PROCEDURE `insertCommodityInfo`(
	IN commodityType_p VARCHAR(20),
	IN commodityName_p VARCHAR(20),
	IN commodityUnit_p VARCHAR(20),
	IN commodityPrice_p FLOAT(9,4),
	IN commodityDiscounts_p FLOAT(9,4)
	)*/
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call insertCommodityInfo('%1','%2','%3','%4',%5,%6)").arg(item.m_id).arg(item.m_commodityType)
		.arg(item.m_commodityName).arg(item.m_commodityUnit).arg(item.m_commodityPrice , 0 , 'f' , 4).arg(item.m_commodityDiscounts);
	if (query.query(sql))
	{
		updateDataFromDatabase();
		return true;
	}
	return false;
}
bool CommodityInfo::insertNewItemEXCEL(const CommodityInfo::CommodityInfoItem& item)
{	
		SqlQuery& query = SqlQuery::getInstance();
		QString sql = QString("call insertCommodityInfo('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%17')")
      .arg(item.m_id)
      .arg(item.m_commodityType)
      .arg(item.m_commodityName)
      .arg(item.m_commodityUnit)
      .arg(item.m_commodityPrice)
      .arg(item.m_commodityDiscounts)
      .arg(item.m_commodityJobPrice)
      .arg(item.m_commodityGemPrice)
      .arg(item.m_commodityRoundNumbers)
      .arg(item.m_commodityMainGemKarat)
      .arg(item.m_commodityAssistantGemKarat)
      .arg(item.m_commodityGrade)
      .arg(item.m_commodityColor)
      .arg(item.m_commodityGoldWeight)
      .arg(item.m_commodityGrossWeight)
      .arg(item.m_commodityCost)
      .arg(item.m_certificateNumbers);
		if (query.query(sql))
		{
			updateDataFromDatabase();
			return true;
		}
		return false;
}
bool CommodityInfo::deleteItem(const QString& id)
{
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call deleteCommodityInfo('%1')").arg(id);
	if (query.query(sql))
	{
		m_idMapItem.remove(id);
		return true;
	}
	return false;
}

