#include "jewelrypurchasingaddexcel.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include "jewelryexcel.h"
#include <QDebug>
#include <QProgressDialog>
#include "CommodityInfo.h"
#include "WarehouseManager.h"
#include "WarehouseInfo.h"
#include "StaffManager.h"
#include "SupplierManager.h"


QString jewelryPurchasingAddExcel::s_excelPath;
jewelryPurchasingAddExcel::jewelryPurchasingAddExcel(QWidget *parent)
	: QDialog(parent)
    ,m_ID(0)
{
	ui.setupUi(this);
  setWindowTitle(QString("批量入库"));
  init();
	//connect(ui.listWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(runBat(const QModelIndex &)));
}
jewelryPurchasingAddExcel::jewelryPurchasingAddExcel(QWidget *parent, const PurchaseManager::PurchaseManagerItem& item)
:QDialog(parent)
  {
    ui.setupUi(this);
    init();
    m_ID = item.m_id;
    setWindowTitle(windowTitle()+QString("采购编号").arg(m_ID));
  }
jewelryPurchasingAddExcel::~jewelryPurchasingAddExcel()
{

}
void jewelryPurchasingAddExcel::init()
{
  WarehouseInfo& warehouseInfo = WarehouseInfo::getInstance();
  warehouseInfo.updateDataFromDatabase();
  PurchaseManager& purchaseManager = PurchaseManager::getInstance();
  purchaseManager.updateDataFromDatabase();
  CommodityInfo& commodityInfo = CommodityInfo::getInstance();
  commodityInfo.updateDataFromDatabase();
  StaffManager& staffManager = StaffManager::getInstance();
  staffManager.updateDatabase();
  SupplierManager& supplierManager = SupplierManager::getInstance();
  supplierManager.updateDataFromDatabase();
  WarehouseManager& warehouseManager = WarehouseManager::getInstance();
  warehouseManager.updateFromDatabase();
  QMap<int , WarehouseInfo::WarehouseInfoItem>& warehouseInfoItemMap = warehouseInfo.getWarehouseInfoMap();
  for (QMap<int , WarehouseInfo::WarehouseInfoItem>::iterator i = warehouseInfoItemMap.begin() ; i != warehouseInfoItemMap.end() ; i++)
  {
    WarehouseInfo::WarehouseInfoItem& warehouseInfoItem = *i;
    ui.cbWarehouseName->addItem(warehouseInfoItem.m_warehouseInfo , warehouseInfoItem.m_id);
  }
  QMap<QString , CommodityInfo::CommodityInfoItem>& commodityInfoItemMap = commodityInfo.getCommodityInfoItemMap();
  //for (QMap<QString , CommodityInfo::CommodityInfoItem>::iterator i = commodityInfoItemMap.begin() ; i != commodityInfoItemMap.end() ; i++)
  //{
  //  CommodityInfo::CommodityInfoItem& item = *i;
  //  ui.cbCommodityName->addItem(item.m_commodityName , item.m_id);
  //}
  QMap<int , StaffManager::StaffManagerItem>& staffManagerItemMap = staffManager.getStaffManagerItemMap();
  for (QMap<int , StaffManager::StaffManagerItem>::iterator i = staffManagerItemMap.begin() ; i != staffManagerItemMap.end() ; i++)
  {
    StaffManager::StaffManagerItem& item = *i;
    ui.cbBuyerName->addItem(item.m_name , item.m_id);
  }
  QMap<int , SupplierManager::SupplierManagerItem>& supplierManagerItemMap = supplierManager.getSupplierManagerMap();
  for (QMap<int , SupplierManager::SupplierManagerItem>::iterator i = supplierManagerItemMap.begin() ; i != supplierManagerItemMap.end() ; i++)
  {
    SupplierManager::SupplierManagerItem& item = *i;
    ui.cbSupplierName->addItem(item.m_supplierName , item.m_id);
  }
}
void jewelryPurchasingAddExcel::updateUIFromData()
{
  PurchaseManager& purchaseManager = PurchaseManager::getInstance();
  PurchaseManager::PurchaseManagerItem item = purchaseManager.getPurchaseManagerItemByID(m_ID);
  int index = ui.cbWarehouseName->findData(item.m_warehouseID);
  if (index >= 0)
  {
    ui.cbWarehouseName->setCurrentIndex(index);
  }
  index = ui.cbSupplierName->findData(item.m_supplierID);
  if (index >= 0)
  {
    ui.cbSupplierName->setCurrentIndex(index);
  }
  index = ui.cbBuyerName->findData(item.m_staffID);
  if (index >= 0)
  {
    ui.cbBuyerName->setCurrentIndex(item.m_staffID);
  }
/*  index = ui.cbCommodityName->findData(item.m_commodityID);
  if (index >= 0)
  {
    ui.cbCommodityName->setCurrentIndex(index);
  }
  ui.spCommodityCount->setValue(item.m_commodityCount);
  ui.dbCommodityPrice->setValue(item.m_commodityPri);*/
}

