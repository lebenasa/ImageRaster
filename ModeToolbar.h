#pragma once
#include "qtoolbar.h"
class ModeToolbar :
	public QToolBar
{
	Q_OBJECT
public:
	ModeToolbar(const QString &title, QWidget *parent=0);
	~ModeToolbar(void);

private:
	void createMe();

	QIcon Icon_LineMarker;
	QIcon Icon_RectMarker;
	QIcon Icon_CircleMarker;
	QIcon Icon_LineRuler;
	QIcon Icon_RectRuler;
	QIcon Icon_CircleRuler;
	QIcon Icon_TwoCircleRuler;
	QIcon Icon_PolyRuler;

	QToolButton *markerButton;
	QToolButton *rulerButton;
	QButtonGroup *modeButtonGroup;

public slots:
	void rulerButton_changed();
	void markerButton_changed();
	void modeButtonGroup_Clicked();

signals:
	void ModeChanged(AppState);
	void RulerChanged(RulerState);
	void MarkerChanged(MarkerState);
};

