#include "jewelrytradingpopup.h"

jewelryTradingPopup::jewelryTradingPopup(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("�鱦����ϵͳ"));
}

jewelryTradingPopup::~jewelryTradingPopup()
{

}
