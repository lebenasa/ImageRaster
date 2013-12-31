#define QT_NO_OPENGL
#include <vector>
#include <QtWidgets>
#include <qstringbuilder.h>
#include "Collection.h"

//These enumerators were used to transfer data not to describe a class, thus
//I'd put their definition here:

enum class AppState {
	//Explanation of these enum is written in Image Raster Qt5 Again note
	Select, Marker, Ruler, Calibration
};

enum class MarkerState {
	Arrow, Circle, Rectangle
};

enum class RulerState {
	Line, Rectangle, Circle, Circle2, Polygon
};

enum class MouseState {
	Click, Move, Release
};