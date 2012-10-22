#ifndef JEWELRYTRADINGPOPUP_H
#define JEWELRYTRADINGPOPUP_H

#include <QWidget>
#include "ui_jewelrytradingpopup.h"

class jewelryTradingPopup : public QWidget
{
	Q_OBJECT

public:
	jewelryTradingPopup(QWidget *parent = 0);
	~jewelryTradingPopup();

private:
	Ui::jewelryTradingPopupClass ui;
};

#endif // JEWELRYTRADINGPOPUP_H
