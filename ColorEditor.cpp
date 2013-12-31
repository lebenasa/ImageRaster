#include "stdafx.h"
#include "ColorEditor.h"

ColorEditor::ColorEditor(QWidget* widget) :
	QComboBox(widget)
{
	populateList();
}

QColor ColorEditor::color() const {
	return qvariant_cast<QColor>(itemData(currentIndex(), Qt::DecorationRole));
}

void ColorEditor::setColor(QColor c) {
	setCurrentIndex(findData(c, int(Qt::DecorationRole)));
}

void ColorEditor::populateList() {
	QStringList colorNames = QColor::colorNames();
	for (int i=0; i<colorNames.size(); ++i) {
		QColor color(colorNames[i]);
		insertItem(i, colorNames[i]);
		setItemData(i, color, Qt::DecorationRole);
	}
}
