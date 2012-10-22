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
   void httpFinished();  //完成下载后的处理
   void httpReadyRead();  //接收到数据时的处
   void updateDataReadProgress(qint64, qint64); //更新进度条

};

#endif // JEWELRYUPDATE_H
