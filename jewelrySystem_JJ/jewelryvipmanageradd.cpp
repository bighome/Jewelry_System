#include "jewelryvipmanageradd.h"

jewelryVIPManagerAdd::jewelryVIPManagerAdd(QWidget *parent)
: QDialog(parent)
, m_vipID(0)
{
	ui.setupUi(this);
	setWindowTitle(tr("添加新会员"));
}

jewelryVIPManagerAdd::jewelryVIPManagerAdd(int vipID , QWidget *parent)
: QDialog(parent)
, m_vipID(vipID)
{
	ui.setupUi(this);
	setWindowTitle(tr("修改编号为%1的会员信息").arg(m_vipID));
	updateUIFromData(VIPManager::getInsance().getVIPManagerItemByID(m_vipID));
}

jewelryVIPManagerAdd::~jewelryVIPManagerAdd()
{

}

VIPManager::VIPManagerItem jewelryVIPManagerAdd::getVIPManagerItem()
{
	return m_VIPManagerItem;
}


void jewelryVIPManagerAdd::on_pbOK_clicked()
{
	updateDataFromUI();
	bool b = false;
	if (m_vipID)
	{
		m_VIPManagerItem.m_id = m_vipID;
		VIPManager::getInsance().getVIPManagerItemMap()[m_vipID] = m_VIPManagerItem;
		b = VIPManager::getInsance().updateItem(m_VIPManagerItem);
	}
	else
	{
		b = VIPManager::getInsance().addNewItem(m_VIPManagerItem);
		if(b)
			VIPManager::getInsance().updateDatabase();
	}
	if(b)
		accept();
}

void jewelryVIPManagerAdd::on_pbCancel_clicked()
{
	reject();
}

void jewelryVIPManagerAdd::updateDataFromUI()
{
	VIPManager::VIPManagerItem& managerItem = m_VIPManagerItem;
	managerItem.m_name = ui.leName->text();
	managerItem.m_gender = ui.cbGender->currentIndex();
	managerItem.m_paperworkID = ui.lePaperworkID->text();
	managerItem.m_phone = ui.lePhone->text();
	managerItem.m_address = ui.leAddress->text();
	managerItem.m_cardType = ui.cbCardType->currentText();
	managerItem.m_consumptionSum = ui.dbAmount->value();
	managerItem.m_integration = ui.sbIntegration->value();
}

void jewelryVIPManagerAdd::updateUIFromData(const VIPManager::VIPManagerItem& managerItem)
{
	ui.leName->setText(managerItem.m_name);
	ui.cbGender->setCurrentIndex(managerItem.m_gender);
	ui.lePaperworkID->setText(managerItem.m_paperworkID);
	ui.lePhone->setText(managerItem.m_phone);
	ui.leAddress->setText(managerItem.m_address);
	int index = ui.cbCardType->findText(managerItem.m_cardType);
	if (index < 0)
	{
		index = 0;
	}
	ui.cbCardType->setCurrentIndex(index);
	ui.dbAmount->setValue(managerItem.m_consumptionSum);
	ui.sbIntegration->setValue(managerItem.m_integration);
}