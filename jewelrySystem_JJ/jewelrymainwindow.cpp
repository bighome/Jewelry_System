#include "jewelrymainwindow.h"
#include "jewelrypurchasing.h"
#include "jewelryinventory.h"
#include "jewelrysales.h"
#include "jewelrylogin.h"
#include "jewelrysystemsetting.h"
#include "jewelrygoodsfiles.h"
#include "jewelryVIPManagerDialog.h"
#include "jewelrysupplierinformation.h"
#include "jewelrywarehouseinformation.h"
#include "jewelrycodesettings.h"
#include "QPushButton"
#include "QMessageBox"
#include "QFile"
#include "QTextStream"
#include <QPainter>
#include "jewelrywarehousemanager.h"
#include "jewelrystaffmanager.h"
#include "SystemSettings.h"
#include "sqlquery.h"
#include <Windows.h>
#include <QProcess>
#include <QMessageBox>
#include <QApplication>
#include <QDir>
#include <QDebug>

jewelryMainWindow::jewelryMainWindow(QWidget *parent)
	: QMainWindow(parent)
	//,m_login(NULL)
	//,m_purchasing(NULL)
	//,m_warehouseManager(NULL)
	//,m_sales(NULL)
	//,m_systemSetting(NULL)
	//,m_goodsFiles(NULL)
	//,m_memberShipInformation(NULL)
	//,m_supplierInformation(NULL)
	//,m_warehouseInformation(NULL)
	//,m_codeSettings(NULL)
{
	ui.setupUi(this);
	init();
}
jewelryMainWindow::~jewelryMainWindow()
{

}
void jewelryMainWindow::init()
{
  //ui.update->hide();
	this->setAttribute(Qt::WA_TranslucentBackground, true);  
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint  
		| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint  
		| Qt::WindowMaximizeButtonHint);  
	jewelryLogin login(this);
  QString temp1 = tr("主程序版本：%1").arg(SystemSettings::getInstance().getVersion());
	QString temp2 = login.getName();
	QString temp3 = SqlQuery::getInstance().getMySqlMessager();
	ui.statusBar->showMessage(temp1+tr("          用户名：")+temp2+tr("          提示：")+temp3);
	ui.statusBar->update();
  ui.label_5->setText(tr("珠宝销售系统  %1").arg(SystemSettings::getInstance().getVersion()));

	//mainwindow
	connect(ui.cyywBTN, SIGNAL(clicked()), this, SLOT(slotsCyywBTN()));
	connect(ui.cgjhBTN, SIGNAL(clicked()), this, SLOT(slotsCgjhBTN()));
	connect(ui.spxsBTN, SIGNAL(clicked()), this, SLOT(slotsSpxsBTN()));
	connect(ui.kcglBTN, SIGNAL(clicked()), this, SLOT(slotsKcglBTN()));
	connect(ui.xtgjBTN, SIGNAL(clicked()), this, SLOT(slotsXtgjBTN()));
	connect(ui.closeSystem, SIGNAL(clicked()), this, SLOT(slotsCloseSystem()));
	connect(ui.spdaBTN, SIGNAL(clicked()), this, SLOT(slotsSpdaBTN()));
	connect(ui.hyxxBTN, SIGNAL(clicked()), this, SLOT(slotsHyxxBTN()));
	connect(ui.gysxxBTN, SIGNAL(clicked()), this, SLOT(slotsGysxxBTN()));
	connect(ui.ckxxBTN,SIGNAL(clicked()), this, SLOT(slotsCkxxBTN()));
	connect(ui.ckxxBTN_1,SIGNAL(clicked()), this, SLOT(slotsCkxxBTN_1()));
	connect(ui.hidebTN,SIGNAL(clicked()), this, SLOT(slotsHideBTN()));
	connect(ui.closeBTN,SIGNAL(clicked()), this, SLOT(slotsCloseBTN()));
	

	ui.stackedWidget->setCurrentIndex(0);

	//stackendwidget
	connect(ui.cgjhBTN_1,SIGNAL(clicked()), this, SLOT(slotsCgjhBTN_1()));
	connect(ui.cgjhBTN_2,SIGNAL(clicked()), this, SLOT(slotsCgjhBTN_2()));
	connect(ui.kcglBTN_1, SIGNAL(clicked()), this, SLOT(slotsKcglBTN_1()));
	connect(ui.pdBTN,SIGNAL(clicked()), this, SLOT(slotsPdBTN()));
	connect(ui.qtxsBTN,SIGNAL(clicked()), this, SLOT(slotsQtxsBTN()));
	connect(ui.qtxsBTN_1,SIGNAL(clicked()), this, SLOT(slotsQtxsBTN_1()));
	connect(ui.xtszBTN, SIGNAL(clicked()), this, SLOT(slotsXtszBTN()));
	connect(ui.loginBTN, SIGNAL(clicked()), this, SLOT(slotsLoginBTN()));
	connect(ui.printBTN_1,SIGNAL(clicked()), this, SLOT(slotsPrintLableBTN()));

	//close
	connect(this, SIGNAL(closeqApp()), qApp, SLOT(quit()));

	//read QSS
	QFile file(":/jewelrySystem_JJ/Resources/mainwindow.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	qApp->setStyleSheet(styleSheet);
	file.close();

	setPermissions();
	//login
}
void jewelryMainWindow::slotsCyywBTN()
{
	ui.stackedWidget->setCurrentIndex(1);
}
void jewelryMainWindow::slotsCgjhBTN()
{
	ui.stackedWidget->setCurrentIndex(2);
}
void jewelryMainWindow::slotsSpxsBTN()
{
	ui.stackedWidget->setCurrentIndex(3);
}
void jewelryMainWindow::slotsKcglBTN()
{
	ui.stackedWidget->setCurrentIndex(4);
}
void jewelryMainWindow::slotsXtgjBTN()
{
	ui.stackedWidget->setCurrentIndex(5);
}
void jewelryMainWindow::slotsCloseSystem()
{
	QMessageBox msgBox(QMessageBox::Question, "注意", "是否退出程序!", QMessageBox::Yes | QMessageBox::No, this);
	//msgBox.setDefaultButton(QMessageBox::Yes);
	int ret = msgBox.exec();
	switch(ret)
	{
			case QMessageBox::Yes:
			// Save was clicked
				emit closeqApp();
			break;
			case QMessageBox::No:
			// Don't Save was clicked
			break;
			default:
			// should never be reached
			break;
	}

}

