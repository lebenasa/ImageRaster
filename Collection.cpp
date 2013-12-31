#include "stdafx.h"
#include "Collection.h"

int Converter::ToInt(const char* val) {
	return QString(val).toInt();
}

std::string Converter::ToString(const int val) {
	return QString().setNum(val).toStdString();
}
