   /* 类说明：小票打印（以html的形式打印）
	*
	*打印格式 ：
	*		   QString("<html>") + 
	*				QString("<br><br><br><br><br><br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%1<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%2<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%3")
	*				.arg(tr("白金首饰 100元 20个"))
	*				.arg(tr("黄金首饰 200元 30个"))
	*				.arg(tr("珠宝首饰 300元 40个"))+ QString("</html>")
	*
	*/
#ifndef PRINTERINVOICE_H
#define PRINTERINVOICE_H

#include <QObject>

class printerInvoice : public QObject
{
	Q_OBJECT

public:
	printerInvoice(QObject *parent);
	~printerInvoice();
void printf(const QString &html = "<html><br><br><br><br><br><br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;打印错误<br>");

private:
	
};

#endif // PRINTERINVOICE_H
