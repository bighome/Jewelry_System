#ifndef JEWELRYCHANGEUNITPRICE_H
#define JEWELRYCHANGEUNITPRICE_H

#include <QWidget>
#include "ui_jewelrychangeunitprice.h"

class jewelryChangeUnitPrice : public QWidget
{
	Q_OBJECT

public:
	jewelryChangeUnitPrice(QWidget *parent = 0);
	~jewelryChangeUnitPrice();

private:
	Ui::jewelryChangeUnitPriceClass ui;
};

#endif // JEWELRYCHANGEUNITPRICE_H
