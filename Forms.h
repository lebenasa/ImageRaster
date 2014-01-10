#pragma once
#include "qdockwidget.h"
#include "ui_RulerDock.h"
#include "ui_MarkerDock.h"
#include "ui_ScaleDock.h"
#include "ui_BlendDock.h"
#include "ui_BlendWizard.h"

class RulerDock :
	public QDockWidget,
	public Ui::RulerDock
{
public:
	RulerDock(QWidget* parent=0);
	~RulerDock();
};

class MarkerDock :
	public QDockWidget,
	public Ui::MarkerDock
{
public:
	MarkerDock(QWidget* parent=0);
	~MarkerDock();
};

class ScaleDock :
	public QDockWidget,
	public Ui::ScaleDock
{
	Q_OBJECT
	QList<QCheckBox*> myCheckBox;
	friend class ImageRaster;
public:
	ScaleDock(QWidget* parent=0);
	enum Checked {
		TL, T, TR, L, C, R, BL, B, BR, None
	} h, v;

public slots:
	void checkState();
	void sendState();
signals:
	void checked_changed(int, int);
};

class CropScene;
class BlendScene;
class BlendWizard:
	public QWizard,
	public Ui::BlendWizard
{
	Q_OBJECT
	QString thumbFile;
	CropScene* crop;
	QPixmap crop_pix;
	BlendScene* blend;
	QString base;
	QFont myFont;
public:
	BlendWizard(const QString& source, QWidget* parent=0);
	enum PageStatus {
		Intro, OpenImg, Crop, StyleEdit
	} page_status;
	enum StyleType {
		Circle, Box, Ellipse, Rectangle
	};
	bool validateCurrentPage();
	void applyFormat();

	int getStyle() const { return styleCombo->currentIndex(); }
	QPen getPen1() { return QPen(QBrush(color1->color()), lineweight->value()); }
	QPen getPen2() const { return QPen(color2->color()); }
	QFont getFont() const { return myFont; }
	QString getText() const { return text->toPlainText(); }
	QGraphicsItem* getAnchor();
	QGraphicsItem* getThumb();
	QGraphicsSimpleTextItem* getText();
	QPointF AnchorPos() const;
	QPointF ThumbPos() const;
	QPointF TextPos() const;

	void accept();

public slots:
	void on_browseButton_clicked();
	void on_styleCombo_currentIndexChanged(int);
	void on_color1_currentIndexChanged();
	void on_color2_currentIndexChanged();
	void on_lineweight_valueChanged(int);
	void on_thumbSize_valueChanged(int);
	void on_anchorSize_valueChanged(int);
	void on_text_textChanged();
	void on_Font_currentFontChanged(const QFont & font);
	void on_fontSize_currentIndexChanged();
};

class BlendDock:
	public QDockWidget,
	public Ui::BlendDock
{
public:
	BlendDock(QWidget* parent=0);
};

