#include "stdafx.h"
#include "nModeToolbar.h"


nModeToolbar::nModeToolbar(const QString &title, QWidget *parent)
	: QToolBar(title, parent),
	Icon_LineMarker(":/Resources/LineMarker.png"),
	Icon_RectMarker(":/Resources/RectMarker.png"),
	Icon_CircleMarker(":/Resources/CircleMarker.png"),
	Icon_LineRuler(":/Resources/LineRuler.png"),
	Icon_RectRuler(":/Resources/RectRuler.png"),
	Icon_CircleRuler(":/Resources/CircleRuler.png"),
	Icon_TwoCircleRuler(":/Resources/TwoCircleRuler.png"),
	Icon_PolyRuler(":/Resources/PolyRuler.png"),
	selectButton(this),
	markerButton(this),
	rulerButton(this),
	calibButton(this),
	markerMenu(this),
	arrMarker(Icon_LineMarker, tr("Arrow"), this),
	circleMarker(Icon_CircleMarker, tr("Circle"), this),
	rectMarker(Icon_RectMarker, tr("Box"), this),
	rulerMenu(this),
	lineRuler(Icon_LineRuler, tr("Line"), 0),
	rectRuler(Icon_RectRuler, tr("Rectangle"), 0),
	circleRuler(Icon_CircleRuler, tr("Circle"), 0),
	circle2Ruler(Icon_TwoCircleRuler, tr("Center-to-Center"), 0),
	polyRuler(Icon_PolyRuler, "Polygon", 0)
{
	selectButton.setToolTip(tr("Normal, use this to move and delete items"));
	selectButton.setIcon(QIcon(":/Resources/Normal.png"));
	selectButton.setCheckable(true);
	selectButton.setChecked(true);

	//Marker Button:
	markerButton.setToolTip(tr("Draw marker with text"));
	markerButton.setIcon(QIcon(":/Resources/LineMarker.png"));
	markerButton.setCheckable(true);
	markerButton.setChecked(false);
	markerButton.setPopupMode(QToolButton::MenuButtonPopup);

	arrMarker.setToolTip(tr("Arrowhead with text"));
	arrMarker.setData((int)MarkerState::Arrow);

	circleMarker.setToolTip(tr("Circle with text"));
	circleMarker.setData((int)MarkerState::Circle);

	rectMarker.setToolTip(tr("Rectangle with text"));
	rectMarker.setData((int)MarkerState::Rectangle);

	markerMenu.addAction(&arrMarker);
	markerMenu.addAction(&circleMarker);
	markerMenu.addAction(&rectMarker);
	markerButton.setMenu(&markerMenu);
	activeMarker = &arrMarker;

	connect(&arrMarker, &QAction::triggered,
		this, &nModeToolbar::markerButton_changed);
	connect(&rectMarker, &QAction::triggered,
		this, &nModeToolbar::markerButton_changed);
	connect(&circleMarker, &QAction::triggered,
		this, &nModeToolbar::markerButton_changed);

	//Ruler Button:
	rulerButton.setToolTip(tr("Calculate distance and area"));
	rulerButton.setIcon(Icon_LineRuler);
	rulerButton.setCheckable(true);
	rulerButton.setChecked(false);
	rulerButton.setPopupMode(QToolButton::MenuButtonPopup);

	lineRuler.setToolTip(tr("Linear length & distance"));
	lineRuler.setData((int)RulerState::Line);
	connect(&lineRuler, &QAction::triggered,
		this, &nModeToolbar::rulerButton_changed);

	rectRuler.setToolTip(tr("Calculate rectangular area"));
	rectRuler.setData((int)RulerState::Rectangle);
	connect(&rectRuler, &QAction::triggered,
		this, &nModeToolbar::rulerButton_changed);

	circleRuler.setToolTip(tr("Calculate circular area"));
	circleRuler.setData((int)RulerState::Circle);
	connect(&circleRuler, &QAction::triggered,
		this, &nModeToolbar::rulerButton_changed);

	circle2Ruler.setToolTip(tr("Calculate distance between two center"));
	circle2Ruler.setData((int)RulerState::Circle2);
	connect(&circle2Ruler, &QAction::triggered,
		this, &nModeToolbar::rulerButton_changed);

	polyRuler.setToolTip(tr("Calculate polygonal area"));
	polyRuler.setData((int)RulerState::Polygon);
	connect(&polyRuler, &QAction::triggered,
		this, &nModeToolbar::rulerButton_changed);

	rulerMenu.addAction(&lineRuler);
	rulerMenu.addAction(&rectRuler);
	rulerMenu.addAction(&circleRuler);
	rulerMenu.addAction(&circle2Ruler);
	rulerMenu.addAction(&polyRuler);
	rulerButton.setMenu(&rulerMenu);
	activeRuler = &lineRuler;

	//Calibration Button:
	calibButton.setToolTip(tr("Calibrate and manage calibration profile"));
	calibButton.setIcon(QIcon(":/Resources/Calibration.png"));
	calibButton.setCheckable(true);
	calibButton.setChecked(false);

	modeButtonGroup = new QButtonGroup(this);
	modeButtonGroup->addButton(&selectButton, (int)AppState::Select);
	modeButtonGroup->addButton(&markerButton, (int)AppState::Marker);
	modeButtonGroup->addButton(&rulerButton, (int)AppState::Ruler);
	modeButtonGroup->addButton(&calibButton, (int)AppState::Calibration);
	modeButtonGroup->setExclusive(true);
	connect(modeButtonGroup, SIGNAL(buttonClicked(int)),
		this, SLOT(modeButtonGroup_Clicked(int)));

	addWidget(&selectButton);
	addWidget(&markerButton);
	addWidget(&rulerButton);
	addWidget(&calibButton);
}


nModeToolbar::~nModeToolbar()
{
}

void nModeToolbar::markerButton_changed() {
	QAction *emitter = qobject_cast<QAction*>(sender());
	MarkerState mode = (MarkerState)emitter->data().toInt();
	switch (mode) {
	case MarkerState::Arrow:
		markerButton.setIcon(Icon_LineMarker);
		break;
	case MarkerState::Rectangle:
		markerButton.setIcon(Icon_RectMarker);
		break;
	case MarkerState::Circle:
		markerButton.setIcon(Icon_CircleMarker);
		break;
	}
	activeMarker = emitter;
	emit MarkerChanged(mode);
	emit ModeChanged((AppState)modeButtonGroup->checkedId());
}

void nModeToolbar::rulerButton_changed() {
	QAction *emitter = qobject_cast<QAction*>(sender());
	RulerState mode = (RulerState)emitter->data().toInt();
	rState = mode;
	switch (mode) {
	case RulerState::Line:
		rulerButton.setIcon(Icon_LineRuler);
		break;
	case RulerState::Rectangle:
		rulerButton.setIcon(Icon_RectRuler);
		break;
	case RulerState::Circle:
		rulerButton.setIcon(Icon_CircleRuler);
		break;
	case RulerState::Circle2:
		rulerButton.setIcon(Icon_TwoCircleRuler);
		break;
	case RulerState::Polygon:
		rulerButton.setIcon(Icon_PolyRuler);
		break;
	}
	activeRuler = emitter;
	emit RulerChanged(mode);
	emit ModeChanged((AppState)modeButtonGroup->checkedId());
}

void nModeToolbar::modeButtonGroup_Clicked(int i) {
	emit ModeChanged((AppState)modeButtonGroup->checkedId());
	if (AppState::Ruler == (AppState)i)
		activeRuler->triggered();
	else if (AppState::Marker == (AppState)i)
		activeMarker->triggered();
}