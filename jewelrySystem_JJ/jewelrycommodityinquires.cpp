#include "jewelrycommodityinquires.h"

jewelryCommodityInquires::jewelryCommodityInquires(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
	this->setWindowTitle(tr("�ֿ����"));
}

jewelryCommodityInquires::~jewelryCommodityInquires()
{

}
