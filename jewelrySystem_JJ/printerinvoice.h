   /* ��˵����СƱ��ӡ����html����ʽ��ӡ��
	*
	*��ӡ��ʽ ��
	*		   QString("<html>") + 
	*				QString("<br><br><br><br><br><br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%1<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%2<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%3")
	*				.arg(tr("�׽����� 100Ԫ 20��"))
	*				.arg(tr("�ƽ����� 200Ԫ 30��"))
	*				.arg(tr("�鱦���� 300Ԫ 40��"))+ QString("</html>")
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
void printf(const QString &html = "<html><br><br><br><br><br><br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��ӡ����<br>");

private:
	
};

#endif // PRINTERINVOICE_H
