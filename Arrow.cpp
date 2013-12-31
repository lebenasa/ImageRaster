#include "stdafx.h"
#include "Arrow.h"
#include <math.h>

//Class Arrow
Arrow::Arrow(const QLineF& l, QGraphicsItem *parent, int arrowhead) : 
		QGraphicsLineItem(l, parent)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	arrowHead = (ArrowHead)arrowhead;
	lines = compose();
}

Arrow::~Arrow(void)
{
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget) {
	QGraphicsLineItem::paint(painter, option, widget);
	for (auto l : lines) {
		QGraphicsLineItem arrow(l);
		arrow.setPen(pen());
		arrow.paint(painter, option, widget);
	}
}

QPainterPath Arrow::shape() const {
	QPainterPath path = QGraphicsLineItem::shape();
	for (auto l : lines)
		path.addPath(QGraphicsLineItem(l).shape());
	return path;
}

QRectF Arrow::boundingRect() const {
	QLineF l = line();
	double arrowSize = (l.length() < 40.0) ? 2.0 : l.length()/20.0;
	double extra = (pen().width() + ::sin(3.14/3.0) * arrowSize) / 2.0;
	QPointF p1 = l.p1();
	QPointF p2 = l.p2();
	return QRectF(p1, QSizeF(p2.x() - p1.x(), p2.y() - p1.y())).normalized().adjusted(-extra, -extra, extra, extra);
}

std::vector<QLineF> Arrow::compose() {
	const qreal pi = 3.14;
	QLineF l = QLineF(line());
	double arrowSize = (l.length() < 40.0) ? 2.0 : l.length()/20.0;
	int dx = l.p2().x() - l.p1().x();
	int dy = l.p2().y() - l.p1().y();
	double angle = ::acos(dx/l.length());
	if (dx >= 0 && dy > 0)
		angle = (pi * 2) - angle;
	else if (dx >= 0 && dy <= 0)
		{ }
	else if (dx < 0 && dy > 0)
		angle = (pi * 2) - angle;
	else if (dx < 0 && dy <= 0)
		{ }
	QPointF P1 = l.p1() + QPointF(::sin(angle+pi/3.0)*arrowSize, ::cos(angle+pi/3.0)*arrowSize);
	QPointF P2 = l.p1() + QPointF(::sin(angle+pi-pi/3.0)*arrowSize, ::cos(angle+pi-pi/3.0)*arrowSize);
	QPointF P3 = l.p2() + QPointF(::sin(angle-pi/3.0)*arrowSize, ::cos(angle-pi/3.0)*arrowSize);
	QPointF P4 = l.p2() + QPointF(::sin(angle+pi+pi/3.0)*arrowSize, ::cos(angle+pi+pi/3.0)*arrowSize);

	std::vector<QLineF> cont;
	if (arrowHead == Arrow::Start) {
		cont.push_back(QLineF(l.p1(), P1));
		cont.push_back(QLineF(l.p1(), P2));
	}
	else if (arrowHead == Arrow::End) {
		cont.push_back(QLineF(l.p2(), P3));
		cont.push_back(QLineF(l.p2(), P4));
	}
	else if (arrowHead == Arrow::Both) {
		cont.push_back(QLineF(l.p1(), P1));
		cont.push_back(QLineF(l.p1(), P2));
		cont.push_back(QLineF(l.p2(), P3));
		cont.push_back(QLineF(l.p2(), P4));
	}
	return cont;
}

//Class ArrowMarker
ArrowMarker::ArrowMarker(const QLineF& l, Container *branch) : 
	Arrow((l.length() > 10) ? l : load_oneClickLine(l), (QGraphicsItem*)0, (int)ArrowHead::Start),
	Marker(branch)
{
	bgA = new Arrow(line(), this, (int)ArrowHead::Start);
	bgA->setFlag(QGraphicsItem::ItemStacksBehindParent);
	myText = new QGraphicsSimpleTextItem(this);
	myText->setPos(textBaseline());
}

QLineF ArrowMarker::load_oneClickLine(const QLineF& l) {
	return QLineF(l.p1(), l.p1()+QPointF(10, 10));
}

