#include "jewelryupdate.h"
#include <QDatetime> 
#include <QMessageBox>
#include <QSettings>
#include <QApplication>
#include<QFileInfo>
#include <QMessageBox>
#include <QDebug>

jewelryUpdate::jewelryUpdate(QWidget *parent)
    : QDialog(parent)
{
  ui.setupUi(this);
  init();
  setWindowTitle("����");
}

jewelryUpdate::~jewelryUpdate()
{
    
}
void jewelryUpdate::init()
{
  ui.progressBar->setValue(0);
  this->readVersion(QString(qApp->applicationDirPath() + "/version.ini"));
}
void jewelryUpdate::readVersion(QString path)
{
  QSettings setting(path, QSettings::IniFormat);
  m_version = setting.value("version", "0").toString();
  m_severPath = setting.value("severPath", "0").toString();
  ui.lineEdit->setText(m_severPath);
  if (m_version == "0" && m_severPath == "0")
  {
    QMessageBox::critical(this, "ϵͳ��Ϣ", "�汾�ļ�������߶�ʧ��������򿪷���Ա��ϵ��");
    return;
  }
  requestHttp(m_severPath);

}
void jewelryUpdate::requestHttp(QUrl url)
{
    qDebug() <<url;
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    if (fileName.isEmpty())
    {
      QMessageBox::critical(this, "ϵͳ��Ϣ", "�汾�ļ�������߶�ʧ��������򿪷���Ա��ϵ��");
      return;
    }
    m_file = new QFile(fileName);
    if (!m_file->open(QIODevice::WriteOnly))
    {
      delete m_file;
      m_file = 0;
      return;
    }
    m_reply = m_manager.get(QNetworkRequest(url));
    connect(m_reply,SIGNAL(finished()),this,SLOT(httpFinished())); //������ɺ�
    connect(m_reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead())); //�п�������ʱ
    connect(m_reply,SIGNAL(downloadProgress(qint64,qint64)), this,SLOT(updateDataReadProgress(qint64,qint64)));//���½�����
}
void jewelryUpdate::httpFinished()
{
  if (m_file)
  {
    m_file->write(m_reply->readAll());//�ļ�����д���ļ�
  }
}
void jewelryUpdate::httpReadyRead()
{
  m_file->flush();
  m_file->close();
  m_reply->deleteLater();
  m_reply = 0;
  delete m_file;
  m_file = 0;
}
void jewelryUpdate::updateDataReadProgress(qint64 nowInt, qint64 maxInt)
{
    ui.progressBar->setMaximum(maxInt);
    ui.progressBar->setValue(nowInt);
}