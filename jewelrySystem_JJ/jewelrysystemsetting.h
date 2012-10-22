#ifndef JEWELRYSYSTEMSETTING_H
#define JEWELRYSYSTEMSETTING_H

#include <QDialog>
#include "ui_jewelrysystemsetting.h"

class jewelrySystemSetting : public QDialog
{
	Q_OBJECT

public:
	jewelrySystemSetting(QWidget *parent);
	~jewelrySystemSetting();

private:
	Ui::jewelrySystemSettingClass ui;

private slots:
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
};

#endif // JEWELRYSYSTEMSETTING_H
