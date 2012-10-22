#ifndef JEWELURPRINTF_H
#define JEWELURPRINTF_H

#include <QObject>
#include "printerinvoice.h"
#include "printcode.h"

struct PRINTFINVOICE{
	QString name;
	QString CertificateNumbers;
	QString unitPrice;
	QString number;
	QString price;
  QString Kg;
};

class jewelurPrintf : public QObject
{
	Q_OBJECT

public:
	static jewelurPrintf& getInstance();
	~jewelurPrintf();
	void setPrint(const QList<struct PRINTFINVOICE>& textList);
	void setPrintCoad(const QString& text, const QString& coad , int number);

private:
	jewelurPrintf(QObject *parent = NULL);
	static jewelurPrintf* m_instance;

private:
	printerInvoice* m_printerInvoice;
	printCode* m_printCode;
	char m_printNmae;
	int m_lHeight;
	int m_gapH;
	int m_lWidth;
	int m_darkness;
	int m_printSpeed;
	int m_x;
	int m_y;
	int m_fHeight;
	int m_fWidth;
	char m_fYupe;
	int m_fSpin;
	int m_fWeight;
	BOOL m_fItalic;
	BOOL m_fUnline;
	BOOL m_fStrikeOut;
	char m_IdName;
	LPTSTR m_text;
	int m_codePx;
	int m_codePy;
	int m_pdirec;
	int m_pCode;
	int m_narrowWidth;
	int m_pHorizonta;
	int m_pVertical;
	char m_pText;
	LPTSTR m_pStr;
	int m_number;
	int m_cpNumber;
};

#endif // JEWELURPRINTF_H
