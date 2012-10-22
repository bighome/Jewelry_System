#ifndef JEWELRYWHOLEAMOUNT_H
#define JEWELRYWHOLEAMOUNT_H

#include <QDialog>
#include "ui_jewelrywholeamount.h"

class jewelryWholeAmount : public QDialog
{
	Q_OBJECT

public:
	jewelryWholeAmount(QWidget *parent = 0);
	~jewelryWholeAmount();
	float getAmount();

private:
	Ui::jewelryWholeAmountClass ui;

private slots:
	void on_pbCancle_clicked();
	void on_pbOK_clicked();

private:
	float m_amount;
};

#endif // JEWELRYWHOLEAMOUNT_H
