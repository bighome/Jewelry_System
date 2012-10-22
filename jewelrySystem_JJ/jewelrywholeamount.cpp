#include "jewelrywholeamount.h"

jewelryWholeAmount::jewelryWholeAmount(QWidget *parent)
	: QDialog(parent)
	, m_amount(0)
{
	ui.setupUi(this);
	//this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("�鱦����ϵͳ"));
}

jewelryWholeAmount::~jewelryWholeAmount()
{

}

float jewelryWholeAmount::getAmount()
{
	return m_amount;
}

void jewelryWholeAmount::on_pbOK_clicked()
{
  m_amount = ui.doubleSpinBox->value();
	accept();
}

void jewelryWholeAmount::on_pbCancle_clicked()
{
	reject();
}