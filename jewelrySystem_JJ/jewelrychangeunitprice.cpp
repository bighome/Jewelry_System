#include "jewelrychangeunitprice.h"

jewelryChangeUnitPrice::jewelryChangeUnitPrice(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("�鱦����ϵͳ"));
}

jewelryChangeUnitPrice::~jewelryChangeUnitPrice()
{

}
