#include "stdafx.h"
#include "ModeToolbar.h"

ModeToolbar::ModeToolbar(const QString &title, QWidget *parent)
	: QToolBar(title, parent)
{
	/*Custom toolbar untuk keperluan mode-select.
	Slots:		None
	Signals:	ModeChanged(RasterMode)
				RulerChanged(RulerMode)
				MarkerChanged(MarkerMode)
	External Dependancies:
				Icon_LineMarker = QIcon(":/Resources/LineMarker.png");
				Icon_RectMarker = QIcon(":/Resources/RectMarker.png");
				Icon_CircleMarker = QIcon(":/Resources/CircleMarker.png");
	
				Icon_LineRuler = QIcon(":/Resources/LineRuler.png");
				Icon_RectRuler = QIcon(":/Resources/RectRuler.png");
				Icon_CircleRuler = QIcon(":/Resources/CircleRuler.png");
				Icon_TwoCircleRuler = QIcon(":/Resources/TwoCircleRuler.png");
				Icon_PolyRuler = QIcon(":/Resources/PolyRuler.png");
	*/
	createMe();
}

ModeToolbar::~ModeToolbar(void)
{
}

void ModeToolbar::createMe() {
	//Load Icons for dynamic icon change
	Icon_LineMarker = QIcon(":/Resources/LineMarker.png");
	Icon_RectMarker = QIcon(":/Resources/RectMarker.png");
	Icon_CircleMarker = QIcon(":/Resources/CircleMarker.png");
	
	Icon_LineRuler = QIcon(":/Resources/LineRuler.png");
	Icon_RectRuler = QIcon(":/Resources/RectRuler.png");
	Icon_CircleRuler = QIcon(":/Resources/CircleRuler.png");
	Icon_TwoCircleRuler = QIcon(":/Resources/TwoCircleRuler.png");
	Icon_PolyRuler = QIcon(":/Resources/PolyRuler.png");

	//Normal Button:
	QToolButton *normalButton = new QToolButton;
	normalButton->setToolTip(tr("Normal, use this to move and delete items"));
	normalButton->setIcon(QIcon(":/Resources/Normal.png"));
	normalButton->setCheckable(true);
	normalButton->setChecked(true);

	//Marker Button:
	markerButton = new QToolButton;
	markerButton->setToolTip(tr("Draw marker with text"));
	markerButton->setIcon(QIcon(":/Resources/LineMarker.png"));
	markerButton->setCheckable(true);
	markerButton->setChecked(false);
	markerButton->setPopupMode(QToolButton::MenuButtonPopup);
	QMenu *markerMenu = new QMenu;

	QAction *lineMarker = new QAction(Icon_LineMarker, tr("Arrow"), 0);
	lineMarker->setToolTip(tr("Arrowhead with text"));
	lineMarker->setData((int)MarkerState::Arrow);

	QAction *rectMarker = new QAction(Icon_RectMarker, tr("Box"), 0);
	rectMarker->setToolTip(tr("Rectangle with text"));
	rectMarker->setData((int)MarkerState::Rectangle);

	QAction *circleMarker = new QAction(Icon_CircleMarker, tr("Circle"), 0);
	circleMarker->setToolTip(tr("Circle with text"));
	circleMarker->setData((int)MarkerState::Circle);

	markerMenu->addAction(lineMarker);
	markerMenu->addAction(rectMarker);
	markerMenu->addAction(circleMarker);
	markerButton->setMenu(markerMenu);

	connect(lineMarker, &QAction::triggered,
		this, &ModeToolbar::markerButton_changed);
	connect(rectMarker, &QAction::triggered,
		this, &ModeToolbar::markerButton_changed);
	connect(circleMarker, &QAction::triggered,
		this, &ModeToolbar::markerButton_changed);

	//Counter Button:
	//QToolButton *counterButton = new QToolButton;
	//counterButton->setToolTip(tr("Count particular object"));
	//counterButton->setIcon(QIcon(":/Resources/Counter.png"));
	//counterButton->setCheckable(true);
	//counterButton->setChecked(false);

	//Ruler Button:
	rulerButton = new QToolButton;
	rulerButton->setToolTip(tr("Calculate distance and area"));
	rulerButton->setIcon(Icon_LineRuler);
	rulerButton->setCheckable(true);
	rulerButton->setChecked(false);
	rulerButton->setPopupMode(QToolButton::MenuButtonPopup);
	QMenu *rulerMenu = new QMenu;
	QAction *lineRuler = new QAction(Icon_LineRuler, tr("Line"), 0);
	lineRuler->setToolTip(tr("Linear length & distance"));
	lineRuler->setData((int)RulerState::Line);
	connect(lineRuler, &QAction::triggered,
		this, &ModeToolbar::rulerButton_changed);

	QAction *rectRuler = new QAction(Icon_RectRuler, tr("Rectangle"), 0);
	rectRuler->setToolTip(tr("Calculate rectangular area"));
	rectRuler->setData((int)RulerState::Rectangle);
	connect(rectRuler, &QAction::triggered,
		this, &ModeToolbar::rulerButton_changed);

	QAction *circleRuler = new QAction(Icon_CircleRuler, tr("Circle"), 0);
	circleRuler->setToolTip(tr("Calculate circular area"));
	circleRuler->setData((int)RulerState::Circle);
	connect(circleRuler, &QAction::triggered,
		this, &ModeToolbar::rulerButton_changed);

	QAction *twoCircleRuler = new QAction(Icon_TwoCircleRuler, tr("Center-to-Center"), 0);
	twoCircleRuler->setToolTip(tr("Calculate distance between two center"));
	twoCircleRuler->setData((int)RulerState::Circle2);
	connect(twoCircleRuler, &QAction::triggered,
		this, &ModeToolbar::rulerButton_changed);

	QAction *polyRuler = new QAction(Icon_PolyRuler, "Polygon", 0);
	polyRuler->setToolTip(tr("Calculate polygonal area"));
	polyRuler->setData((int)RulerState::Polygon);
	connect(polyRuler, &QAction::triggered,
		this, &ModeToolbar::rulerButton_changed);

	rulerMenu->addAction(lineRuler);
	rulerMenu->addAction(rectRuler);
	rulerMenu->addAction(circleRuler);
	rulerMenu->addAction(twoCircleRuler);
	rulerMenu->addAction(polyRuler);
	rulerButton->setMenu(rulerMenu);

	QToolButton *calibButton = new QToolButton;
	calibButton->setToolTip(tr("Calibrate and manage calibration profile"));
	calibButton->setIcon(QIcon(":/Resources/Calibration.png"));
	calibButton->setCheckable(true);
	calibButton->setChecked(false);

	modeButtonGroup = new QButtonGroup(this);
	modeButtonGroup->addButton(normalButton, (int)AppState::Select);
	modeButtonGroup->addButton(markerButton, (int)AppState::Marker);
	modeButtonGroup->addButton(rulerButton, (int)AppState::Ruler);
	modeButtonGroup->addButton(calibButton, (int)AppState::Calibration);
	modeButtonGroup->setExclusive(true);
	connect(modeButtonGroup, SIGNAL(buttonClicked()),
		this, SLOT(modeButtonGroup_Clicked()));

	addWidget(normalButton);
	addWidget(markerButton);
	addWidget(rulerButton);
	addWidget(calibButton);
}

