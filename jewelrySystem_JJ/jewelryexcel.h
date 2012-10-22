#ifndef JEWELRYEXCEL_H
#define JEWELRYEXCEL_H

#include <ActiveQt/QAxObject>
#include <QString>
#include <QHash>

class jewelryExcel
{

public:
	static jewelryExcel& getInterFace();
	~jewelryExcel();
	QHash<QString, QStringList> getExcelData(QString path);

private:
	jewelryExcel(void);
	QHash<QString, QStringList> m_excelDataMap;
	static jewelryExcel* s_interFace;
	QAxObject *m_excel;
	
};

#endif // JEWELRYEXCEL_H
