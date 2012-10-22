#include "jewelurprintf.h"
#include <QSettings>
#include <QStringList>
#include <QApplication>
#include <QDebug>
#include <QDateTime >

jewelurPrintf* jewelurPrintf::m_instance = NULL;

jewelurPrintf& jewelurPrintf::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new jewelurPrintf;
	}
	return *m_instance;
}

jewelurPrintf::jewelurPrintf(QObject *parent)
	: QObject(parent)
{
  
}

jewelurPrintf::~jewelurPrintf()
{

}
void jewelurPrintf::setPrint(const QList<struct PRINTFINVOICE>& text)
{
  QDateTime nowTime = QDateTime::currentDateTime();
  QString time = nowTime.toString("yyyy-MM-dd");
	static QString printHtml;
	QString tempHtml;
	QStringList htmlList;
	QString tempHtemList;
  QList<float> tempTotalPrices;
  float tempsToatalPrices = 0;
  float totalPrices = 0;
	int temp;
	for (int i = 0; i < text.size(); i++)
	{
		tempHtml = QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;")
								+text.at(i).name
								+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;")
								+text.at(i).CertificateNumbers
								+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;")
								+text.at(i).unitPrice
								+QString("&nbsp;&nbsp;&nbsp;")
								+text.at(i).Kg
								+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;")
								+text.at(i).number
								+QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;")
								+text.at(i).price;
    tempTotalPrices << text.at(i).price.toFloat();
		htmlList << tempHtml;
	}
	printHtml = QString("<html>") 
		+ QString("<br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%1<br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;品名&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;证书编号&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;单价&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;克数&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;数量&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;总价").arg(time);
	for (int i = 0 ; i < htmlList.size(); i++)
	{
		tempHtemList  = QString("<br>"+htmlList.at(i));
		printHtml = printHtml +tempHtemList;
	}
  for (int i =0; i< tempTotalPrices.size(); i++)
  {
    tempsToatalPrices = tempTotalPrices.at(i);
    totalPrices = totalPrices + tempsToatalPrices;
  }
  printHtml = printHtml+QString("<br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;实收金额:￥%1<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;顾客签名:___________</html>").arg(totalPrices);
	m_printerInvoice = new printerInvoice(this);
	m_printerInvoice->printf(printHtml);
}
void jewelurPrintf::setPrintCoad(const QString& text, const QString& coad , int number)
{
	QSettings openSettings(qApp->applicationDirPath() + "/settings.ini" , QSettings::IniFormat);
	openSettings.beginGroup("printfCoad");
	m_printNmae = openSettings.value("m_printNmae","").toChar().toAscii();
	m_lHeight = openSettings.value("m_lHeight", "").toInt();
	m_gapH = openSettings.value("m_gapH","").toInt();
	m_lWidth = openSettings.value("m_lWidth", "").toInt();
	m_darkness = openSettings.value("m_darkness", "").toInt();
	m_printSpeed = openSettings.value("m_printSpeed", "").toInt();
	m_x = openSettings.value("m_x", "").toInt();
	m_y = openSettings.value("m_y", "").toInt();
	m_fHeight = openSettings.value("m_fHeight", "").toInt();
	m_fWidth = openSettings.value("m_fWidth", "").toInt();
	m_fYupe = openSettings.value("m_fYupe", "").toChar().toAscii();
	m_fSpin = openSettings.value("m_fSpin", "").toInt();
	m_fWeight = openSettings.value("m_fWeight", "").toInt();
	m_fItalic = openSettings.value("m_fItalic", "").toBool();
	m_fUnline = openSettings.value("m_fUnline", "").toBool();
	m_fStrikeOut = openSettings.value("m_fStrikeOut", "").toBool();
	m_IdName = openSettings.value("m_IdName", "").toChar().toAscii();

	m_text = new WCHAR[text.count() + 1];
	memset(m_text , 0 , sizeof(WCHAR) * (coad.count() + 1));
	text.toWCharArray(m_text);
	//m_text = (LPTSTR)text.data();

	m_codePx = openSettings.value("m_codePx", "").toInt();
	m_codePy = openSettings.value("m_codePy", "").toInt();
	m_pdirec = openSettings.value("m_pdirec", "").toInt();
	m_pCode = openSettings.value("m_pCode", "").toInt();
	m_narrowWidth = openSettings.value("m_narrowWidth", "").toInt();
	m_pHorizonta = openSettings.value("m_pHorizonta", "").toInt();
	m_pVertical = openSettings.value("m_pVertical", "").toInt();
	m_pText = openSettings.value("m_pText", "").toChar().toAscii();

	m_pStr = new WCHAR[coad.count() + 1];
	memset(m_pStr , 0 , sizeof(WCHAR) * (coad.count() + 1));
	coad.toWCharArray(m_pStr);

	m_number = number;
	m_cpNumber = openSettings.value("m_cpNumber", "").toInt();
	openSettings.endGroup();
	m_printCode = new printCode(LPCTSTR(m_printNmae),
																	 m_lHeight,
																	m_gapH,
																	 m_lWidth,
																	 m_darkness,
																	m_printSpeed,
																	m_x ,
																	m_y,
																	m_fHeight,
																	m_fWidth,
																	LPCTSTR(m_fYupe),
																	m_fSpin,
																	m_fWeight,
																	m_fItalic,
																	m_fUnline,
																	m_fStrikeOut,
																	LPCTSTR(m_IdName),
																	LPCTSTR (m_text) ,
																	m_codePx,
																	m_codePy,
																	m_pdirec,
																	LPTSTR(m_pCode),
																	m_narrowWidth,
																	m_pHorizonta,
																	m_pVertical,
																	m_pText,
																	LPTSTR(m_pStr),
																	m_number,
																	m_cpNumber);
	delete []m_text;
	delete []m_pStr;
} 