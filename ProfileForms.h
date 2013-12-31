#pragma once
#include "ui_ProfileForm.h"

namespace Ui {
	class uiProfileForm;
}
class ImageRaster;

class ProfileForm :
	public QWidget
{
	Q_OBJECT
	Ui::uiProfileForm *ui;
	friend class ImageRaster;
public:
	ProfileForm(QWidget* parent=0);
	~ProfileForm();
};

