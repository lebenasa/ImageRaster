#include "stdafx.h"
#include "Forms.h"
#include "RasterScene.h"

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
	h = BL;
	v = BL;
	connect(horizontalGroup, SIGNAL(buttonClicked(int)), this, SLOT(checkState()));
	connect(verticalGroup, SIGNAL(buttonClicked(int)), this, SLOT(checkState()));
	connect(length, SIGNAL(currentTextChanged(QString)), this, SLOT(sendState()));
	connect(unit, SIGNAL(currentIndexChanged(int)), this, SLOT(sendState()));
	connect(style_, SIGNAL(currentIndexChanged(int)), this, SLOT(sendState()));
}

void ScaleDock::checkState() {
	if (QRadioButton *b = qobject_cast<QRadioButton*>(qobject_cast<QButtonGroup*>(sender())->checkedButton())) {
		QString n = b->objectName();
		if (n.contains("_2")) {
			//vertical:
			if (n.contains("topleft"))
				v = TL;
			else if (n.contains("topright"))
				v = TR;
			else if (n.contains("center"))
				v = C;
			else if (n.contains("bottomleft"))
				v = BL;
			else if (n.contains("bottomright"))
				v = BR;
			else if (n.contains("left"))
				v = L;
			else if (n.contains("top"))
				v = T;
			else if (n.contains("right"))
				v = R;
			else if (n.contains("bottom"))
				v = B;
		}
		else {
			//horizontal:
			if (n.contains("topleft"))
				h = TL;
			else if (n.contains("topright"))
				h = TR;
			else if (n.contains("center"))
				h = C;
			else if (n.contains("bottomleft"))
				h = BL;
			else if (n.contains("bottomright"))
				h = BR;
			else if (n.contains("left"))
				h = L;
			else if (n.contains("top"))
				h = T;
			else if (n.contains("right"))
				h = R;
			else if (n.contains("bottom"))
				h = B;
		}
	}
	emit checked_changed(h, v);
}

void ScaleDock::sendState() {
	emit checked_changed(h, v);
}

BlendWizard::BlendWizard(const QString& source, QWidget* parent) :
	QWizard(parent),
	Ui::BlendWizard()
{
	Ui::BlendWizard::setupUi(this);
	//QMetaObject::connectSlotsByName(this);
	base = source;
	myFont = QFont();
}

bool BlendWizard::validateCurrentPage() {
	if (Intro == currentId()) {
	}
	else if (OpenImg == currentId()) {
		if (!QFile::exists(browse->text())) {
			QMessageBox::warning(this, tr("Image Not Found"),
			tr("Unable to find image. Please browse for image again."), QMessageBox::Ok);
			return false;
		}
		else {
			thumbFile = browse->text();
			crop = new CropScene(thumbFile, this);
			view1->setScene(crop);
		}
	}
	else if (Crop == currentId()) {
		crop_pix = crop->cropped();
		blend = new BlendScene(base, crop_pix, this);
		view2->setDragMode(QGraphicsView::RubberBandDrag);
		view2->setScene(blend);
		view2->centerOn(QPointF(100, 100));
		Font->setCurrentFont(myFont);
		color1->setColor(Qt::black);
		color2->setColor(Qt::white);
		fontSize->setCurrentText(QString().setNum(myFont.pointSize()));
		text->setPlainText("Text");
	}
	else if (StyleEdit == currentId()) {
		
	}
	return QWizard::validateCurrentPage();
}

void BlendWizard::on_browseButton_clicked() {
	QFileDialog openFileDg(this);
	openFileDg.setFileMode(QFileDialog::ExistingFile);
	openFileDg.setNameFilter("Portable Network Graphics File (*.png);;JPEG File-Format (*.jpg);;Bitmap File (*.bmp)");
	//openFileDg.setDirectory(QDir::home());
	//openFileDg.setViewMode(QFileDialog::Detail);
	QString imgName;
	if (openFileDg.exec())
		imgName = openFileDg.selectedFiles().at(0);
	browse->setText(imgName);
}

void BlendWizard::on_styleCombo_currentIndexChanged(int i) {
	blend->removeAnchor();
	blend->removeThumb();
	if (Circle == i) {
		blend->addClipCircle(thumbSize->value());
		blend->addCircleItem(anchorSize->value(), anchorSize->value());
	}
	else if (Box == i) {
		blend->addClipRect(thumbSize->value());
		blend->addRectItem(anchorSize->value(), anchorSize->value());
	}
	else if (Ellipse == i) {
		double ratio = 1.0 * crop_pix.width() / crop_pix.height();
		blend->addFitCircle(thumbSize->value(), thumbSize->value() / ratio);
		blend->addCircleItem(anchorSize->value(), anchorSize->value() / ratio);
	}
	else if (Rectangle == i) {
		double ratio = 1.0 * crop_pix.width() / crop_pix.height();
		blend->addFitRect(thumbSize->value(), thumbSize->value() / ratio);
		blend->addRectItem(anchorSize->value(), anchorSize->value() / ratio);
	}
	applyFormat();
}

void BlendWizard::applyFormat() {
	on_lineweight_valueChanged(lineweight->value());
}

void BlendWizard::on_color1_currentIndexChanged() {
	blend->setPen1(QPen(QBrush(color1->color()), lineweight->value()));
}

void BlendWizard::on_color2_currentIndexChanged() {
	blend->setPen2(QPen(QBrush(color2->color()), lineweight->value()));
}

void BlendWizard::on_lineweight_valueChanged(int i) {
	blend->setPen1(QPen(QBrush(color1->color()), i));
}

void BlendWizard::on_thumbSize_valueChanged(int) {
	on_styleCombo_currentIndexChanged(styleCombo->currentIndex());
}

void BlendWizard::on_anchorSize_valueChanged(int) {
	on_styleCombo_currentIndexChanged(styleCombo->currentIndex());
}

void BlendWizard::on_text_textChanged() {
	blend->setText(text->toPlainText());
}

void BlendWizard::on_Font_currentFontChanged(const QFont & font) {
	myFont = font;
	myFont.setPointSize(fontSize->currentText().toInt());
	blend->setFont(myFont);
}

void BlendWizard::on_fontSize_currentIndexChanged() {
	myFont.setPointSize(fontSize->currentText().toInt());
	blend->setFont(myFont);
}

QGraphicsItem* BlendWizard::getAnchor() { return blend->getAnchor(); }
QGraphicsItem* BlendWizard::getThumb() { return blend->getThumb(); }
QGraphicsSimpleTextItem* BlendWizard::getText() { return blend->getText(); }
QPointF BlendWizard::AnchorPos() const { return blend->AnchorPos(); }
QPointF BlendWizard::ThumbPos() const { return blend->ThumbPos(); }
QPointF BlendWizard::TextPos() const { return blend->TextPos(); }

void BlendWizard::accept() {
	QWizard::accept();
}

BlendDock::BlendDock(QWidget* parent) :
	QDockWidget(parent),
	Ui::BlendDock()
{
	Ui::BlendDock::setupUi(this);
};