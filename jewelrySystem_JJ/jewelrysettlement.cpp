#include "jewelrysettlement.h"

jewelrySettlement::jewelrySettlement(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("�鱦����ϵͳ"));
}

jewelrySettlement::~jewelrySettlement()
{

}
