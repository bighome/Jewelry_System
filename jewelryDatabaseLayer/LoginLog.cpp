#include "LoginLog.h"
#include "sqlquery.h"
#include <QString>

LoginLog* LoginLog::s_instance = NULL;

LoginLog::LoginLog(void)
{
}

LoginLog::~LoginLog(void)
{
}

LoginLog& LoginLog::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new LoginLog;
	}
	return *s_instance;
}

bool LoginLog::insertNewItem(int staffID)
{
	SqlQuery& query = SqlQuery::getInstance();
	QString sql = QString("call insertLoginLog(%1)").arg(staffID);
	if (query.query(sql))
	{
		return false;
	}
	return true;
}

