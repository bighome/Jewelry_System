#include "jewelrysales.h"
#include "jewelrysingleproductdiscount.h"
#include "jewelrytradediscount.h"
#include "jewelrychangeunitprice.h"
#include "jewelrycommodityinquires.h"
#include "jewelryVIPManagerDialog.h"
#include "jewelrysettlement.h"
#include "jewelrytradingpopup.h"
#include "jewelrywholeamount.h"
#include "jewelrylogin.h"
#include "sqlquery.h"
#include "SystemSettings.h"
#include "staffmanager.h"
#include "jewelurprintf.h"
#include "jewelrygoodsfiles.h"
#include <Windows.h>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>

bool jewelrySales::s_tableWidgetBool = false;
int jewelrySales::s_tableWidgetItemRows;
QTableWidgetItem* jewelrySales::m_tableWidgetItem;
jewelrySales::jewelrySales(QWidget *parent)
	: QDialog()
	, m_singleProductDiscount(NULL)
	, m_tradeDiscount(NULL)
	, m_changeUnitPrice(NULL)
	, m_commodityInquires(NULL)
	, m_VIPManagerDialog(NULL)
	, m_settlement(NULL)
	, m_tradingPopup(NULL)
	, m_wholeAmount(NULL)
  ,m_goodsGiles(NULL)
	, m_login(NULL)
{
	ui.setupUi(this);
	init();
}

jewelrySales::~jewelrySales()
{

}
void jewelrySales::init()
{
	this->showFullScreen();
	connect(ui.pushButton_11, SIGNAL(clicked()), this, SLOT(slotswholeAmount()));
	connect(ui.pushButton_12, SIGNAL(clicked()), this, SLOT(slotsLogin()));
	connect(ui.pushButton_14, SIGNAL(clicked()), this, SLOT(slotleClose()));
  connect(ui.tableWidget, SIGNAL(itemPressed ( QTableWidgetItem *)), this, SLOT(slotsTableWidgetItem(QTableWidgetItem *)));
	//connect(ui.leBarcode , SIGNAL(textEdited(const QString &)) , this , SLOT(slotleBarcodeTextEdited(const QString &)));
	connect(ui.leBarcode , SIGNAL(returnPressed()) , this , SLOT(slotleBarcodeReturnPressed()));
	connect(ui.lePaidUp , SIGNAL(returnPressed()) , this , SLOT(slotlePaidUpReturnPressed()));
	connect(ui.lePaidUp , SIGNAL(textChanged(const QString&)) , this , SLOT(slotlePaidUpTextChanged(const QString&)));

	ui.leBarcode->setFocus(Qt::MouseFocusReason);
	updateSalersInfo();
}
void jewelrySales::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_F1:
		ui.leBarcode->setFocus(Qt::MouseFocusReason);
		break;
	case Qt::Key_F2:
		ui.lePaidUp->setFocus(Qt::MouseFocusReason);
		break;
	case Qt::Key_F3:
		{
      oneDiscount(s_tableWidgetItemRows);
		}
		break;
	case Qt::Key_F4:
		{
			//if (m_tradeDiscount == NULL)
			//{
			//	m_tradeDiscount  = new jewelryTradeDiscount;
			//}
			//m_tradeDiscount->show();
      ui.dbTradeDiscounts->setFocus(Qt::MouseFocusReason);
		}
		break;
	case Qt::Key_F5:
		{
      if (s_tableWidgetBool)
      {
        s_tableWidgetBool = false;
        ui.tableWidget->removeRow(s_tableWidgetItemRows);
      }
      else
      {
        QMessageBox::critical(this, tr("ϵͳ��Ϣ"), tr("��ѡ����Ʒ"),QMessageBox::Yes);
      }
         calculateAmountMoney();
		}
		break;
	case Qt::Key_F6:
		break;
	case Qt::Key_F7:
		{

		}
		break;
	case Qt::Key_F8:
		{
			if (m_goodsGiles == NULL)
			{
				m_goodsGiles = new jewelryGoodsFiles(this);
			}
			m_goodsGiles->exec();
		}
		break;
	case Qt::Key_F9:
		{
			if (m_VIPManagerDialog == NULL)
			{
				m_VIPManagerDialog = new jewelryVIPManagerDialog;
			}
			if(m_VIPManagerDialog->exec())
			{
				m_vipManagerItem = m_VIPManagerDialog->getCurrentVIPItem();
				ui.leVIPCardNo->setText(m_vipManagerItem.m_name);
			}
		}
		break;
	case Qt::Key_F11:
		{
			//if (m_tradingPopup == NULL)
			//{
			//	m_tradingPopup = new jewelryTradingPopup;
			//}
			//m_tradingPopup->show();
		}
		break;
	case Qt::Key_Escape:
		clearAll();
		break;
	//case Qt::Key_Enter:
	//	{
	//		if (m_settlement)
	//		{
	//			m_settlement = new jewelrySettlement;
	//		}
	//		m_settlement->show();
	//	}
	//	break;
	}
}
void jewelrySales::slotswholeAmount()
{
	if (m_wholeAmount == NULL)
	{
		m_wholeAmount = new jewelryWholeAmount(this);
	}
  if (m_wholeAmount->exec())
  {
    ui.leAmount->setText(QString::number(m_wholeAmount->getAmount() , 'f' , 4));
  }
}
void jewelrySales::slotsLogin()
{
	if (m_login == NULL)
	{
		m_login = new jewelryLogin(this);
	}
	m_login->exec();
}

