#pragma once
#include "qgraphicsitem.h"

//Custom Item:
class SimpleTextItem :
	public QGraphicsSimpleTextItem
{
	QGraphicsRectItem *frame;
public:
	SimpleTextItem(const QString& txt, QGraphicsItem *parent=0);

	enum { Type = UserType + 23 };
	int type() const { return Type; }

	void setText(const QString& txt);
};

class EventHandler;
class TextItem :
	public QGraphicsTextItem
{
	EventHandler* handle;
public:
	TextItem(EventHandler* handler, const QString& txt, QGraphicsItem* parent=0);
	
	enum { Type = UserType + 24 };
	int type() const { return Type; }

protected:
	void keyReleaseEvent(QKeyEvent* event);
};

class EventHandler
{
public:
	EventHandler();
	virtual void keyRelease(QKeyEvent* event) = 0;
};

//Markers:
class Marker :
	public mData,
	public Container,
	public Format
{
public:
	Marker(Container* branch=0):
		Container(branch), mData(), Format() { }
	~Marker() { }
};

class Arrow :
	public QGraphicsLineItem
{
	std::vector<QLineF> lines;
	std::vector<QLineF> compose();

public:
	Arrow(const QLineF& l, QGraphicsItem *parent=0, int arrowhead=(int)Both);
	~Arrow(void);

	enum { Type = UserType + 1 };
	int type() const { return Type; }

	enum ArrowHead {
		Start, End, Both
	} arrowHead;

	virtual QRectF boundingRect() const;

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget = 0);

	virtual QPainterPath shape() const;
};

class ArrowMarker :
	public Arrow,
	public Marker
{
	Arrow *bgA;
	QGraphicsSimpleTextItem *myText;
	QLineF load_oneClickLine(const QLineF& l);
protected:
	virtual QPointF textBaseline() const;
public:
	ArrowMarker(const QLineF& l, Container *branch=0);
	~ArrowMarker() { }

	enum { Type = UserType + 2 };
	int type() const { return Type; }

	QRectF boundingRect() const;

	QPainterPath shape() const;

	void setLabel(const QString& txt) override {
		myLabel = txt;
		myText->setText(txt);
	}
	void setFont(const QFont& f) override {
		myFont = f;
		myText->setFont(f);
	}

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);

};

class RectMarker :
	public ArrowMarker
{
	QGraphicsRectItem* bg;
	QGraphicsRectItem* fg;
	QLineF calculateMarkerLine(const QRectF&);
	QRectF testOneClick(const QRectF&) const;
public:
	RectMarker(const QRectF& r,	Container *branch=0, QGraphicsItem *parent=0);
	~RectMarker() { }

	enum { Type = UserType + 3 };
	int type() const { return Type; }

	QRectF boundingRect() const;

	QPainterPath shape() const;

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);
};

class CircleMarker :
	public ArrowMarker
{
	QGraphicsEllipseItem* bg;
	QGraphicsEllipseItem* fg;
	QLineF calculateMarkerLine(const QRectF&);
	QRectF testOneClick(const QRectF&) const;
public:
	CircleMarker(const QRectF& r,	Container *branch=0, QGraphicsItem *parent=0);
	~CircleMarker() { }

	enum { Type = UserType + 4 };
	int type() const { return Type; }

	QRectF boundingRect() const;

	QPainterPath shape() const;

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);
};

//Rulers:
class Ruler :
	public rData,
	public Format,
	public Container
{
public:
	Ruler(Container* branch=0):
		Container(branch), rData(), Format() { }
	~Ruler() { }
};

class LineRuler:
	public Ruler,
	public Arrow
{
	bool showArrow;
protected:
	Arrow* bg;
	QGraphicsSimpleTextItem* myText;
	virtual QPointF calculateTextPos() const;
public:
	LineRuler(const QLineF& l, Container* parent=0);
	~LineRuler();

	enum { Type = UserType + 5 };
	int type() const { return Type; }

	QRectF boundingRect() const;

	QPainterPath shape() const;

	QString text() const { return myText->text(); }
	void setText(const QString& txt);
	virtual QString defaultText() const;

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);

	void setFont(const QFont& f);
};

class RectRuler:
	public LineRuler
{
	QGraphicsRectItem *myRect, *bgR;
protected:
	QPointF calculateTextPos() const override;
public:
	RectRuler(const QRectF& r, Container* parent=0);
	
	enum { Type = UserType + 6 };
	int type() const { return Type; }

	QRectF boundingRect() const;

	QPainterPath shape() const;

	QString defaultText() const override;

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);

	QRectF rect() const { return myRect->rect(); }
};

class CircleRuler:
	public LineRuler
{
	QGraphicsEllipseItem *myRect, *bgR;
	QPointF p1, p2, p3;
protected:
	QPointF calculateTextPos() const override;
public:
	CircleRuler(const QRectF& r, Container* parent=0);
	
	enum { Type = UserType + 7 };
	int type() const { return Type; }

	QRectF boundingRect() const;

	QPainterPath shape() const;

	QString defaultText() const override;

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);

	QRectF rect() const { return myRect->rect(); }

	void setOriginal(const QPointF& pa, const QPointF& pb, const QPointF& pc);
	QList<QPointF> original() const;

	void setRect(const QRectF& r);
};

