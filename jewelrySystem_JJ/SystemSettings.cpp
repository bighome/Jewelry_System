#include "SystemSettings.h"
#include "sqlquery.h"
#include <QSettings>
#include <QApplication>

SystemSettings* SystemSettings::s_instance = NULL;

SystemSettings::SystemSettings()
: m_goldPrice(100)
{
	QSettings settings(qApp->applicationDirPath() + "/seversettings.ini", QSettings::IniFormat);
	m_host = settings.value("host" ).toString();
	m_databaseName = settings.value("databaseName").toString();
	m_user = settings.value("user" ).toString();
	m_password = settings.value("password").toString();
  m_version = settings.value("version").toString();
	setConnectInfo(m_host , m_databaseName , m_user , m_password);
}

SystemSettings::~SystemSettings()
{

}

SystemSettings& SystemSettings::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new SystemSettings;
	}
	return *s_instance;
}

void SystemSettings::setCurrentStaffID(int id)
{
	m_staffID = id;
}

int SystemSettings::getCurrentStaffID()
{
	return m_staffID;
}

void SystemSettings::setGoldPrice(double goldPrice)
{
	m_goldPrice = goldPrice;
}

double SystemSettings::getGoldPrice()
{
	return m_goldPrice;
}

void SystemSettings::setConnectInfo(const QString & host , const QString & databaseName , const QString & user, const QString & password)
{
	SqlQuery::getInstance().connectDatabase(host , databaseName , user , password);
}

QString SystemSettings::getHost()
{
	return m_host;
}

QString SystemSettings::getDatabaseName()
{
	return m_databaseName;
}

QString SystemSettings::getUser()
{
	return m_user;
}

QString SystemSettings::getPassword()
{
	return m_password;
}
QString SystemSettings::getVersion()
  {
    return m_version;
  }