void jewelryMainWindow::slotsCgjhBTN_1()
{
	//if (m_purchasing == NULL)
	//{
	//	m_purchasing = new jewelryPurchasing(this);
	//}
	//m_purchasing->exec();
	jewelryPurchasing purchase(this);
	purchase.exec();
}
void jewelryMainWindow::slotsCgjhBTN_2()
{
	//if (m_purchasing == NULL)
	//{
	//	m_purchasing = new jewelryPurchasing(this);
	//}
	//m_purchasing->exec();
	jewelryPurchasing purchase(this);
	purchase.exec();
}
void jewelryMainWindow::slotsKcglBTN_1()
{
	slotsPdBTN();
}
void jewelryMainWindow::slotsPdBTN()
{
	//if (m_warehouseManager == NULL)
	//{
	//	m_warehouseManager = new jewelryWarehouseManager(this);
	//}
	//m_warehouseManager->exec();
	jewelryWarehouseManager warehouseManager(this);
	warehouseManager.exec();
}
void jewelryMainWindow::slotsQtxsBTN()
{
	//if (m_sales == NULL)
	//{
	//	m_sales = new jewelrySales(this);
	//}
	//m_sales->exec();
	jewelrySales sales(this);
	sales.exec();
}
void jewelryMainWindow::slotsQtxsBTN_1()
{
	//if (m_sales == NULL)
	//{
	//	m_sales = new jewelrySales(this);
	//}
	//m_sales->exec();
	slotsQtxsBTN();
}
void jewelryMainWindow::slotsXtszBTN()
{
	//if (m_systemSetting == NULL)
	//{
	//	m_systemSetting = new jewelrySystemSetting(this);
	//}
	//m_systemSetting->exec();
	jewelrySystemSetting systemSetting(this);
	systemSetting.exec();
}
void jewelryMainWindow::slotsLoginBTN()
{
	//if (m_login == NULL)
	//{
	//	m_login = new jewelryLogin;
	//}
	//m_login ->exec();
	jewelryLogin login(this);
	login.exec();
}
void jewelryMainWindow::slotsSpdaBTN()
{
	//if (m_goodsFiles == NULL)
	//{
	//	m_goodsFiles = new jewelryGoodsFiles(this);
	//}
	//m_goodsFiles->exec();
	jewelryGoodsFiles goodsFiles(this);
	goodsFiles.exec();
}
void jewelryMainWindow::slotsHyxxBTN()
{
	//if (m_memberShipInformation == NULL)
	//{
	//	m_memberShipInformation = new jewelryVIPManagerDialog(this);
	//}
	//m_memberShipInformation->exec();
	jewelryVIPManagerDialog VIPManagerDialog(this);
	VIPManagerDialog.exec();
}
void jewelryMainWindow::slotsGysxxBTN()
{
	//if (m_supplierInformation == NULL)
	//{
	//	m_supplierInformation = new jewelrySupplierInformation(this);
	//}
	//m_supplierInformation->exec();
	jewelrySupplierInformation supplierInformation(this);
	supplierInformation.exec();
}
void jewelryMainWindow::slotsCkxxBTN()
{
	//if (m_warehouseInformation == NULL)
	//{
	//	m_warehouseInformation = new jewelryWarehouseInformation(this);
	//}
	//m_warehouseInformation->exec();
	jewelryWarehouseInformation warehouseInformation(this);
	warehouseInformation.exec();
}
void jewelryMainWindow::slotsCkxxBTN_1()
{
	//if (m_warehouseInformation == NULL)
	//{
	//	m_warehouseInformation = new jewelryWarehouseInformation(this);
	//}
	//m_warehouseInformation->exec();
	slotsCkxxBTN();
}
void jewelryMainWindow::slotsPrintLableBTN()
{
	//if (m_codeSettings == NULL)
	//{
	//	m_codeSettings = new jewelryCodeSettings(this);
	//}
	//m_codeSettings->exec();
	jewelryCodeSettings codeSettings(this);
	codeSettings.exec();
}
void jewelryMainWindow::slotsHideBTN()
{
	this->showMinimized(); 
}
void jewelryMainWindow::slotsCloseBTN()
{
  QMessageBox msgBox(QMessageBox::Question, "注意", "是否退出程序!", QMessageBox::Yes | QMessageBox::No, this);
	int ret = msgBox.exec();
	switch(ret)
	{
	case QMessageBox::Yes:
		// Save was clicked
		emit closeqApp();
		break;
	case QMessageBox::No:
		// Don't Save was clicked
		break;
	default:
		// should never be reached
		break;
	}
}
void jewelryMainWindow::paintEvent (QPaintEvent *event )
{
	QPainter p(this);  
	p.drawRoundedRect(0, 0, width() - 1, height() - 3, 5, 5);  
	QPixmap pix(":/jewelrySystem_JJ/Resources/background.png");
	if (!pix.isNull())
	{
		p.drawPixmap(0, 0, width(), height(), pix);
	}
}

void jewelryMainWindow::on_settingsBTN_clicked()
{
	jewelryStaffManager  staff;
	staff.exec();
}

void jewelryMainWindow::setPermissions()
{
	SystemSettings& systemSettings = SystemSettings::getInstance();
	StaffManager::StaffManagerItem& staffManagerItem = StaffManager::getInstance().getStaffManagerItemByID(systemSettings.getCurrentStaffID());
	if (staffManagerItem.m_post == tr("管理员"))
	{
	}
	else if (staffManagerItem.m_post == tr("会计"))
	{
		ui.groupBox->setVisible(false);
		ui.xtgjBTN->setVisible(false);
	}
}

void jewelryMainWindow::on_update_clicked()
{
  //jewelryUpdate updateSystem(this);
  //updateSystem.exec();
  if ((QMessageBox::information(this, tr("警告"), tr("主程序正在运行，更新程序时必须退出主程序才能更新！"), QMessageBox::Yes)) == QMessageBox::Yes)
  {
    WinExec(QString(qApp->applicationDirPath() + "/updateSystem.exe").toAscii(), SW_SHOW);
    this->close();
    return;
  }
}