#include "jewelrysupplierinformationedit.h"

jewelrySupplierInformationEdit::jewelrySupplierInformationEdit(QWidget* parent)
: QDialog()
, m_update(false)
{
	ui.setupUi(this);
}

jewelrySupplierInformationEdit::jewelrySupplierInformationEdit(QWidget* parent , const SupplierManager::SupplierManagerItem& item)
: QDialog(parent)
, m_update(true)
{
	ui.setupUi(this);
	updateUIFromData(item);
	setWindowTitle(windowTitle() + QString(":¹©Ó¦ÉÌ±àºÅ%1").arg(item.m_id));
	m_id = item.m_id;
}

jewelrySupplierInformationEdit::~jewelrySupplierInformationEdit()
{

}

void jewelrySupplierInformationEdit::updateUIFromData(const SupplierManager::SupplierManagerItem& item)
{
	ui.leSupplierName->setText(item.m_supplierName);
	ui.leConnector->setText(item.m_contactor);
	ui.leAddress->setText(item.m_address);
	ui.leCodezip->setText(item.m_zipCode);
	ui.leEmail->setText(item.m_email);
	ui.lePhone->setText(item.m_phone);
	ui.leMobilePhone->setText(item.m_mobilePone);
	ui.leFax->setText(item.m_fax);
}

void jewelrySupplierInformationEdit::updateDataFromUI(SupplierManager::SupplierManagerItem& item)
{
	item.m_supplierName = ui.leSupplierName->text();
	item.m_contactor = ui.leConnector->text();
	item.m_address = ui.leAddress->text();
	item.m_zipCode = ui.leCodezip->text();
	item.m_email = ui.leEmail->text();
	item.m_phone = ui.lePhone->text();
	item.m_mobilePone = ui.leMobilePhone->text();
	item.m_fax = ui.leFax->text();
}

void jewelrySupplierInformationEdit::on_pbOK_clicked()
{
	SupplierManager::SupplierManagerItem item;
	updateDataFromUI(item);
	SupplierManager& supplierManager = SupplierManager::getInstance();
	bool b = false;
	if (m_update)
	{
		item.m_id = m_id;
		b = supplierManager.updateDatabase(item);
	}
	else
		b = supplierManager.insertNewItem(item);
	if(b)
		accept();
}

void jewelrySupplierInformationEdit::on_pbCancel_clicked()
{
	reject();
}