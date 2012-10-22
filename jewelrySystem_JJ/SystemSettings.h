#pragma once
#include "stddef.h"
#include <QString>

class SystemSettings
{
public:
	~SystemSettings();
	static SystemSettings& getInstance();
	void setCurrentStaffID(int id);
	int getCurrentStaffID();
	void setGoldPrice(double goldPrice);
	double getGoldPrice();
	void setConnectInfo(const QString & host , const QString & databaseName , const QString & user, const QString & password);
	QString getHost();
	QString getDatabaseName();
	QString getUser();
	QString getPassword();
  QString getVersion();

private:
	SystemSettings();

private:
	int m_staffID;
	double m_goldPrice;

	 QString m_host;
	 QString m_databaseName;
	 QString m_user;
	 QString m_password;
   QString m_version;

private:
	static SystemSettings* s_instance;
};