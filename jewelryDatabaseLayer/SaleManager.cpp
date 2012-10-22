#include "SaleManager.h"
#include "sqlquery.h"

SaleManager::SaleManager(void)
{
}

SaleManager::~SaleManager(void)
{
}

bool SaleManager::saled(const SaleItem& item)
{
	/*CREATE DEFINER = 'root'@'localhost' PROCEDURE `jewelrySales_Insert`(
	IN commodityID_p VARCHAR(40),
	IN saleCount_p INTEGER(11),
	IN staffID_p INTEGER(11),
	IN payment_p VARCHAR(20),
	IN warehouseID_p INTEGER(11),
	IN tradeDiscounts_p FLOAT(9,4),
	IN vipID_p INTEGER(11),
	IN amount_p FLOAT(9,4)
	)*/
	SqlQuery& query = SqlQuery::getInstance();
	if (item.m_commodityList.isEmpty())
	{
		return false;
	}
	QString dateTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmzzz");
	for (QList<SaleItem::CommodityItem>::const_iterator i = item.m_commodityList.constBegin() ; i != item.m_commodityList.constEnd() ; i++)
	{
		const SaleItem::CommodityItem& commodityItem = *i;
		QString sql = QString("call jewelrySales_Insert('%1',%2,%3,'%4',%5,%6,%7,%8,'%9')")
						.arg(commodityItem.m_commodityInfoItem.m_id).arg(commodityItem.m_saleCount).arg(item.m_staffItem.m_id)  
						.arg(item.m_payment).arg(commodityItem.m_warehouseItem.m_id).arg(item.m_tradeDiscounts , 0 , 'f' , 4)
						.arg(item.m_vipItem.m_id).arg(commodityItem.m_amount).arg(item.m_saleID);
		if (!query.query(sql))
		{
			return false;
		}
	}
	m_lastID = query.value(0 , 0).toString();
	QString fielName = query.fieldName(0);
	return true;
}
//
//QString SaleManager::lastID()
//{
//	return m_lastID;
//}
