#ifndef JEWELRYSETTLEMENT_H
#define JEWELRYSETTLEMENT_H

#include <QWidget>
#include "ui_jewelrysettlement.h"

class jewelrySettlement : public QWidget
{
	Q_OBJECT

public:
	jewelrySettlement(QWidget *parent = 0);
	~jewelrySettlement();

private:
	Ui::jewelrySettlementClass ui;
};

#endif // JEWELRYSETTLEMENT_H
