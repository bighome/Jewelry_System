#include "printerinvoice.h"
#include <QTextDocument>
#include <QFont>
#include <QPrinter>

printerInvoice::printerInvoice(QObject *parent)
	: QObject(parent)
{

}

printerInvoice::~printerInvoice()
{

}
void printerInvoice::printf(const QString &html)
{
	QPrinter p;
	QTextDocument doc;
	QFont font = doc.defaultFont();
	font.setBold(true);
	font.setPointSize(font.pointSize());
	doc.setDefaultFont(font);
	QSizeF s = QSizeF(p.logicalDpiX() * 7.5, p.logicalDpiY() * 7.5);
	doc.setPageSize(s);
	p.setOutputFormat(QPrinter::NativeFormat);
	doc.setHtml(html);
	doc.print(&p);
}