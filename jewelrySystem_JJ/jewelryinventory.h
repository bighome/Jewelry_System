//ел╣Ц

#ifndef JEWELRYINVENTORY_H
#define JEWELRYINVENTORY_H

#include <QDialog>
#include "ui_jewelryinventory.h"

class jewelryInventory : public QDialog
{
	Q_OBJECT

public:
	jewelryInventory(QWidget *parent);
	~jewelryInventory();

private:
	Ui::jewelryInventoryClass ui;
};

#endif // JEWELRYINVENTORY_H
