#include "sqlquery.h"
#include <QMessageBox>
#include <QApplication>
#include <QSqlRecord>
#include <QSqlError>

SqlQuery* SqlQuery::s_instance = NULL;

SqlQuery& SqlQuery::getInstance()
{
    if(s_instance == NULL)
        s_instance = new SqlQuery;
    return *s_instance;
}

SqlQuery::SqlQuery(QObject *parent) 
: QObject(parent)
, m_database(QSqlDatabase::addDatabase("QMYSQL"))
, m_query(NULL)
{

}

SqlQuery::~SqlQuery()
{

}

void SqlQuery::connectDatabase(const QString & host , const QString & name , const QString & user, const QString & password)
{
	m_database.setHostName(host);//dingoliwei.eicp.net
	m_database.setDatabaseName(name);
	if (m_database.open(user , password))
	{
		//if (!m_database.transaction())
		//{
		//	int k = 0;
		//}
		QString hostIP = host;
		m_messager = tr("数据库连接成功!                   服务器IP地址: %1").arg(host);
	}
	else
	{
		QString lastError = m_database.lastError().text();
		QMessageBox::warning(0 , tr("系统消息") , lastError);
	}
	if(m_query == NULL)
		m_query = new QSqlQuery;
	//query("insert staffmanager(id , name) values(17 , 'name2')");
	//query("select * from staffmanager");
	//int row = rowCount();
	//int column = columnCount();
	//for (int i = 0 ; i < row ; i++)
	//{
	//	for (int j= 0 ; j < column ; j++)
	//	{
	//		QVariant tem = value(i , j);
	//		QString v = tem.toString();
	//		int k = 0;
	//	}
	//}
}

bool SqlQuery::query(const QString& sql)
{
	if (!m_database.isValid())
	{
		return false;
	}
	if (sql.isEmpty())
	{
		return false;
	}
	bool b = false;
	if (m_query &&  m_query->exec(sql))
	{
		if (m_query->isSelect())
		{
			m_values.clear();
			QSqlRecord record = m_query->record();
			int row = 0;
			while (m_query->next()) 
			{
				QList<QVariant> columnList;
				for (int colunm = 0 ; colunm < record.count() ; colunm++)
				{
					QVariant v = m_query->value(colunm);
					columnList << v;
				}
				m_values << columnList;
			}
		}
		//else
		//{
		//	m_database.commit();
		//	m_query->finish();
		//}
		b = true;
	}
	return b;
}

QVariant SqlQuery::value(int row , int column)
{
	QVariant val;
	if (m_values.count() > row)
	{
		QList<QList<QVariant>>::iterator i = m_values.begin();
		i += row;
		QList<QVariant>& col = *i;
		if (col.count() > column)
		{
			QList<QVariant>::iterator j = col.begin();
			j += column;
			val = *j;
		}
	}
	return val;
}

int SqlQuery::rowCount()
{
	return m_values.count();
}

int SqlQuery::columnCount()
{
	if (m_values.isEmpty())
	{
		return 0;
	}
	return m_values[0].count();
}

int SqlQuery::fieldCount()
{
	return m_query->record().count();
}

QString SqlQuery::fieldName(int index)
{
	return m_query->record().fieldName(index);
}

QString SqlQuery::lastError()
{
	return m_query->lastError().text();
}

QVariant SqlQuery::lastInsertId()
{
	return m_query->lastInsertId();
}
QString SqlQuery::getMySqlMessager()
{
	return m_messager;
}
