#ifndef JEWELRYCODESETTINGS_H
#define JEWELRYCODESETTINGS_H

#include <QDialog>
#include "ui_jewelrycodesettings.h"

class jewelryCodeSettings : public QDialog
{
	Q_OBJECT

public:
	jewelryCodeSettings(QWidget *parent);
	~jewelryCodeSettings();
public:
	void init();
private slots:
	void slotsLableWidget(double);
	void slotsLableHeight(double);
	void slotsCodeX(double);
	void slotsCodeY(double);
	void slotsEnter();
private:
	Ui::jewelryCodeSettingsClass ui;
	double lableWidget;
	double lableHeight;
	double codeX;
	double codeY;
};

#endif // JEWELRYCODESETTINGS_H
