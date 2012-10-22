#ifndef JEWELRYLOGIN_H
#define JEWELRYLOGIN_H

#include <QDialog>
#include "ui_jewelrylogin.h"
#include "jewelrymainwindow.h"
#include "jewelrysystemsetting.h"
#include <QPaintEvent>

class jewelryLogin : public QDialog
{
	Q_OBJECT

public:
	jewelryLogin(QWidget *parent = 0);
	~jewelryLogin();
	void init();
	QString getName();
private slots:
  void on_logMinClose_clicked();
  void on_pushButton_clicked();
	void slotsLogin();
	void slotsSetting();

private:
	Ui::jewelryLoginClass ui;
	jewelryMainWindow* m_mainwindow;
	jewelrySystemSetting* m_systemSetting;
  void paintEvent (QPaintEvent *event );
	static int error;
};

#endif // JEWELRYLOGIN_H
