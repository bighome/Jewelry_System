#ifndef JEWELRYTRADEDISCOUNT_H
#define JEWELRYTRADEDISCOUNT_H

#include <QWidget>
#include "ui_jewelrytradediscount.h"

class jewelryTradeDiscount : public QWidget
{
	Q_OBJECT

public:
	jewelryTradeDiscount(QWidget *parent = 0);
	~jewelryTradeDiscount();

private:
	Ui::jewelryTradeDiscountClass ui;
};

#endif // JEWELRYTRADEDISCOUNT_H
