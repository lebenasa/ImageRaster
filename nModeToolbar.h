#pragma once
#include "qtoolbar.h"
class nModeToolbar :
	public QToolBar
{
	Q_OBJECT
	QIcon Icon_LineMarker;
	QIcon Icon_RectMarker;
	QIcon Icon_CircleMarker;
	QIcon Icon_LineRuler;
	QIcon Icon_RectRuler;
	QIcon Icon_CircleRuler;
	QIcon Icon_TwoCircleRuler;
	QIcon Icon_PolyRuler;

	QToolButton selectButton;
	QToolButton markerButton;
	QToolButton rulerButton;
	QToolButton calibButton;
	QButtonGroup *modeButtonGroup;

	QMenu markerMenu;
	QAction arrMarker;
	QAction circleMarker;
	QAction rectMarker;

	QMenu rulerMenu;
	QAction lineRuler;
	QAction rectRuler;
	QAction circleRuler;
	QAction circle2Ruler;
	QAction polyRuler;

	QAction *activeRuler;
	QAction *activeMarker;

public:
	nModeToolbar(const QString &title, QWidget *parent=0);
	~nModeToolbar();
	RulerState rState;

public slots:
	void rulerButton_changed();
	void markerButton_changed();
	void modeButtonGroup_Clicked(int);

signals:
	void ModeChanged(AppState);
	void RulerChanged(RulerState);
	void MarkerChanged(MarkerState);
};