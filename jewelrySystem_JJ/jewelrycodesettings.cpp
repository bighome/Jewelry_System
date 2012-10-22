#include "jewelrycodesettings.h"

jewelryCodeSettings::jewelryCodeSettings(QWidget *parent)
	: QDialog()
{
	ui.setupUi(this);
	init();
}

jewelryCodeSettings::~jewelryCodeSettings()
{

}
void jewelryCodeSettings::init()
{
	this->setWindowTitle(tr("´òÓ¡±êÇ©"));
	connect(ui.labelWidgetSB, SIGNAL(valueChanged ( double)), this, SLOT(slotsLableWidget(double)));
	connect(ui.lableHeightSB, SIGNAL(valueChanged ( double)), this, SLOT(slotsLableHeight(double)));
	connect(ui.codeXSB, SIGNAL(valueChanged ( double)), this, SLOT(slotsCodeX(double)));
	connect(ui.codeYSB, SIGNAL(valueChanged ( double)), this, SLOT(slotsCodeY(double)));
	connect(ui.enter, SIGNAL(clicked()), this, SLOT(slotsEnter()));
	connect(ui.exit, SIGNAL(clicked()),this, SLOT(close()));

	lableWidget = ui.labelWidgetSB->value();
	lableHeight = ui.lableHeightSB->value();
	codeX = ui.codeXSB->value();
	codeY = ui.codeYSB->value();
	ui.printfWidget->setMaximumSize(QSize(lableWidget, lableHeight));
	ui.codeWidget->move(codeX,codeY);
}
void jewelryCodeSettings::slotsLableWidget(double w)
{
	lableWidget = w;
	ui.printfWidget->setMaximumSize(QSize(lableWidget, lableHeight));
	ui.printfWidget->update();
}
void jewelryCodeSettings::slotsLableHeight(double h)
{
	lableHeight = h;
	ui.printfWidget->setMaximumSize(QSize(lableWidget, lableHeight));
	ui.printfWidget->update();
}
void jewelryCodeSettings::slotsCodeX(double x)
{
	codeX = x;
	ui.codeWidget->move(codeX, codeY);
	ui.codeWidget->update();
}
void jewelryCodeSettings::slotsCodeY(double y)
{
	codeY = y;
	ui.codeWidget->move(codeX, codeY);
	ui.codeWidget->update();
}
void jewelryCodeSettings::slotsEnter()
{
	this->close();
}