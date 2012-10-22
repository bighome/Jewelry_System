#ifndef JEWELRYPURCHASINGADDEXCEL_H
#define JEWELRYPURCHASINGADDEXCEL_H

#include <QDialog>
#include "ui_jewelrypurchasingaddexcel.h"
#include "PurchaseManager.h"

class jewelryPurchasingAddExcel : public QDialog
{
	Q_OBJECT

public:
	jewelryPurchasingAddExcel(QWidget *parent);
  jewelryPurchasingAddExcel(QWidget *parent, const PurchaseManager::PurchaseManagerItem& item);
	~jewelryPurchasingAddExcel();

private:
	Ui::jewelryPurchasingAddExcelClass ui;
  void init();
	void find();
	QHash<QString, QStringList> m_excelData;
	void setUItableWidget(QHash<QString, QStringList> mapData);
  void insertData(QHash<QString, QStringList> mapData);
  	void updateDataFromUI(PurchaseManager::PurchaseManagerItem& item);
  void updateUIFromData();


private:
  static QString s_excelPath;
  QString m_id;
  QString m_certificateNumbers;//证书编号
  QString m_commodityName;
  QString m_commodityType;
  QString m_commodityUnit;//单位
  float m_commodityPrice;//单价或质量
  float m_commodityJobPrice;//工本费
  float m_commodityGemPrice;//宝石价格（素金）
  float m_commodityRoundNumbers;//戒指圈号
  float m_commodityMainGemKarat;//主宝石克拉数
  float m_commodityAssistantGemKarat;//副宝石克拉数
  QString m_commodityGrade;//等级
  QString m_commodityColor;//颜色
  float m_commodityGoldWeight;//金重
  float m_commodityGrossWeight;//总质量
  float m_commodityDiscounts;//商品固定折扣，默认为一
  float m_commodityCost;//商品进价

  int m_ID;

private slots:
	void on_escPtn_clicked();
	void on_addPtn_clicked();
	void on_openExcelPtn_clicked();
	void runBat(const QModelIndex &);
};

#endif // JEWELRYPURCHASINGADDEXCEL_H
