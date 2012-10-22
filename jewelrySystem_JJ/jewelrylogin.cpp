#include "jewelrylogin.h"
#include "SystemSettings.h"
#include "StaffManager.h"
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QFile>
#include "LoginLog.h"

int jewelryLogin::error = 0;
jewelryLogin::jewelryLogin(QWidget *parent)
	: QDialog()
	,m_mainwindow(NULL)
	,m_systemSetting(NULL)
{
	ui.setupUi(this);
	//this->setWindowFlags(Qt::WindowStaysOnTopHint) ;
  this->setAttribute(Qt::WA_TranslucentBackground, true);  
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint  
    | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint  
    | Qt::WindowMaximizeButtonHint);  

  //read QSS
  QFile file(":/jewelrySystem_JJ/Resources/log.qss");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());
  qApp->setStyleSheet(styleSheet);
  file.close();

	this->setWindowTitle(tr("系统登录"));
	init();
}

jewelryLogin::~jewelryLogin()
{

}
void jewelryLogin::paintEvent (QPaintEvent *event )
{
  QPainter p(this);  
  p.drawRoundedRect(0, 0, width() - 1, height() - 3, 5, 5);  
  QPixmap pix(":/jewelrySystem_JJ/Resources/loging.png");
  if (!pix.isNull())
  {
    p.drawPixmap(0, 0, width(), height(), pix);
  }
}
void jewelryLogin::init()
{
	connect(ui.logEnter, SIGNAL(clicked()), this, SLOT(slotsLogin()));
	connect(ui.logClose, SIGNAL(clicked()), this, SLOT(close()));
	//connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(slotsSetting()));

	StaffManager& staffManager = StaffManager::getInstance();
	QMap<int , StaffManager::StaffManagerItem>& staffManagerItemMap = staffManager.getStaffManagerItemMap();
	for (QMap<int , StaffManager::StaffManagerItem>::iterator i = staffManagerItemMap.begin() ; 
		i != staffManagerItemMap.end() ; i++)
	{
		const StaffManager::StaffManagerItem& staffManagerItem = i.value();
		if (staffManagerItem.m_post == tr("采购") || staffManagerItem.m_post == tr("销售") )
		{
			continue;
		}
		ui.cbName->addItem(staffManagerItem.m_name , staffManagerItem.m_id);
	}
}
void jewelryLogin::slotsLogin()
{
	StaffManager& staffManager = StaffManager::getInstance();
	int staffID = ui.cbName->itemData(ui.cbName->currentIndex()).toInt();
	const StaffManager::StaffManagerItem staffManagerItem = staffManager.getStaffManagerItemByID(staffID);
	QString password = ui.lePassword->text();
	QString name = ui.cbName->currentText();

	if (staffManagerItem.m_name == name && staffManagerItem.m_password == password)
	{
		SystemSettings::getInstance().setCurrentStaffID(staffManagerItem.m_id);
		LoginLog::getInstance().insertNewItem(staffManagerItem.m_id);

		if (m_mainwindow == NULL)
		{
			m_mainwindow = new jewelryMainWindow;
		}
		m_mainwindow->show();
		close();
		return;
	}

	QMessageBox::warning(this , tr("系统消息") , tr("用户名和密码不符！"));
}

void jewelryLogin::slotsSetting()
{
	if (m_systemSetting == NULL)
	{
		m_systemSetting = new jewelrySystemSetting(this);
	}
	m_systemSetting->exec();
}
QString jewelryLogin::getName()
{
	return ui.cbName->currentText();
}



void jewelryLogin::on_pushButton_clicked()
{

}

void jewelryLogin::on_logMinClose_clicked()
{
  this->close();
  return;
}