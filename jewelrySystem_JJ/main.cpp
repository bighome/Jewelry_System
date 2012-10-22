#include <QtGui/QApplication>
#include <QTextCodec>
#include <time.h>
#include <QSplashScreen>
#include "jewelrylogin.h"
#include "SystemSettings.h"
#include "jewelurprintf.h"

//�ӡ��������������̡����������е���clock()������ʱ֮���CPUʱ�Ӽ�ʱ��Ԫ��clock tick����
void MainSleep(unsigned msec)
{
  clock_t start = clock();
  while(true)
  {
    clock_t diff = clock()-start;
    if(diff > msec) return;

    qApp->processEvents();
  }
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
  QApplication::setStyle("plastique");
	QTextCodec *codec = QTextCodec::codecForName("system"); 
	QTextCodec::setCodecForLocale(codec); 
	QTextCodec::setCodecForCStrings(codec); 
	QTextCodec::setCodecForTr(codec);
	SystemSettings::getInstance();
  QPixmap pixmap(":/jewelrySystem_JJ/Resources/loading.png");
  QFont splashFont("Times", 10, QFont::Normal);
  QSplashScreen splash(pixmap);
  splash.setFont(splashFont);
  splash.showMessage(QObject::tr("           ���ڼ���............"),Qt::AlignBottom | Qt::AlignLeft, Qt::white);
  splash.show();
	jewelryLogin login;
  qApp->processEvents();
  MainSleep(4000);
  login.resize(400, 230);
	login.show();
   splash.finish(&login);
	return a.exec();
}
