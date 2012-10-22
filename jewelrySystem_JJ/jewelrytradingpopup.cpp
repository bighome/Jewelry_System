#include "jewelrytradingpopup.h"

jewelryTradingPopup::jewelryTradingPopup(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("珠宝销售系统"));
}

jewelryTradingPopup::~jewelryTradingPopup()
{

}
