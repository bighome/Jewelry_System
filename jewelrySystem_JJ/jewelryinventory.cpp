#include "jewelryinventory.h"

jewelryInventory::jewelryInventory(QWidget *parent)
	: QDialog()
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("�̵�"));
}

jewelryInventory::~jewelryInventory()
{

}