class Circle2Ruler:
	public LineRuler
{
	QGraphicsEllipseItem *myRect1, *bgR1;
	QGraphicsEllipseItem *myRect2, *bgR2;
	QLineF lineFrom2Rect(const QRectF& r1, const QRectF& r2);
	QList<QPointF> origin_points;
public:
	Circle2Ruler(const QRectF& r1, const QRectF& r2, Container* parent=0);
	
	enum { Type = UserType + 8 };
	int type() const { return Type; }

	QRectF boundingRect() const;

	QPainterPath shape() const;

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);

	void setOriginal(const QPointF& pa, const QPointF& pb, const QPointF& pc,
		const QPointF& pd, const QPointF& pe, const QPointF& pf);
	QList<QPointF> original() const;

	void setRect(const QRectF& r1, const QRectF& r2);
};

class PolyRuler:
	public LineRuler
{
	QGraphicsPolygonItem *myRect, *bgR;
protected:
	QPointF calculateTextPos() const override;
public:
	PolyRuler(const QPolygonF& r, Container* parent=0);
	
	enum { Type = UserType + 9 };
	int type() const { return Type; }

	QRectF boundingRect() const;

	QPainterPath shape() const;

	QString defaultText() const override;

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);

	QPolygonF rect() { return myRect->polygon(); }
};

class LineItem:
	public QGraphicsLineItem
{
	//Convenient line with background
	QGraphicsLineItem *bg;
	QPen pen1, pen2;
public:
	LineItem(const QLineF& l, QGraphicsItem* parent=0);
	~LineItem() { }

	enum { Type = UserType + 10 };
	int type() const { return Type; }

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);
};

//Scale:
class SimpleScale:
	public LineItem
{
	QGraphicsSimpleTextItem *text1, *text2;
	LineItem *tick1, *tick2;
	QPen pen1, pen2;
public:
	SimpleScale(const QLineF& l, QGraphicsItem* parent=0);
	~SimpleScale() { }

	enum { Type = UserType + 11 };
	int type() const { return Type; }

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);

	void setText(const QString& t1, const QString& t2);
};

class BarScale:
	public LineItem
{
	QGraphicsSimpleTextItem *text1, *text2;
	QList<QGraphicsLineItem*> stripes;
	QPen pen1, pen2;
public:
	BarScale(const QLineF& l, QGraphicsItem* parent=0);
	~BarScale() { }

	enum { Type = UserType + 12 };
	int type() const { return Type; }

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);

	void setText(const QString& t1, const QString& t2);
};

class RulerScale:
	public SimpleScale
{
	QList<LineItem*> ticks;
public:
	RulerScale(const QLineF& l, QGraphicsItem* parent=0);
	~RulerScale() { }

	enum { Type = UserType + 13 };
	int type() const { return Type; }

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);
};

//Legend:
class MarkerModel;
class LegendItem:
	public QGraphicsRectItem,
	public EventHandler
{
	QList<QGraphicsEllipseItem*> marks;
	QList<TextItem*> texts;
	MarkerModel* model;
	QRectF generateRect() const;
public:
	LegendItem(MarkerModel* m, const QPointF& origin = QPointF(0, 0), QGraphicsItem* parent=0);
	~LegendItem() {}

	enum { Type = UserType + 14 };
	int type() const { return Type; }

	void updateRect();
	void keyRelease(QKeyEvent*);
};

//Blend:
class RectItem:
	public QGraphicsRectItem,
	public Format
{
	QGraphicsRectItem *bg;
public:
	RectItem(const QRectF& r, QGraphicsItem* parent=0);
	~RectItem() { }

	enum { Type = UserType + 15 };
	int type() const { return Type; }

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);
};

class CircleItem:
	public QGraphicsEllipseItem,
	public Format
{
	QGraphicsEllipseItem* bg;
public:
	CircleItem(const QRectF& r, QGraphicsItem* parent=0);
	~CircleItem() { }

	enum { Type = UserType + 16 };
	int type() const { return Type; }

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);
};

class FrameRect:
	public RectItem
{
	QPixmap myPix;
public:
	FrameRect(const QPixmap& pix, const QRectF& r, QGraphicsItem* parent=0);
	~FrameRect() { }

	enum { Type = UserType + 17 };
	int type() const { return Type; }

	virtual void setPix(const QPixmap& pix) = 0;
	QPixmap pix() const { return myPix; }
};

class FrameCircle:
	public CircleItem
{
	QPixmap myPix;
public:
	FrameCircle(const QPixmap& pix, const QRectF& r, QGraphicsItem* parent=0);
	~FrameCircle() { }

	enum { Type = UserType + 18 };
	int type() const { return Type; }

	virtual void setPix(const QPixmap& pix) = 0;
	QPixmap pix() const { return myPix; }
};

class ClipRect:
	public FrameRect
{
public:
	ClipRect(const QPixmap& pix, const QRectF& r, QGraphicsItem* parent=0);

	enum { Type = UserType + 19 };
	int type() const { return Type; }

	void setPix(const QPixmap& pix);
};

class ClipCircle:
	public FrameCircle
{
public:
	ClipCircle(const QPixmap& pix, const QRectF& r, QGraphicsItem* parent=0);

	enum { Type = UserType + 20 };
	int type() const { return Type; }

	void setPix(const QPixmap& pix);
};

class FitRect:
	public FrameRect
{
public:
	FitRect(const QPixmap& pix, const QRectF& r, QGraphicsItem* parent=0);

	enum { Type = UserType + 21 };
	int type() const { return Type; }

	void setPix(const QPixmap& pix);
};

class FitCircle:
	public FrameCircle
{
public:
	FitCircle(const QPixmap& pix, const QRectF& r, QGraphicsItem* parent=0);

	enum { Type = UserType + 22 };
	int type() const { return Type; }

	void setPix(const QPixmap& pix);
};