void ModeToolbar::markerButton_changed() {
	QAction *emitter = qobject_cast<QAction*>(sender());
	MarkerState mode = (MarkerState)emitter->data().toInt();
	switch (mode) {
	case MarkerState::Arrow:
		markerButton->setIcon(Icon_LineMarker);
		break;
	case MarkerState::Rectangle:
		markerButton->setIcon(Icon_RectMarker);
		break;
	case MarkerState::Circle:
		markerButton->setIcon(Icon_CircleMarker);
		break;
	}
	emit MarkerChanged(mode);
}

void ModeToolbar::rulerButton_changed() {
	QAction *emitter = qobject_cast<QAction*>(sender());
	RulerState mode = (RulerState)emitter->data().toInt();
	switch (mode) {
	case RulerState::Line:
		rulerButton->setIcon(Icon_LineRuler);
		break;
	case RulerState::Rectangle:
		rulerButton->setIcon(Icon_RectRuler);
		break;
	case RulerState::Circle:
		rulerButton->setIcon(Icon_CircleRuler);
		break;
	case RulerState::Circle2:
		rulerButton->setIcon(Icon_TwoCircleRuler);
		break;
	case RulerState::Polygon:
		rulerButton->setIcon(Icon_PolyRuler);
		break;
	}
	emit RulerChanged(mode);
}

void ModeToolbar::modeButtonGroup_Clicked() {
	emit ModeChanged((AppState)modeButtonGroup->checkedId());
}