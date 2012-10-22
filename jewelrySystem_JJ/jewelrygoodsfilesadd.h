#ifndef JEWELRYGOODSFILESADD_H
#define JEWELRYGOODSFILESADD_H

#include <QDialog>
#include "ui_jewelrygoodsfilesadd.h"
#include <QString>
#include "CommodityInfo.h"

class jewelryGoodsFilesAdd : public QDialog
{
	Q_OBJECT

public:
	jewelryGoodsFilesAdd(QWidget *parent);
	jewelryGoodsFilesAdd(QWidget *parent , const QString& commodityID);
	~jewelryGoodsFilesAdd();

private:
	void updateUIFromDatabase();
	void updateDataFromUI(CommodityInfo::CommodityInfoItem& item);
	void updateDatabase();
	void insertNewItem();

private:
	Ui::jewelryGoodsFilesAddClass ui;
	QString m_id;

private slots:
	void on_cbCommodityUnit_currentIndexChanged(QString);
	void on_leCommodityID_textChanged(const QString &);
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
};

#endif // JEWELRYGOODSFILESADD_H
