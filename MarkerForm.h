#pragma once
#include "ui_MarkerForm.h"

namespace Ui {
	class Form;
}

class ImageRaster;

class MarkerForm :
	public QWidget
{
	Q_OBJECT
	Ui::Form *ui;
	friend class ImageRaster;
public:
	MarkerForm(QWidget *parent=0);
	virtual ~MarkerForm(void);
};

