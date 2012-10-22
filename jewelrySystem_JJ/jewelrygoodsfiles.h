#ifndef JEWELRYGOODSFILES_H
#define JEWELRYGOODSFILES_H

#include <QDialog>
#include "ui_jewelrygoodsfiles.h"

class jewelryGoodsFiles : public QDialog
{
	Q_OBJECT
	enum TABLEITEM
	{
		TABLEITEM_id,
		TABLEITEM_commodityName,
		TABLEITEM_commodityType,
		TABLEITEM_commodityUnit,
		TABLEITEM_commodityPrice,
		TABLEITEM_commodityDiscounts
	};
public:
	jewelryGoodsFiles(QWidget *parent);
	~jewelryGoodsFiles();

private:
	void updateUIFromDatabase();

private:
	Ui::jewelryGoodsFilesClass ui;

private slots:
	void on_pbDelete_clicked();
	void on_pbQuit_clicked();
	void on_pbEdit_clicked();
	void on_pbAdd_clicked();
};

#endif // JEWELRYGOODSFILES_H
