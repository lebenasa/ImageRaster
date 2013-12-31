#pragma once
#include "qcombobox.h"
class ColorEditor :
	public QComboBox
{
Q_OBJECT
	Q_PROPERTY(QColor color READ color WRITE setColor USER true)

	void populateList();
public:
	ColorEditor(QWidget *widget=0);

	QColor color() const;
	void setColor(QColor c);
};