void jewelrySales::slotScanningBarcode(QString barcodeID)
{
	CommodityInfo::CommodityInfoItem item = CommodityInfo::getInstance().getCommodityInfoItemByID(barcodeID);
	addNewCommudity(item);
}

void jewelrySales::addNewCommudity(const CommodityInfo::CommodityInfoItem& item)
{
	if (item.m_id > 0)
	{
		int rowCount = ui.tableWidget->rowCount();
		int row = 0;
		for (; row <rowCount ; row++)
		{
			const QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_ID);
			if (tableWidgetItem && tableWidgetItem->text() == item.m_id)
			{
				QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_COUNT);//shuliang
				int commodityCount = tableWidgetItem->text().toInt() + 1;
				tableWidgetItem->setText(QString::number(commodityCount));

				tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_AMOUNT );//�ܼ�
				tableWidgetItem->setText(QString::number(ui.tableWidget->item(row , TABLEHEADER_PRICE)->text().toFloat() * commodityCount , 'f' , 4));
				//ui.tableWidget->setItem(rowCount , TABLEHEADER_AMOUNT , tableWidgetItem);

				tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_STOCKNUM);
				if (tableWidgetItem && tableWidgetItem->text() != tr("�޿����Ϣ"))
				{
					tableWidgetItem->setText(QString::number(tableWidgetItem->text().toInt() - 1));
				}
				break;
			}
		}
		if (row == rowCount)
		{
			ui.tableWidget->setRowCount(rowCount + 1);
			int column = 0;
			{//id0
				QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(item.m_id);
				ui.tableWidget->setItem(rowCount , TABLEHEADER_ID , tableWidgetItem);
			}
      {//֤����
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(item.m_certificateNumbers);
        ui.tableWidget->setItem(rowCount, TABLEHEADER_CERTIFICATEID, tableWidgetItem);
      }	

      {//��ʯ�۸�
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(item.m_commodityGemPrice));
        ui.tableWidget->setItem(rowCount , TABLEHEADER_GEMPRICE , tableWidgetItem);
      }
      {//����
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(item.m_commodityJobPrice));
        ui.tableWidget->setItem(rowCount , TABLEHEADER_JOBPRICE , tableWidgetItem);
      }
      {//Ȧ��
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(item.m_commodityRoundNumbers));
        ui.tableWidget->setItem(rowCount , TABLEHEADER_ROUNDNUMBERS , tableWidgetItem);
      }
      {//��ʯ������
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(item.m_commodityMainGemKarat));
        ui.tableWidget->setItem(rowCount , TABLEHEADER_MAINGEMKARAT , tableWidgetItem);
      }
      {//��ʯ������
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(item.m_commodityAssistantGemKarat));
        ui.tableWidget->setItem(rowCount , TABLEHEADER_ASSISTANTGEMKARAT , tableWidgetItem);
      }
      {//�ȼ�
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(item.m_commodityGrade);
        ui.tableWidget->setItem(rowCount , TABLEHEADER_GRADE , tableWidgetItem);
      }
      {//��ɫ
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(item.m_commodityColor);
        ui.tableWidget->setItem(rowCount , TABLEHEADER_COLOR , tableWidgetItem);
      }
      {//����
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(item.m_commodityGoldWeight));
        ui.tableWidget->setItem(rowCount , TABLEHEADER_GOLDWEIGHT , tableWidgetItem);
      }
      {//������
        QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(item.m_commodityGrossWeight));
        ui.tableWidget->setItem(rowCount , TABLEHEADER_GROSSWEIGHT , tableWidgetItem);
      }

      {//unit
				QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(item.m_commodityUnit);
				ui.tableWidget->setItem(rowCount , TABLEHEADER_UNIT , tableWidgetItem);
			}
			{//name
				QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(item.m_commodityName);
				ui.tableWidget->setItem(rowCount , TABLEHEADER_NAME , tableWidgetItem);
			}
			{//count3
				QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(1));
				ui.tableWidget->setItem(rowCount , TABLEHEADER_COUNT , tableWidgetItem);
			}
			{//Discounts4
				QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(item.m_commodityDiscounts , 'f' , 4));
				ui.tableWidget->setItem(rowCount , TABLEHEADER_DISCOUNTS , tableWidgetItem);
			}
			{//Price5
				double tem = item.m_commodityPrice;
				if (item.m_commodityUnit == tr("��"))
				{
					tem *= SystemSettings::getInstance().getGoldPrice();
				}
				QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(tem , 'f' , 4));
				ui.tableWidget->setItem(rowCount , TABLEHEADER_PRICE , tableWidgetItem);
			}
			{//amount6
				float tem = ui.tableWidget->item(row , TABLEHEADER_PRICE)->text().toFloat() * item.m_commodityDiscounts;
				QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(QString::number(tem , 'f' , 4));
				ui.tableWidget->setItem(rowCount , TABLEHEADER_AMOUNT , tableWidgetItem);
			}
			{//type7
				QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(item.m_commodityType);
				ui.tableWidget->setItem(rowCount , TABLEHEADER_TYPE , tableWidgetItem);
			}
			{//stockNum8
				WarehouseManager& warehouseManager = WarehouseManager::getInstance();
				StaffManager& staffManager = StaffManager::getInstance();
				StaffManager::StaffManagerItem staffManagerItem = staffManager.getStaffManagerItemByID(SystemSettings::getInstance().getCurrentStaffID());
				WarehouseManager::WarehouseManagerItem warehouseManagerItem = warehouseManager.getWarehouseManagerItem(staffManagerItem.m_warehouseID , item.m_id);
				QString str;
				if (warehouseManagerItem.m_id > 0)
				{
					str = QString::number(warehouseManagerItem.m_commodityCount - 1);
				}
				else
				{
					str = tr("�޿����Ϣ");
					QMessageBox::information(this , tr("ϵͳ��Ϣ") , str);
					ui.tableWidget->setRowCount(rowCount - 1);
				}
				ui.tableWidget->setItem( rowCount , TABLEHEADER_STOCKNUM , new QTableWidgetItem(str) );
			}
		}
		calculateAmountMoney();
	}
	else
	{
		QMessageBox::information(this , tr("ϵͳ��Ϣ") , tr("���޴���Ʒ����Ʒ���Ϊ��%1").arg(item.m_id));
	}
}

