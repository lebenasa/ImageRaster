#include "stdafx.h"
#include "Forms.h"

RulerDock::RulerDock(QWidget* parent) :
	QDockWidget(parent),
	Ui::RulerDock()
{
	Ui::RulerDock::setupUi(this);
}

RulerDock::~RulerDock() {
}

MarkerDock::MarkerDock(QWidget* parent) :
	QDockWidget(parent),
	Ui::MarkerDock()
{
	Ui::MarkerDock::setupUi(this);
}

MarkerDock::~MarkerDock(){
}

ScaleDock::ScaleDock(QWidget* parent) :
	QDockWidget(parent),
	Ui::ScaleDock()
{
	Ui::ScaleDock::setupUi(this);
	for (auto widget : this->children()) {
		if (QCheckBox* cb = qobject_cast<QCheckBox*>(widget)) {
			myCheckBox.append(cb);
			connect(cb, QCheckBox::stateChanged, this, ScaleDock::checkState);
		}
	}
}

void ScaleDock::checkState() {
	Checked c1 = None, c2 = None;
	for (auto cb : myCheckBox) {
		if (!cb->isChecked()) continue;
		if (cb->objectName() == "topleft")
			c1 = TL;
		else if (cb->objectName() == "top")
			c1 = T;
		else if (cb->objectName() == "topright")
			c1 = TR;
		else if (cb->objectName() == "left")
			c1 = L;
		else if (cb->objectName() == "center")
			c1 = C;
		else if (cb->objectName() == "right")
			c1 = R;
		else if (cb->objectName() == "bottomleft")
			c1 = BL;
		else if (cb->objectName() == "bottom")
			c1 = B;
		else if (cb->objectName() == "bottomright")
			c1 = BR;
	}
	for (auto cb : myCheckBox) {
		if (!cb->isChecked()) continue;
		if (cb->objectName() == "topleft" && c1 != TL)
			c2 = TL;
		else if (cb->objectName() == "top" && c1 != T)
			c2 = T;
		else if (cb->objectName() == "topright" && c1 != TR)
			c2 = TR;
		else if (cb->objectName() == "left" && c1 != L)
			c2 = L;
		else if (cb->objectName() == "center" && c1 != C)
			c2 = C;
		else if (cb->objectName() == "right" && c1 != R)
			c2 = R;
		else if (cb->objectName() == "bottomleft" && c1 != BL)
			c2 = BL;
		else if (cb->objectName() == "bottom" && c1 != B)
			c2 = B;
		else if (cb->objectName() == "bottomright" && c1 != BR)
			c2 = BR;
	}
	if (None != c1 && None != c2)
		for (auto cb : myCheckBox)
			if (!cb->isChecked())
				cb->setEnabled(false);
	else
		for (auto cb : myCheckBox)
			cb->setEnabled(true);
	emit checked_changed(c1, c2);
}

BlendWizard::BlendWizard(QWidget* parent) :
	QWizard(parent),
	Ui::BlendWizard()
{
	Ui::BlendWizard::setupUi(this);
	QMetaObject::connectSlotsByName(this);
}

bool BlendWizard::validateCurrentPage() {
	switch (currentId()) {
	case Intro:
		break;
	case OpenImg:
		if (!QFile::exists(browse->text())) {
			QMessageBox::warning(this, tr("Image Not Found"),
			tr("Unable to find image. Please browse for image again."), QMessageBox::Ok);
			return false;
		}
		else {
			thumbFile = browse->text();
			return true;
		}
		break;
	case Crop:
		break;
	case StyleEdit:
		break;
	}
	QWizard::validateCurrentPage();
}

void BlendWizard::on_browseButton_clicked() {
	QFileDialog openFileDg(this);
	openFileDg.setFileMode(QFileDialog::ExistingFile);
	openFileDg.setNameFilter("Portable Network Graphics File (*.png);;JPEG File-Format (*.jpg);;Bitmap File (*.bmp)");
	//openFileDg.setDirectory(QDir::home());
	openFileDg.setViewMode(QFileDialog::Detail);
	QString imgName;
	if (openFileDg.exec())
		imgName = openFileDg.selectedFiles().at(0);
	browse->setText(imgName);
}

void BlendWizard::on_style_currentIndexChanged(int i) {

}

void BlendWizard::on_color1_currentIndexChanged() {

}

void BlendWizard::on_color2_currentIndexChanged() {

}

void BlendWizard::on_lineweight_valueChanged(int i) {

}

void BlendWizard::on_thumbSize_valueChanged(int) {

}

void BlendWizard::on_anchorSize_valueChanged(int) {

}

void BlendWizard::on_text_textChanged() {

}

BlendDock::BlendDock(QWidget* parent) :
	QDockWidget(parent),
	Ui::BlendDock()
{
	Ui::BlendDock::setupUi(this);
};