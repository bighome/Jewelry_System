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
  QString m_certificateNumbers;//֤����
  QString m_commodityName;
  QString m_commodityType;
  QString m_commodityUnit;//��λ
  float m_commodityPrice;//���ۻ�����
  float m_commodityJobPrice;//������
  float m_commodityGemPrice;//��ʯ�۸��ؽ�
  float m_commodityRoundNumbers;//��ָȦ��
  float m_commodityMainGemKarat;//����ʯ������
  float m_commodityAssistantGemKarat;//����ʯ������
  QString m_commodityGrade;//�ȼ�
  QString m_commodityColor;//��ɫ
  float m_commodityGoldWeight;//����
  float m_commodityGrossWeight;//������
  float m_commodityDiscounts;//��Ʒ�̶��ۿۣ�Ĭ��Ϊһ
  float m_commodityCost;//��Ʒ����

  int m_ID;

private slots:
	void on_escPtn_clicked();
	void on_addPtn_clicked();
	void on_openExcelPtn_clicked();
	void runBat(const QModelIndex &);
};

#endif // JEWELRYPURCHASINGADDEXCEL_H
