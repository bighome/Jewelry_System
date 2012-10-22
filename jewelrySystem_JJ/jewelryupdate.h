#ifndef JEWELRYUPDATE_H
#define JEWELRYUPDATE_H

#include <QDialog>
#include "ui_jewelryupdate.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>

class jewelryUpdate : public QDialog
{
    Q_OBJECT

public:
    jewelryUpdate(QWidget *parent = 0);
    ~jewelryUpdate();
    void init();
    void readVersion(QString path);
    void requestHttp(QUrl url);

private:
    Ui::jewelryUpdateClass ui;
    QString m_version;
    QString m_severPath;   
    QNetworkAccessManager m_manager;
    QNetworkReply *m_reply; 
    QFile* m_file; 

private slots:
   void httpFinished();  //������غ�Ĵ���
   void httpReadyRead();  //���յ�����ʱ�Ĵ�
   void updateDataReadProgress(qint64, qint64); //���½�����

};

#endif // JEWELRYUPDATE_H
