#pragma once
#include "qdockwidget.h"
#include "ui_RulerDock.h"
#include "ui_MarkerDock.h"

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
