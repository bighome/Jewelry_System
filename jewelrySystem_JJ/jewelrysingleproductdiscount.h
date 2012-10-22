#ifndef JEWELRYSINGLEPRODUCTDISCOUNT_H
#define JEWELRYSINGLEPRODUCTDISCOUNT_H

#include <QDialog>
#include <QTableWidgetItem>
#include "ui_jewelrysingleproductdiscount.h"

class jewelrySingleProductDiscount : public QDialog
{
	Q_OBJECT

public:
	jewelrySingleProductDiscount(QWidget *parent = 0);
	~jewelrySingleProductDiscount();
  void setTableWidgetItem(QTableWidgetItem *item);
  float getPrice();
private slots:
  void slotsEnter();
  void slotsPrice(const QString&);
private:
	Ui::jewelrySingleProductDiscountClass ui;
  float m_price;
  float m_YPrice;
};

#endif // JEWELRYSINGLEPRODUCTDISCOUNT_H