void jewelryPurchasingAddExcel::on_openExcelPtn_clicked()
{
	find();
}
void jewelryPurchasingAddExcel::find()
{
	s_excelPath = QFileDialog::getOpenFileName(
		this,
		tr("打开EXCEL"),
		QDir::currentPath(),
		"97-2003工作簿 (*.xls);;工作薄(*.xlsx)");
	ui.lineEdit->setText(s_excelPath);
}
void jewelryPurchasingAddExcel::runBat(const QModelIndex & value)
{
	//m_excelPath =ui.lineEdit->text()+QString("\\")+value.data().toString();
}


void jewelryPurchasingAddExcel::on_addPtn_clicked()
{
	//导入EXCEL
	if (s_excelPath != NULL /*&& ui.cbSupplierName->currentText() != NULL && ui.cbWarehouseName->currentText() != NULL && ui.cbBuyerName->currentText() != NULL*/)
	{
		m_excelData = jewelryExcel::getInterFace().getExcelData(s_excelPath);
		this->setUItableWidget(m_excelData);
    this->insertData(m_excelData);
		qDebug()<< m_excelData;
	}
	else
	{
    QMessageBox::warning(this, "提示", "请把数据信息填写完整！");
		return;
	}

}
void jewelryPurchasingAddExcel::setUItableWidget(QHash<QString, QStringList> mapData)
{
	int temp_i = 0;
 
	QStringList headersNameList;
	QStringList dataList;
	for (QHash<QString, QStringList>::iterator i = mapData.begin(); i != mapData.end(); i++)
	{
		headersNameList << i.key();
		dataList = i.value();
		ui.tableWidget->setColumnCount(headersNameList.size());
		ui.tableWidget->setHorizontalHeaderLabels(headersNameList);
		ui.tableWidget->setRowCount(dataList.size());
		for (int j = 0; j < dataList.size(); j++)
		{
			ui.tableWidget->setItem(j, temp_i, new QTableWidgetItem(dataList[j]));
		}
		temp_i = temp_i + 1;
	}
}
void jewelryPurchasingAddExcel::insertData(QHash<QString, QStringList> mapData)
{
 CommodityInfo& commodityInfo = CommodityInfo::getInstance();
 //commodityInfo.updateDataFromDatabase();
 CommodityInfo::CommodityInfoItem item;

 PurchaseManager& purchaseManager = PurchaseManager::getInstance();
 PurchaseManager::PurchaseManagerItem items;

 bool tempBool;
  QProgressDialog *progressDlg=new QProgressDialog;  
  progressDlg->setWindowModality(Qt::WindowModal);  
  progressDlg->setMinimumDuration(5);  
  progressDlg->setWindowTitle("请等待");  
  progressDlg->setLabelText("正在将数据导入数据库......");  
  progressDlg->setCancelButtonText("取消");  

  int size;
  for (QHash<QString, QStringList>::iterator k = mapData.begin(); k!= mapData.end(); k++)
  {
         size = k.value().size();
         break;
  }
    progressDlg->setRange(0,size);  
    int tempNumber = 0;
    int tempNumbers = 0;
    for (int j = 0; j <size; j++)
    {
      for (QHash<QString, QStringList>::iterator k = mapData.begin(); k!= mapData.end(); k++)
      {
        if (k.key() == "编号")
        {
          item.m_id = k.value().at(tempNumbers);
          items.m_commodityID = k.value().at(tempNumbers);
          qDebug() << m_id;
        }
        else if (k.key() == "证书编号")
        {
            item.m_certificateNumbers = k.value().at(tempNumbers);
          qDebug() <<  item.m_certificateNumbers;
        }
        else if (k.key() == "单位")
        {
           item.m_commodityUnit = k.value().at(tempNumbers);
          qDebug() <<  item.m_commodityUnit;
        }
        else if (k.key() == "品名")
        {
           item.m_commodityName = k.value().at(tempNumbers);
          qDebug() <<  item.m_commodityName;
        }
        else if (k.key() == "类别")
        {
            item.m_commodityType = k.value().at(tempNumbers);
           qDebug() <<  item.m_commodityType;
        }
        else if (k.key() == "价格")
        {
           item.m_commodityPrice = k.value().at(tempNumbers).toFloat();
            items.m_commodityPrice = k.value().at(tempNumbers).toFloat();
          qDebug() <<  item.m_commodityPrice;
        }
        else if (k.key() == "宝石价格")
        {
         item.m_commodityGemPrice = k.value().at(tempNumbers).toFloat();
         qDebug() <<  item.m_commodityGemPrice;
        }
        else if (k.key() == "工费")
        {
           item.m_commodityJobPrice = k.value().at(tempNumbers).toFloat();
          qDebug() <<  item.m_commodityJobPrice;
        }
        else if (k.key() == "圈号")
        {
           item.m_commodityRoundNumbers = k.value().at(tempNumbers).toFloat();
          qDebug() <<  item.m_commodityRoundNumbers;
        }
        else if (k.key() == "主石克拉数")
        {
          item.m_commodityMainGemKarat = k.value().at(tempNumbers).toFloat();
         qDebug() <<  item.m_commodityMainGemKarat;
        }
        else if (k.key() == "副石克拉数")
        {
           item.m_commodityAssistantGemKarat = k.value().at(tempNumbers).toFloat();
          qDebug() <<  item.m_commodityAssistantGemKarat;
        }
        else if (k.key() == "等级")
        {
          item.m_commodityGrade = k.value().at(tempNumbers);
         qDebug() <<  item.m_commodityGrade;
        }
        else if (k.key() == "颜色")
        {
          item.m_commodityColor = k.value().at(tempNumbers);
         qDebug() <<  item.m_commodityColor;
        }
        else if (k.key() == "金重")
        {
           item.m_commodityGoldWeight = k.value().at(tempNumbers).toFloat();
          qDebug() <<  item.m_commodityGoldWeight;
        }
        else if (k.key() == "总质量")
        {
          item.m_commodityGrossWeight = k.value().at(tempNumbers).toFloat();
         qDebug() <<  item.m_commodityGrossWeight;
        }
        else if (k.key() == "进货单价")
        {
            item.m_commodityCost = k.value().at(tempNumbers).toFloat();
           qDebug() <<  item.m_commodityCost;
        }
        else if (k.key() == "折扣")
        {
          item.m_commodityDiscounts = k.value().at(tempNumbers).toFloat();
         qDebug() <<  item.m_commodityDiscounts;
        }
        else if (k.key() == "库存")
        {
              items.m_commodityCount = k.value().at(tempNumbers).toInt();
        }
        tempNumber = tempNumber+1;
        if (tempNumber == mapData.size())
        {
          tempNumber =0;
          tempNumbers = tempNumbers +1;
          updateDataFromUI(items);
          if (!CommodityInfo::getInstance().insertNewItemEXCEL(item))
          {
            QMessageBox::critical(this, "系统消息", "数据导入失败");
            tempBool = false;
            return;
          }
          else
          {
            if (!purchaseManager.insertNewItem(items))
            {
              QMessageBox::critical(this, "系统消息", "数据导入失败");
            }
            tempBool = true;
          }
        }
      }
      progressDlg->setValue(j+1);  
    }
    if (tempBool)
    {
      QMessageBox::information(this, "系统消息","数据导入成功");
    }
}
void jewelryPurchasingAddExcel::on_escPtn_clicked()
{
	this->	close();
}
void jewelryPurchasingAddExcel::updateDataFromUI(PurchaseManager::PurchaseManagerItem& item)
{
  item.m_supplierID = ui.cbSupplierName->itemData(ui.cbSupplierName->currentIndex()).toInt();
  item.m_warehouseID = ui.cbWarehouseName->itemData(ui.cbWarehouseName->currentIndex()).toInt();
  item.m_staffID = ui.cbBuyerName->itemData(ui.cbBuyerName->currentIndex()).toInt();
}