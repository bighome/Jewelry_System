#include "jewelrysingleproductdiscount.h"
#include "jewelrysales.h"
#include <QDebug>

jewelrySingleProductDiscount::jewelrySingleProductDiscount(QWidget *parent)
	: QDialog()
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("珠宝销售系统"));
  connect(ui.lineEdit_2, SIGNAL(returnPressed()), this, SLOT(slotsEnter()));
  connect(ui.lineEdit_2, SIGNAL(textChanged(const QString&)), this, SLOT(slotsPrice(const QString&)));
}

jewelrySingleProductDiscount::~jewelrySingleProductDiscount()
{

}
void jewelrySingleProductDiscount::setTableWidgetItem(QTableWidgetItem *item)
 {
   ui.lineEdit_3->setText(QString::number(ui.lineEdit->text().toFloat() * ui.lineEdit_2->text().toFloat(), 'f', 4));
   ui.lineEdit->setText(item->text());
   float price = ui.lineEdit->text().toFloat() * ui.lineEdit_2->text().toFloat();
   ui.lineEdit_3->setText(QString::number(price, 'f', 4));
 }
void jewelrySingleProductDiscount::slotsEnter()
{
  m_price = ui.lineEdit_3->text().toFloat();
 accept();
}
void jewelrySingleProductDiscount::slotsPrice(const QString& price)
{
  ui.lineEdit_3->setText(QString::number(ui.lineEdit->text().toFloat() * price.toFloat(), 'f', 4));
}
float jewelrySingleProductDiscount::getPrice()
{
  return m_price;
}
