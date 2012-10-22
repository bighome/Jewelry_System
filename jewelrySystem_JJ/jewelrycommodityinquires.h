#ifndef JEWELRYCOMMODITYINQUIRES_H
#define JEWELRYCOMMODITYINQUIRES_H

#include <QWidget>
#include "ui_jewelrycommodityinquires.h"

class jewelryCommodityInquires : public QWidget
{
	Q_OBJECT

public:
	jewelryCommodityInquires(QWidget *parent = 0);
	~jewelryCommodityInquires();

private:
	Ui::jewelryCommodityInquiresClass ui;
};

#endif // JEWELRYCOMMODITYINQUIRES_H