QPointF ArrowMarker::textBaseline() const {
	QLineF l(line());
	QRectF bound = myText->boundingRect();
	int dx = l.p2().x() - l.p1().x();
	int dy = l.p2().y() - l.p1().y();
	QPointF pos = l.p2();
	QPointF offset(0, 0);
	if (dx >= 0 && dy <=0) {

	}
	else if (dx >= 0 && dy <= 0) {
		offset.setX(0);
		offset.setY(-bound.height());
	}
	else if (dx < 0 && dy > 0) {
		offset.setX(-bound.width());
		offset.setY(0);
	}
	else if (dx < 0 && dy <= 0) {
		offset.setX(-bound.width());
		offset.setY(-bound.height());
	}
	return pos + offset;
}

QRectF ArrowMarker::boundingRect() const {
	QLineF l = line();
	QRectF tb = myText->boundingRect();
	QRectF b(textBaseline(), QSizeF(tb.width(), tb.height()));
	double arrowSize = (l.length() < 200.0) ? 10.0 : l.length()/20.0;
	double extra = (pen1().width() + ::sin(3.14/3.0) * arrowSize) / 2.0;
	QPointF p1 = l.p1();
	QPointF p2 = l.p2();
	QRectF base = QRectF(p1, QSizeF(p2.x() - p1.x(), p2.y() - p1.y())).normalized();
	QRectF bound = base.united(b).normalized().adjusted(-extra, -extra, extra, extra);
	return bound;
}

QPainterPath ArrowMarker::shape() const {
	QPainterPath path = Arrow::shape();
	path.addPath(myText->shape());
	return path;
}

void ArrowMarker::setPen1(const QPen& p) {
	Format::setPen1(p);
	Arrow::setPen(p);
	myText->setBrush(p.color());
	setPen2(pen2());
}

void ArrowMarker::setPen2(const QPen& p) {
	Format::setPen2(p);
	QPen pen = p;
	pen.setWidth(pen1().width()+1);
	bgA->setPen(pen);
}

//Class RectMarker
RectMarker::RectMarker(const QRectF& r, Container *branch, QGraphicsItem *parent) :
	ArrowMarker(calculateMarkerLine(testOneClick(r)), branch)
{
	bg = new QGraphicsRectItem(testOneClick(r), this);
	fg = new QGraphicsRectItem(testOneClick(r), this);
	QPen p = pen2();
	p.setWidth(pen1().width()+1);
	bg->setPen(p);
	fg->setPen(pen1());
}

QLineF RectMarker::calculateMarkerLine(const QRectF& r) {
	//Return a line starts from bottomRight() to += 10
	QPointF br = r.bottomRight();
	return QLineF(br, br + QPointF(10, 10));
}

QRectF RectMarker::testOneClick(const QRectF& r) const {
	if (r.width() <= 20.0 && r.height() <= 20.0)
		return QRectF(r.topLeft()-QPointF(10,10), QSizeF(20, 20));
	else
		return r;
}

QRectF RectMarker::boundingRect() const {
	QRectF b = ArrowMarker::boundingRect();
	double extra = pen1().width();
	return b.united(bg->boundingRect()).adjusted(-extra, -extra, extra, extra);
}

QPainterPath RectMarker::shape() const {
	QPainterPath path = ArrowMarker::shape();
	path.addPath(bg->shape());
	return path;
}

void RectMarker::setPen1(const QPen& p) {
	ArrowMarker::setPen1(p);
	fg->setPen(ArrowMarker::pen1());
}

void RectMarker::setPen2(const QPen& p) {
	QPen p2 = QPen(p);
	p2.setWidth(pen1().width()+1);
	ArrowMarker::setPen2(p2);
	bg->setPen(ArrowMarker::pen2());
}

