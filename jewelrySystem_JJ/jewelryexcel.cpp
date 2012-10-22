#include "jewelryexcel.h"
#include <QMessageBox>
#include <QDebug>
#include <QMap>
#include <QProgressDialog>

jewelryExcel* jewelryExcel::s_interFace = NULL;

jewelryExcel& jewelryExcel:: getInterFace()
{
	if (s_interFace == NULL)
	{
		s_interFace = new jewelryExcel;
	}
	return *s_interFace;
}
jewelryExcel::jewelryExcel(void)
{
	m_excel = NULL;
}

jewelryExcel::~jewelryExcel()
{
	delete m_excel;
}
QHash<QString, QStringList> jewelryExcel::getExcelData(QString path)
{
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;

	QStringList listHeadersName;
	QStringList listTableData;
	int temp_i =0;
	int temp_j = 1;

	QProgressDialog *progressDlg=new QProgressDialog;  
	progressDlg->setWindowModality(Qt::WindowModal);  
	progressDlg->setMinimumDuration(5);  
	progressDlg->setWindowTitle("请等待");  
	progressDlg->setLabelText("正在将数据导入程序......");  
	progressDlg->setCancelButtonText("取消");  

    m_excel = new QAxObject("Excel.Application");
    if (!m_excel)
    {
		QMessageBox msgBox;
		msgBox.setText("EXCEL对象丢失.");
		msgBox.exec();
        return m_excelDataMap;
    }
    m_excel->dynamicCall("SetVisible(bool)", false);
    workbooks = m_excel->querySubObject("WorkBooks");
    workbook = workbooks->querySubObject("Open(QString, QVariant)", path);
	//打开第一个sheet
	QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);
	//获取该sheet的使用范围对象
    QAxObject * usedrange = worksheet->querySubObject("UsedRange");
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");
    //获取行数和列数
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
	//qDebug() << "row:" << intRowStart << "column:" << intColStart << "count1:" << intCols << "count2:" << intRows;
    //获取入库单表头
    for (int r = intRowStart; r < intRowStart + intRows; r++)  //行
    {
        for (int c = intColStart; c < intColStart + intCols; c++)  //列
        {
            QAxObject * HeadersName = worksheet->querySubObject("Cells(int,int)", r, c ); 
			 //qDebug() << r << c <<HeadersName->dynamicCall("Value2()").toString();
			 if (r == 1)
			 {
				listHeadersName << HeadersName->dynamicCall("Value2()").toString(); 
			 }
		}
    }
	progressDlg->setRange(0,listHeadersName.size());  

	//获取入库单内容
	for (int h = 0; h< listHeadersName.size(); h++)
	{
		for (int r = intRowStart; r < intRowStart + intRows; r++)
		{
			for (int c = intColStart; c < intColStart + intCols; c++)
			{
				QAxObject * data = worksheet->querySubObject("Cells(int,int)", r, c );
				if (r != 1 && c == temp_j)
				{	
					listTableData <<  data->dynamicCall("Value2()").toString();
				}
			}
		}
			progressDlg->setValue(temp_j);  
			m_excelDataMap.insert(listHeadersName.at(temp_i), listTableData);
			qDebug() << "key:" <<listHeadersName.at(temp_i) << "value:" << listTableData;
			listTableData.clear();
			temp_i++;
			temp_j++;
	}
	workbook->dynamicCall("Close (Boolean)", true);
	return m_excelDataMap;
	delete m_excel;
}