#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "jewelrydatabaselayer_global.h"

class JEWELRYDATABASELAYER_EXPORT SqlQuery : protected QObject
{
    Q_OBJECT
public:
	static SqlQuery& getInstance();
	void connectDatabase(const QString & host , const QString & databaseName , const QString & user, const QString & password);
    ~SqlQuery();

    bool query(const QString& sql);
	QVariant value(int row , int column);
	int rowCount();
	int columnCount();
	int fieldCount();
	QString fieldName(int index);
	QString lastError();
	QVariant lastInsertId();
	QString getMySqlMessager();

protected:
    SqlQuery(QObject *parent = 0);

public slots:
	
private:
	QSqlDatabase m_database;
	QSqlQuery* m_query;
	QList<QList<QVariant>> m_values;
	QString m_messager;

private:
    static SqlQuery* s_instance;
};

#endif // SQLQUERY_H
