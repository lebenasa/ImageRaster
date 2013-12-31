#include "stdafx.h"
#include "Collection.h"

int Converter::ToInt(const char* val) {
	return QString(val).toInt();
}

std::string Converter::ToString(const int val) {
	return QString().setNum(val).toStdString();
}

void rData::setMod(const Unit& u) {
	if (Unit::Micrometer == u)
		modifier = 1.0;
	else if (Unit::Milimeter == u)
		modifier = 0.001;
	else if (Unit::Centimeter == u)
		modifier = 0.0001;
	else if (Unit::Meter == u)
		modifier = 0.000001;
}

QString rData::unit() const {
	if (modifier == 1.0)
		return QString::fromLatin1(" µm");
	else if (modifier == 0.001)
		return " mm";
	else if (modifier == 0.0001)
		return " cm";
	else if (modifier == 0.000001)
		return " m";
	return QString::fromLatin1(" µm");
}
