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