#include "stdafx.h"
#include "imageraster.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageRaster w;
	w.show();
	return a.exec();
}