void jewelrySales::calculateAmountMoney()
{
  ui.tableWidget->update();
	int rowCount = ui.tableWidget->rowCount();
	float amount = 0.f;
	for (int i = 0 ; i <rowCount ; i++)
	{
		QTableWidgetItem* amountItem = ui.tableWidget->item(i , TABLEHEADER_AMOUNT);//�ܼ�
		amount += amountItem->text().toFloat();
	}
	ui.leAmount->setText(QString::number(amount , 'f' , 4));
}

void jewelrySales::slotleBarcodeReturnPressed()
{
	QString text = ui.leBarcode->text();
	if (text.count())
	{
		slotScanningBarcode(text);
		ui.leBarcode->clear();
	}
	else
		ui.lePaidUp->setFocus(Qt::MouseFocusReason);
}

void jewelrySales::slotlePaidUpReturnPressed()
{
	completionTransaction();
}

void jewelrySales::showEvent(QShowEvent *event)
{
	ui.leBarcode->setFocus(Qt::MouseFocusReason);
}

void jewelrySales::slotlePaidUpTextChanged(const QString& text)
{
	float amount = ui.leAmount->text().toFloat();
	float paidUp = text.toFloat();
	float tem = paidUp - amount;
	ui.leChange->setText(QString::number(tem , 'f' , 4));
}

void jewelrySales::clearAll()
{
	ui.lePaidUp->clear();
	ui.leBarcode->setFocus(Qt::MouseFocusReason);
	ui.leChange->clear();
	ui.tableWidget->setRowCount(0);
	ui.leAmount->clear();
	ui.leVIPCardNo->clear();
}

void jewelrySales::updateSalersInfo()
{
	QMap<int , StaffManager::StaffManagerItem>& staffManagerItemMap = StaffManager::getInstance().getStaffManagerItemMap();
	for (QMap<int , StaffManager::StaffManagerItem>::iterator i = staffManagerItemMap.begin() ; i != staffManagerItemMap.end() ; i++)
	{
		StaffManager::StaffManagerItem& item = *i;
		ui.cbSaler->addItem(item.m_name , item.m_id);
	}
}

