#include "jewelrytradediscount.h"

jewelryTradeDiscount::jewelryTradeDiscount(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("�鱦����ϵͳ"));
}

jewelryTradeDiscount::~jewelryTradeDiscount()
{

}
