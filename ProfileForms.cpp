#include "stdafx.h"
#include "ProfileForms.h"

ProfileForm::ProfileForm(QWidget* parent) :
	QWidget(parent), ui(new Ui::uiProfileForm())
{
	ui->setupUi(this);
}

ProfileForm::~ProfileForm() {
	delete ui;
}
