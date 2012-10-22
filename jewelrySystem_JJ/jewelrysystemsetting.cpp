#include "jewelrysystemsetting.h"
#include "SystemSettings.h"

jewelrySystemSetting::jewelrySystemSetting(QWidget *parent)
	: QDialog(0)
{
	ui.setupUi(this);
	this->setWindowTitle(tr("ÏµÍ³ÉèÖÃ"));

	SystemSettings& systemSettings = SystemSettings::getInstance();
	ui.leHost->setText(systemSettings.getHost());
	ui.leDatabaseName->setText(systemSettings.getDatabaseName());
	ui.leUser->setText(systemSettings.getUser());
	ui.lePassword->setText(systemSettings.getPassword());
}

jewelrySystemSetting::~jewelrySystemSetting()
{

}


void jewelrySystemSetting::on_pbOK_clicked()
{
	QString host  = ui.leHost->text();
	QString databaseName = ui.leDatabaseName->text();
	QString user = ui.leUser->text();
	QString password = ui.lePassword->text();
	SystemSettings::getInstance().setConnectInfo(host , databaseName , user , password);
	accept();
}

void jewelrySystemSetting::on_pbCancel_clicked()
{
	reject();
}