void jewelrySales::updateWarehouseInfo()
{
	//ui.leStockNum->setText(warehouseManager.getWarehouseManagerItemByCommodityID());
}

SaleManager::SaleItem jewelrySales::updateDataFromUI()
{
	SaleManager::SaleItem currentSaleItem;
	int staffID = ui.cbSaler->itemData(ui.cbSaler->currentIndex()).toInt();
	currentSaleItem.m_staffItem = StaffManager::getInstance().getStaffManagerItemByID(staffID);
	currentSaleItem.m_payment = ui.cbPayment->currentText();
	currentSaleItem.m_saleID = QDateTime::currentDateTime().toString("yyyyMMddhhmmzzz");
	StaffManager& staffManager = StaffManager::getInstance();
	for (int row = 0 ; row < ui.tableWidget->rowCount() ; row++)
	{
		SaleManager::SaleItem::CommodityItem item;
		int column = 0;
		{//id0
			QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_ID);
			item.m_commodityInfoItem.m_id = tableWidgetItem->text();
		}
    {
      QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_CERTIFICATEID);
      item.m_commodityInfoItem.m_certificateNumbers = tableWidgetItem->text();
    }
    {//��ʯ�۸�
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_GEMPRICE );
      item.m_commodityInfoItem.m_commodityGemPrice = tableWidgetItem->text().toFloat();
    }
    {//����
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_JOBPRICE );
      item.m_commodityInfoItem.m_commodityJobPrice = tableWidgetItem->text().toFloat();
    }
    {//Ȧ��
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_ROUNDNUMBERS );
      item.m_commodityInfoItem.m_commodityRoundNumbers = tableWidgetItem->text().toFloat();
    }
    {//��ʯ������
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_MAINGEMKARAT );
      item.m_commodityInfoItem.m_commodityMainGemKarat = tableWidgetItem->text().toFloat();
    }
    {//��ʯ������
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_ASSISTANTGEMKARAT );
      item.m_commodityInfoItem.m_commodityAssistantGemKarat = tableWidgetItem->text().toFloat();
    }
    {//�ȼ�
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_GRADE );
      item.m_commodityInfoItem.m_commodityGrade = tableWidgetItem->text();
    }
    {//��ɫ
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_COLOR );
      item.m_commodityInfoItem.m_commodityColor = tableWidgetItem->text();
    }
    {//����
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_GOLDWEIGHT );
      item.m_commodityInfoItem.m_commodityGoldWeight = tableWidgetItem->text().toFloat();
    }
    {//������
      QTableWidgetItem* tableWidgetItem  =  ui.tableWidget->item(row , TABLEHEADER_GROSSWEIGHT );
      item.m_commodityInfoItem.m_commodityGrossWeight = tableWidgetItem->text().toFloat();
    }
		{//name1
			QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_NAME);
			item.m_commodityInfoItem.m_commodityName = tableWidgetItem->text();
		}
    {//Price5
      QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_PRICE);
      item.m_commodityInfoItem.m_commodityPrice = tableWidgetItem->text().toFloat();
    }
		{//unit2
			QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_UNIT);
			item.m_commodityInfoItem.m_commodityUnit = tableWidgetItem->text();
		}
		{//count3
			QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_COUNT);
			item.m_saleCount = tableWidgetItem->text().toInt();
		}
		{//Discounts4
			QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_DISCOUNTS);
			item.m_commodityInfoItem.m_commodityDiscounts = tableWidgetItem->text().toFloat();
		}
		{//5
			QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_AMOUNT);
			item.m_amount = tableWidgetItem->text().toFloat();
		}
		{//type6
			QTableWidgetItem* tableWidgetItem = ui.tableWidget->item(row , TABLEHEADER_TYPE);
			item.m_commodityInfoItem.m_commodityType = tableWidgetItem->text();
		}
		{//stockNum7
			WarehouseManager& warehouseManager = WarehouseManager::getInstance();
			StaffManager::StaffManagerItem staffManagerItem = staffManager.getStaffManagerItemByID(SystemSettings::getInstance().getCurrentStaffID());
			WarehouseManager::WarehouseManagerItem warehouseManagerItem = warehouseManager.getWarehouseManagerItem( staffManagerItem.m_warehouseID
				, item.m_commodityInfoItem.m_id);
			item.m_warehouseItem = warehouseManagerItem;
		}
		currentSaleItem.m_commodityList << item;
	}
	QString vipNo = ui.leVIPCardNo->text();
	currentSaleItem.m_tradeDiscounts = ui.dbTradeDiscounts->value();
	if (vipNo.count())
	{
		currentSaleItem.m_vipItem = m_vipManagerItem;
	}
	return currentSaleItem;
}

