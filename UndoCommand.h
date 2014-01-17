#pragma once
#include "qundostack.h"

class ImageRaster;
class RasterScene;
class MarkerBranch;
class MarkerModel;
class ArrowMarker;
class Marker;
class RulerModel;
class LineRuler;
class RectRuler;
class CircleRuler;
class Circle2Ruler;
class PolyRuler;

class AddItem :
	public QUndoCommand
{
	Marker* item;
	RasterScene* scene;
	MarkerBranch* branch;
public:
	AddItem(Marker* graphicsItem, RasterScene* scn, MarkerBranch* brc, QUndoCommand* parent=0);
	~AddItem();

	void undo();
	void redo();
};

class AddMarker :
	public QUndoCommand
{
	MarkerModel* model;
	ImageRaster* raster;
public:
	AddMarker(MarkerModel* m, ImageRaster* p, QUndoCommand* parent=0);

	void undo();
	void redo();
};

class RemoveMarker:
	public QUndoCommand
{
	MarkerModel* model;
	int index;
	ImageRaster* raster;
	MarkerBranch* branch;
	QList<ArrowMarker*>items;
public:
	RemoveMarker(MarkerModel* m, int i, ImageRaster* p, QUndoCommand* parent=0);

	void undo();
	void redo();
};

class LabelChg:
	public QUndoCommand
{
	MarkerBranch* branch;
	QString oldValue;
	QString newValue;
public:
	LabelChg(MarkerBranch*, const QString&, const QString&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 1; }
	//bool mergeWith(const QUndoCommand* other);
};

class Color1Chg:
	public QUndoCommand
{
	MarkerBranch* branch;
	QColor oldValue;
	QColor newValue;
public:
	Color1Chg(MarkerBranch*, const QColor&, const QColor&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 2; }
	//bool mergeWith(const QUndoCommand* other);
};

class Color2Chg:
	public QUndoCommand
{
	MarkerBranch* branch;
	QColor oldValue;
	QColor newValue;
public:
	Color2Chg(MarkerBranch*, const QColor&, const QColor&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 3; }
	//bool mergeWith(const QUndoCommand* other);
};

class FontChg:
	public QUndoCommand
{
	MarkerBranch* branch;
	QFont oldValue;
	QFont newValue;
public:
	FontChg(MarkerBranch*, const QFont&, const QFont&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 4; }
	//bool mergeWith(const QUndoCommand* other);
};

class FontSizeChg:
	public QUndoCommand
{
	MarkerBranch* branch;
	int oldValue;
	int newValue;
public:
	FontSizeChg(MarkerBranch*, const int&, const int&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 5; }
	//bool mergeWith(const QUndoCommand* other);
};

class WidthChg:
	public QUndoCommand
{
	MarkerBranch* branch;
	int oldValue;
	int newValue;
public:
	WidthChg(MarkerBranch*, const int&, const int&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 6; }
	//bool mergeWith(const QUndoCommand* other);
};

class Visibility:
	public QUndoCommand
{
	MarkerBranch* branch;
	ImageRaster* raster;
	bool value;
public:
	Visibility(MarkerBranch*, bool, ImageRaster*, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 7; }
	//bool mergeWith(const QUndoCommand* other);
};

class AddRuler :
	public QUndoCommand
{
	RulerModel* model;
	LineRuler* ruler;
protected:
	ImageRaster* parent;
	virtual void update() = 0;
public:
	AddRuler(LineRuler* ruler_, RulerModel* model_, ImageRaster* parent_);
	
	void undo();
	void redo();
};

class AddLineRuler :
	public AddRuler
{
protected:
	void update() override;
public:
	AddLineRuler(LineRuler* ruler_, RulerModel* model_, ImageRaster* parent_);
};

class AddRectRuler :
	public AddRuler
{
protected:
	void update() override;
public:
	AddRectRuler(RectRuler* ruler_, RulerModel* model_, ImageRaster* parent_);
};

class AddCircleRuler :
	public AddRuler
{
protected:
	void update() override;
public:
	AddCircleRuler(CircleRuler* ruler_, RulerModel* model_, ImageRaster* parent_);
};

class AddCircle2Ruler :
	public AddRuler
{
protected:
	void update() override;
public:
	AddCircle2Ruler(Circle2Ruler* ruler_, RulerModel* model_, ImageRaster* parent_);
};

class AddPolyRuler :
	public AddRuler
{
protected:
	void update() override;
public:
	AddPolyRuler(PolyRuler* ruler_, RulerModel* model_, ImageRaster* parent_);
};

class RColor1Chg:
	public QUndoCommand
{
	RulerModel* branch;
	QColor oldValue;
	QColor newValue;
public:
	RColor1Chg(RulerModel*, const QColor&, const QColor&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 2; }
	//bool mergeWith(const QUndoCommand* other);
};

class RColor2Chg:
	public QUndoCommand
{
	RulerModel* branch;
	QColor oldValue;
	QColor newValue;
public:
	RColor2Chg(RulerModel*, const QColor&, const QColor&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 3; }
	//bool mergeWith(const QUndoCommand* other);
};

class RFontChg:
	public QUndoCommand
{
	RulerModel* branch;
	QFont oldValue;
	QFont newValue;
public:
	RFontChg(RulerModel*, const QFont&, const QFont&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 4; }
	//bool mergeWith(const QUndoCommand* other);
};

class RFontSizeChg:
	public QUndoCommand
{
	RulerModel* branch;
	int oldValue;
	int newValue;
public:
	RFontSizeChg(RulerModel*, const int&, const int&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 5; }
	//bool mergeWith(const QUndoCommand* other);
};

class RWidthChg:
	public QUndoCommand
{
	RulerModel* branch;
	int oldValue;
	int newValue;
public:
	RWidthChg(RulerModel*, const int&, const int&, QUndoCommand* parent=0);

	void undo();
	void redo();
	//int id() { return 6; }
	//bool mergeWith(const QUndoCommand* other);
};

class RemoveItems:
	public QUndoCommand
{
	QList<QGraphicsItem*> items;
	QList<QPair<ArrowMarker*, Container*> > markers;
	QMap<int, QList<LineRuler*> > rulers;
	QList<QGraphicsItem*> EE;
	ImageRaster* raster;
public:
	RemoveItems(QList<QGraphicsItem*>, ImageRaster*, QUndoCommand* parent=0);

	void undo();
	void redo();
};