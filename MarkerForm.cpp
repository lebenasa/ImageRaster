#include "stdafx.h"
#include "MarkerForm.h"

MarkerForm::MarkerForm(QWidget *parent) :
	QWidget(parent), ui(new Ui::Form)
{
	ui->setupUi(this);
}

MarkerForm::~MarkerForm(void)
{
	delete ui;
}
