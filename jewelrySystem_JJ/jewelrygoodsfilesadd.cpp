#include "jewelrygoodsfilesadd.h"
#include "CommodityInfo.h"
#include <QMessageBox>

jewelryGoodsFilesAdd::jewelryGoodsFilesAdd(QWidget *parent)
:QDialog()
{
	ui.setupUi(this);
	ui.lbCertificate->setVisible(false);
	ui.leCertificate->setVisible(false);
	ui.dbCommodityDiscounts->setValue(1);
}

jewelryGoodsFilesAdd::jewelryGoodsFilesAdd(QWidget *parent , const QString& commodityID)
:QDialog(parent)
{
	ui.setupUi(this);
	ui.lbCertificate->setVisible(false);
	ui.leCertificate->setVisible(false);
	m_id = commodityID;
	ui.leCommodityID->setReadOnly(true);
	ui.dbCommodityDiscounts->setValue(1);
	updateUIFromDatabase();
}

jewelryGoodsFilesAdd::~jewelryGoodsFilesAdd()
{

}

void jewelryGoodsFilesAdd::updateUIFromDatabase()
{
	CommodityInfo::CommodityInfoItem item = CommodityInfo::getInstance().getCommodityInfoItemByID(m_id);
	ui.leCommodityID->setText(item.m_id);
	ui.leCommodityName->setText(item.m_commodityName);
	ui.leCommodityType->setText(item.m_commodityType);

	int index = ui.cbCommodityUnit->findText(item.m_commodityUnit);
	if (index < 0)
	{
		index = 0;
	}
	ui.cbCommodityUnit->setCurrentIndex(index);

	ui.dbCommodityPrice->setValue(item.m_commodityPrice);
	ui.dbCommodityDiscounts->setValue(item.m_commodityDiscounts);
	ui.leCertificate->setText(item.m_certificateNumbers);
}

void jewelryGoodsFilesAdd::updateDataFromUI(CommodityInfo::CommodityInfoItem& item)
{
	item.m_id = ui.leCommodityID->text();
	item.m_commodityName = ui.leCommodityName->text();
	item.m_commodityType = ui.leCommodityType->text();
	item.m_commodityUnit = ui.cbCommodityUnit->currentText();
	item.m_commodityPrice = ui.dbCommodityPrice->value();
	item.m_commodityDiscounts = ui.dbCommodityDiscounts->value();
	item.m_certificateNumbers = ui.leCertificate->text();
}

void jewelryGoodsFilesAdd::updateDatabase()
{
	CommodityInfo& commodityInfo = CommodityInfo::getInstance();
	CommodityInfo::CommodityInfoItem item;
	updateDataFromUI(item);
	item.m_id = m_id;
	if (commodityInfo.updateDatabase(item))
	{
		accept();
		QMessageBox::information(this , tr("系统消息") ,tr("更新商品信息完成"));
	}
}

void jewelryGoodsFilesAdd::insertNewItem()
{
	CommodityInfo& commodityInfo = CommodityInfo::getInstance();
	CommodityInfo::CommodityInfoItem item;
	updateDataFromUI(item);
	if (commodityInfo.insertNewItem(item))
	{
		accept();
		QMessageBox::information(this , tr("系统消息") ,tr("新增商品信息完成"));
	}
}


void jewelryGoodsFilesAdd::on_pbOK_clicked()
{
	if (m_id.count())
	{
		updateDatabase();
	}
	else
		insertNewItem();
}

void jewelryGoodsFilesAdd::on_pbCancel_clicked()
{
	reject();
}

void jewelryGoodsFilesAdd::on_leCommodityID_textChanged(const QString &text)
{
	if (text.contains('\t'))
	{
		ui.leCommodityName->setFocus(Qt::MouseFocusReason);
	}
}

void jewelryGoodsFilesAdd::on_cbCommodityUnit_currentIndexChanged(QString text)
{
	if (text == tr("克"))
	{
		ui.lbCommodity->setText(tr("商品质量："));
		ui.lbCertificate->setVisible(false);
		ui.leCertificate->setVisible(false);
		ui.label_8->setText(text);
	}
	else if (text == tr("颗"))
	{
		ui.lbCommodity->setText(tr("商品单价："));
		ui.lbCertificate->setVisible(true);
		ui.leCertificate->setVisible(true);
		ui.label_8->setText(text);
	}
}