//Class CircleMarker
CircleMarker::CircleMarker(const QRectF& r,	Container *branch, QGraphicsItem *parent) :
	ArrowMarker(calculateMarkerLine(testOneClick(r)), branch)
{
	bg = new QGraphicsEllipseItem(testOneClick(r), this);
	fg = new QGraphicsEllipseItem(testOneClick(r), this);
	QPen p = pen2();
	p.setWidth(pen1().width()+1);
	bg->setPen(p);
	fg->setPen(pen1());
	bg->setFlag(QGraphicsItem::ItemIsSelectable, true);
	fg->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QLineF CircleMarker::calculateMarkerLine(const QRectF& r) {
	//Return a line starts from bottomRight() to += 10
	QPointF br = r.bottomRight();
	return QLineF(br, br + QPointF(10, 10));
}

QRectF CircleMarker::testOneClick(const QRectF& r) const {
	if (r.width() <= 20.0 && r.height() <= 20.0)
		return QRectF(r.topLeft()-QPointF(10,10), QSizeF(20, 20));
	else
		return r;
}

QRectF CircleMarker::boundingRect() const {
	QRectF b = ArrowMarker::boundingRect();
	double extra = pen1().width();
	return b.united(bg->boundingRect()).adjusted(-extra, -extra, extra, extra);
}

QPainterPath CircleMarker::shape() const {
	QPainterPath path = ArrowMarker::shape();
	path.addPath(bg->shape());
	return path;
}

void CircleMarker::setPen1(const QPen& p) {
	ArrowMarker::setPen1(p);
	fg->setPen(ArrowMarker::pen1());
}

void CircleMarker::setPen2(const QPen& p) {
	QPen p2 = QPen(p);
	p2.setWidth(pen1().width()+1);
	ArrowMarker::setPen2(p2);
	bg->setPen(ArrowMarker::pen2());
}

//Class LineRuler
LineRuler::LineRuler(const QLineF& l, Container* parent) :
	Arrow(l),
	Ruler(parent)
{
	myText = new QGraphicsSimpleTextItem(this);
	bg = new Arrow(l, this);
	myText->setFont(myFont);
	myText->setBrush(QBrush(myInPen.color()));
	//myText->setFlag(QGraphicsItem::ItemIsSelectable);

	QPen p = myOutPen;
	p.setWidth(myInPen.width()+1);
	bg->setPen(p);
	setFlag(QGraphicsItem::ItemIsSelectable);

	myText->setPos(calculateTextPos());
	bg->setFlag(QGraphicsItem::ItemStacksBehindParent);
}

LineRuler::~LineRuler() {
}

void LineRuler::setText(const QString& txt) {
	myText->setText(txt);
	myText->setPos(calculateTextPos());
}

QString LineRuler::defaultText() const {
	return QString().setNum(length()) + QString::fromLatin1(" µm");
}

QPointF LineRuler::calculateTextPos() const {
	QRectF bound = myText->boundingRect();
	int dx = line().p2().x() - line().p1().x();
	int dy = line().p2().y() - line().p1().y();
	QPointF pos = QPointF(line().x1() + dx/2,
		line().y1() + dy/2);
	QPointF offset = QPointF(0, 0);
	if (bound.width() < line().length()) {
		if (dx >= 0 && dy > 0) {
			if (dy == dx)
				offset.setY(-bound.height());
			else if (dy > dx)
				offset = QPointF(0, -bound.height());
			else if (dy < dx)
				offset = QPointF(-bound.width(), bound.height());
		}
		else if (dx >= 0 && dy <= 0) {
			//offset.setX(bound.width()/2);
		}
		else if (dx < 0 && dy > 0) {
			//offset.setX((dy > -1.0*dx) ? 0 : -bound.width()/2);
			//offset.setY((dy < -1.0*dx) ? bound.height() : 0);
			//offset.setX((dy == -1.0*dx) ? 0 : offset.x());
		}
		else if (dx < 0 && dy <= 0) {
			if (dy == dx)
				offset.setY(-bound.height());
			else if (dy < dx)
				offset = QPointF(0, -bound.height());
			else if (dy > dx)
				offset = QPointF(-bound.width(), bound.height());
		}
	}
	else {
		pos = bg->boundingRect().bottomRight();
		offset = QPointF(0, -bound.height());
	}
	return pos + offset;
}

QRectF LineRuler::boundingRect() const {
	QRectF bound = bg->boundingRect();
	double extra = pen1().width();
	QRectF tb = myText->boundingRect();
	QRectF b = QRectF(calculateTextPos(), tb.size());
	return bound.united(b).normalized().adjusted(-extra, -extra, extra, extra);
}

QPainterPath LineRuler::shape() const {
	QPainterPath path = Arrow::shape();
	path.addPath(myText->shape());
	return path;
}

void LineRuler::setPen1(const QPen& p) {
	Format::setPen1(p);
	Arrow::setPen(p);
	myText->setBrush(p.color());
}

void LineRuler::setPen2(const QPen& p) {
	Format::setPen2(p);
	QPen pen = p;
	pen.setWidth(pen1().width()+1);
	bg->setPen(pen);
}

void LineRuler::setFont(const QFont& f) {
	Format::setFont(f);
	myText->setFont(f);
}

//class RectRuler
RectRuler::RectRuler(const QRectF& r, Container* parent) :
	LineRuler(QLineF(r.bottomLeft(), r.bottomRight()), parent)
{
	this->setFlag(QGraphicsItem::ItemHasNoContents);
	LineRuler::bg->setFlag(QGraphicsItem::ItemHasNoContents);
	bgR = new QGraphicsRectItem(r, this);
	myRect = new QGraphicsRectItem(r, this);
	myRect->setFlag(QGraphicsItem::ItemIsSelectable);
	myText->setPos(calculateTextPos());
}

QPointF RectRuler::calculateTextPos() const {
	QPointF bl = myRect->boundingRect().bottomLeft();
	bl.setX(bl.x() + myRect->boundingRect().width()/2 - myText->boundingRect().width()/2);
	bl.setY(bl.y() + 10);
	return bl;
}

QRectF RectRuler::boundingRect() const {
	QRectF bound = myRect->boundingRect();
	double extra = pen1().width();
	QRectF tb = myText->boundingRect();
	QRectF b = QRectF(calculateTextPos(), tb.size());
	return bound.united(b).adjusted(-extra, -extra, extra, extra);
}

QPainterPath RectRuler::shape() const {
	QPainterPath path = myRect->shape();
	path.addPath(myText->shape());
	return path;
}

QString RectRuler::defaultText() const {
	QString w = "Width:  " + QString().setNum(width()) + QString::fromLatin1(" µm") + "\n";
	QString h = "Height: " + QString().setNum(height()) + QString::fromLatin1(" µm") + "\n";
	//QString a = "Area:   " + QString().setNum(area()) + QString::fromLatin1(" (µm²)");
	return w+h;
}

void RectRuler::setPen1(const QPen& p) {
	LineRuler::setPen1(p);
	myRect->setPen(p);
}

void RectRuler::setPen2(const QPen& p) {
	LineRuler::setPen2(p);
	QPen pen = p;
	pen.setWidth(pen1().width()+1);
	bgR->setPen(pen);
}

//class CircleRuler
CircleRuler::CircleRuler(const QRectF& r, Container* parent) :
	LineRuler(QLineF(r.bottomLeft(), r.bottomRight()), parent)
{
	this->setFlag(QGraphicsItem::ItemHasNoContents);
	LineRuler::bg->setFlag(QGraphicsItem::ItemHasNoContents);
	bgR = new QGraphicsEllipseItem(r, this);
	myRect = new QGraphicsEllipseItem(r, this);
	myRect->setFlag(QGraphicsItem::ItemIsSelectable);
	myText->setPos(calculateTextPos());
}

QPointF CircleRuler::calculateTextPos() const {
	QPointF bl = myRect->boundingRect().bottomLeft();
	bl.setX(bl.x() + myRect->boundingRect().width()/2 - myText->boundingRect().width()/2);
	bl.setY(bl.y() + 10);
	return bl;
}

QRectF CircleRuler::boundingRect() const {
	return myRect->boundingRect().united(myText->boundingRect());
}

QPainterPath CircleRuler::shape() const {
	QPainterPath path = myRect->shape();
	path.addPath(myText->shape());
	return path;
}

QString CircleRuler::defaultText() const {
	return "Radius:  " + QString().setNum(radius()) + QString::fromLatin1(" µm");
}

void CircleRuler::setPen1(const QPen& p) {
	LineRuler::setPen1(p);
	myRect->setPen(p);
}

void CircleRuler::setPen2(const QPen& p) {
	LineRuler::setPen2(p);
	QPen pen = p;
	pen.setWidth(pen1().width()+1);
	bgR->setPen(pen);
}

//class Circle2Ruler
Circle2Ruler::Circle2Ruler(const QRectF& r1, const QRectF& r2, Container* parent):
	LineRuler(lineFrom2Rect(r1, r2))
{
	bgR1 = new QGraphicsEllipseItem(r1, this);
	bgR2 = new QGraphicsEllipseItem(r2, this);
	myRect1 = new QGraphicsEllipseItem(r1, this);
	myRect2 = new QGraphicsEllipseItem(r2, this);
	bgR1->setFlag(QGraphicsItem::ItemStacksBehindParent);
	bgR2->setFlag(QGraphicsItem::ItemStacksBehindParent);
	myRect1->setFlag(QGraphicsItem::ItemStacksBehindParent);
	myRect2->setFlag(QGraphicsItem::ItemStacksBehindParent);
}

QLineF Circle2Ruler::lineFrom2Rect(const QRectF& r1, const QRectF& r2) {
	QPointF p1 = r1.topLeft() + QPointF(r1.width()/2, r1.height()/2);
	QPointF p2 = r2.topLeft() + QPointF(r2.width()/2, r2.height()/2);
	return QLineF(p1, p2);
}

QRectF Circle2Ruler::boundingRect() const {
	QRectF bound = LineRuler::boundingRect();
	return bound.united(myRect1->boundingRect()).united(myRect2->boundingRect());
}

QPainterPath Circle2Ruler::shape() const {
	QPainterPath path = LineRuler::shape();
	path.addPath(myRect1->shape());
	path.addPath(myRect2->shape());
	return path;
}

void Circle2Ruler::setPen1(const QPen& p) {
	LineRuler::setPen1(p);
	myRect1->setPen(p);
	myRect2->setPen(p);
}

void Circle2Ruler::setPen2(const QPen& p) {
	LineRuler::setPen2(p);
	QPen pen = p;
	pen.setWidth(pen1().width()+1);
	bgR1->setPen(pen);
	bgR2->setPen(pen);
}

//class PolyRuler
PolyRuler::PolyRuler(const QPolygonF& r, Container* parent) :
	LineRuler(QLineF(), parent)
{
	this->setFlag(QGraphicsItem::ItemHasNoContents);
	LineRuler::bg->setFlag(QGraphicsItem::ItemHasNoContents);
	bgR = new QGraphicsPolygonItem(r, this);
	myRect = new QGraphicsPolygonItem(r, this);
	myRect->setFlag(QGraphicsItem::ItemIsSelectable);
	myText->setPos(calculateTextPos());
}

QPointF PolyRuler::calculateTextPos() const {
	QPointF bl = myRect->boundingRect().bottomLeft();
	bl.setX(bl.x() + myRect->boundingRect().width()/2 - myText->boundingRect().width()/2);
	bl.setY(bl.y() + 10);
	return bl;
}

QRectF PolyRuler::boundingRect() const {
	return myRect->boundingRect().united(myText->boundingRect());
}

QPainterPath PolyRuler::shape() const {
	QPainterPath path = myRect->shape();
	path.addPath(myText->shape());
	return path;
}

QString PolyRuler::defaultText() const {
	return "Area:  " + QString().setNum(area()) + QString::fromLatin1(" µm²");
}

void PolyRuler::setPen1(const QPen& p) {
	LineRuler::setPen1(p);
	myRect->setPen(p);
}

void PolyRuler::setPen2(const QPen& p) {
	LineRuler::setPen2(p);
	QPen pen = p;
	pen.setWidth(pen1().width()+1);
	bgR->setPen(pen);
}