void jewelrySales::completionTransaction()
{
  //����
	SaleManager::SaleItem currentSaleItem = updateDataFromUI();
	if(m_saleManager.saled(currentSaleItem))
	{
		QMessageBox::information(this , tr("ϵͳ��Ϣ") ,  tr("���׶����ţ�%1").arg(currentSaleItem.m_saleID));
		QList<SaleManager::SaleItem::CommodityItem>& commodityItemList = currentSaleItem.m_commodityList;
		QList<struct PRINTFINVOICE> printList;
		for (QList<SaleManager::SaleItem::CommodityItem>::iterator i = commodityItemList.begin() ; i != commodityItemList.end() ; i++)
		{
			SaleManager::SaleItem::CommodityItem& commodityItem = *i;
			PRINTFINVOICE printItem;
			printItem.name = commodityItem.m_commodityInfoItem.m_commodityName;
			printItem.CertificateNumbers = commodityItem.m_commodityInfoItem.m_certificateNumbers;

			//if (commodityItem.m_commodityInfoItem.m_commodityUnit == tr("��"))
			//{
			//	printItem.quality = commodityItem.m_commodityInfoItem.m_certificateNumbers;
			//}
			//else
      printItem.unitPrice = QString::number(commodityItem.m_commodityInfoItem.m_commodityPrice, 'f', 4);
      printItem.Kg = QString::number(commodityItem.m_commodityInfoItem.m_commodityGoldWeight, 'f', 2);
      printItem.number = QString::number(commodityItem.m_saleCount);
      printItem.price = QString::number(commodityItem.m_amount, 'f', 4);
			printList << printItem;
		}
    if (ui.checkBox->isChecked())
    {
      jewelurPrintf::getInstance().setPrint(printList);
    }
		clearAll();
	}
}


void jewelrySales::on_tableWidget_clicked(const QModelIndex &)
{

}
void jewelrySales::slotleClose()
{
  if (QMessageBox::warning(this, tr("ϵͳ��Ϣ"), tr("�Ƿ��˳�ǰ̨���ۣ�"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
  {
      this->close();
      return;
  }
}
void jewelrySales::slotsTableWidgetItem(QTableWidgetItem *item)
{
  s_tableWidgetBool = true;
  s_tableWidgetItemRows = item->row();
}
void jewelrySales::oneDiscount(int row)
{
  if (s_tableWidgetBool)
  {
    s_tableWidgetBool = false;
    if (m_singleProductDiscount == NULL)
    {
      m_singleProductDiscount  = new jewelrySingleProductDiscount(this);
    }
    m_tableWidgetItem = ui.tableWidget->item(row, TABLEHEADER_AMOUNT);
    m_singleProductDiscount->setTableWidgetItem(m_tableWidgetItem);
    if (m_singleProductDiscount->exec())
    {
      float tempPrice1;
      float tempPrice2;
      float tempPrice3;
      float tempPrice4;
      tempPrice1 = ui.leAmount->text().toFloat();
      tempPrice2 = m_singleProductDiscount->getPrice();
      tempPrice3 = m_tableWidgetItem->text().toFloat();
      tempPrice4 = tempPrice1 - tempPrice3 + tempPrice2;
      ui.leAmount->setText(QString::number(tempPrice4, 'f', 4));
       m_tableWidgetItem->setData(Qt::DisplayRole, QString::number(m_singleProductDiscount->getPrice(), 'f', 4));
    }
  }
  else
  {
    QMessageBox::critical(this, tr("ϵͳ��Ϣ"), tr("��ѡ����Ʒ"),QMessageBox::Yes);
  }
}

void jewelrySales::modifyPrice(int row)
{
  if (s_tableWidgetBool)
  {
    s_tableWidgetBool = false;
    if (m_changeUnitPrice == NULL)
    {
      m_changeUnitPrice = new jewelryChangeUnitPrice;
    }
    m_changeUnitPrice->show();
  }
  else
  {
    QMessageBox::warning(this, tr("ϵͳ��Ϣ"), tr("��ѡ����Ʒ"),QMessageBox::Yes);
  }
}

void jewelrySales::on_pushButton_15_clicked()
{
      WinExec(QString(qApp->applicationDirPath() + "/Calcute.exe").toAscii(), SW_SHOW);
}