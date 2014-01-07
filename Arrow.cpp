#include "stdafx.h"
#include "Arrow.h"
#include "ModelView.h"
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
	double arrowSize = (l.length() < 100.0) ? 5.0 : l.length()/20.0;
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
	Arrow((l.length() > 10.0) ? l : load_oneClickLine(l), (QGraphicsItem*)0, (int)ArrowHead::Start),
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
	QPen tPen = pen;
	tPen.setWidth(1);
	myText->setPen(tPen);
	myText->setBrush(pen1().color());
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
	QPen pen = QPen(p);
	pen.setWidth(pen1().width()+1);
	ArrowMarker::setPen2(pen);
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
	return QString().setNum(length()*mod()) + unit();
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
	QPen tPen = pen;
	tPen.setWidth(1);
	myText->setPen(tPen);
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
	QString w = "Width:\t" + QString().setNum(width()*mod()) + unit() + "\n";
	QString h = "Height:\t" + QString().setNum(height()*mod()) + unit() + "\n";
	QString a = "Area:\t" + QString().setNum(width()*mod()*height()*mod()) + unit() + QString::fromLatin1("²");
	return w+h+a;
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
	QString r = "Radius:\t" + QString().setNum(radius()*mod()) + unit() + "\n";
	QString d = "Diameter:\t" + QString().setNum(radius()*2*mod()) + unit() + "\n";
	QString a = "Area:\t" + QString().setNum(radius()*radius()*3.14*mod()*mod()) + unit() + QString::fromLatin1("²");
	return r+d+a;
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
	QString l = "Length:\t" + QString().setNum(length()*mod()) + unit() + "\n";
	QString a = "Area:\t" + QString().setNum(area()*mod()*mod()) + unit() + QString::fromLatin1("²");
	return l+a;
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

//class LineItem
LineItem::LineItem(const QLineF& l, QGraphicsItem* parent) :
	QGraphicsLineItem(l, parent)
{
	bg = new QGraphicsLineItem(l, this);
	bg->setFlag(QGraphicsItem::ItemStacksBehindParent);
	setPen1(QPen(Qt::black));
	setPen2(QPen(Qt::white));
}

void LineItem::setPen1(const QPen& p) {
	pen1 = p;
	setPen(p);
	setPen2(pen2);
}

void LineItem::setPen2(const QPen& p) {
	pen2 = p;
	pen2.setWidth(pen1.width()+1);
	bg->setPen(pen2);
}

//class SimpleScale
SimpleScale::SimpleScale(const QLineF& l, QGraphicsItem* parent) :
	LineItem(l, parent)
{
	QLineF t1, t2;
	if (l.dx() == 0.0) {
		//vertical line
		t1 = QLineF(l.p1() + QPointF(-10, 0), l.p1() + QPointF(10, 0));
		t2 = QLineF(l.p2() + QPointF(-10, 0), l.p2() + QPointF(10, 0));
	}
	else {
		t1 = QLineF(l.p1() + QPointF(0, -10), l.p1() + QPointF(0, 10));
		t2 = QLineF(l.p2() + QPointF(0, -10), l.p2() + QPointF(0, 10));
	}
	tick1 = new LineItem(t1, this);
	tick2 = new LineItem(t2, this);
	text1 = new QGraphicsSimpleTextItem("0", this);
	text2 = new QGraphicsSimpleTextItem("", this);
}

void SimpleScale::setPen1(const QPen& p) {
	setPen(p);
	tick1->setPen1(p);
	tick2->setPen1(p);
	text1->setBrush(p.color());
	text2->setBrush(p.color());
}

void SimpleScale::setPen2(const QPen& p) {
	LineItem::setPen2(p);
	tick1->setPen2(p);
	tick2->setPen2(p);
}

void SimpleScale::setText(const QString& t1, const QString& t2) {
	text1->setText(t1);
	text2->setText(t2);
	QLineF l = line();
	if (l.dx() == 0.0) {
		//vertical line
		text2->setPos(l.p1() + QPointF(10, -1.0*text1->boundingRect().height()/2));
		text1->setPos(l.p2() + QPointF(10, -1.0*text2->boundingRect().height()/2));
	}
	else {
		text1->setPos(l.p1() + QPointF(-1.0*text1->boundingRect().width()/2, 10));
		text2->setPos(l.p2() + QPointF(-1.0*text2->boundingRect().width()/2, 10));
	}
}

//class BarScale
BarScale::BarScale(const QLineF& l, QGraphicsItem* parent) :
	LineItem(l, parent)
{
	if (l.dx() == 0.0) {
		//vertical line
		for (int i=1; i<=9; i+=2) {
			QLineF li = QLineF(l.p1()+QPointF(0, 0.1*i*l.length()), l.p1()+QPointF(0, 0.1*(i+1)*l.length()));
			QGraphicsLineItem* stripe = new QGraphicsLineItem(li, this);
			stripes.append(stripe);
		}
	}
	else {
		for (int i=1; i<=9; i+=2) {
			QLineF li = QLineF(l.p1()+QPointF(0.1*i*l.length(), 0), l.p1()+QPointF(0.1*(i+1)*l.length(), 0));
			QGraphicsLineItem* stripe = new QGraphicsLineItem(li, this);
			stripes.append(stripe);
		}
	}
	text1 = new QGraphicsSimpleTextItem("0", this);
	text2 = new QGraphicsSimpleTextItem("", this);
	//Default format:
	QPen p1 = QPen(QBrush(Qt::black), 10, Qt::SolidLine, Qt::FlatCap);
	QPen p2 = QPen(QBrush(Qt::white), 10, Qt::SolidLine, Qt::FlatCap);
	setPen(p1);
	LineItem::setPen2(QPen(Qt::transparent));
	for (auto stripe : stripes)
		stripe->setPen(p2);
	text1->setBrush(Qt::black);
	text2->setBrush(Qt::black);
}

void BarScale::setPen1(const QPen& p) {
	setPen(p);
	text1->setBrush(p.color());
	text2->setBrush(p.color());
	for (auto stripe : stripes)
		stripe->setPen(p);
}

void BarScale::setPen2(const QPen& p) {
	LineItem::setPen2(p);
}

void BarScale::setText(const QString& t1, const QString& t2) {
	text1->setText(t1);
	text2->setText(t2);
	QLineF l = line();
	if (l.dx() == 0.0) {
		//vertical line
		text2->setPos(l.p1() + QPointF(10, -1.0*text1->boundingRect().height()/2));
		text1->setPos(l.p2() + QPointF(10, -1.0*text2->boundingRect().height()/2));
	}
	else {
		text1->setPos(l.p1() + QPointF(-1.0*text1->boundingRect().width()/2, 10));
		text2->setPos(l.p2() + QPointF(-1.0*text2->boundingRect().width()/2, 10));
	}
}

//class RulerScale:
RulerScale::RulerScale(const QLineF& l, QGraphicsItem* parent) :
	SimpleScale(l, parent)
{
	//Generate ticks:
	double may = 6.0;
	double mid = 3.0;
	double min = 1.0;
	if (l.dx() == 0.0) {
		//vertical line
		for (int i=0; i<10; ++i) {
			for (int j=1; j<10; ++j) {
				if (j==5) {
					QLineF li = QLineF(l.p1()+QPointF(mid, (0.1*i+0.01*j)*l.length()), l.p1()+QPointF(-mid, (0.1*i+0.01*j)*l.length()));
					LineItem* tick = new LineItem(li, this);
					ticks.append(tick);
					continue;
				}
				QLineF li = QLineF(l.p1()+QPointF(min, (0.1*i+0.01*j)*l.length()), l.p1()+QPointF(-min, (0.1*i+0.01*j)*l.length()));
				LineItem* tick = new LineItem(li, this);
				ticks.append(tick);
			}
			QLineF li = QLineF(l.p1()+QPointF(may, 0.1*i*l.length()), l.p1()+QPointF(-may, 0.1*i*l.length()));
			LineItem* tick = new LineItem(li, this);
			ticks.append(tick);
		}
	}
	else {
		for (int i=0; i<10; ++i) {
			for (int j=1; j<10; ++j) {
				if (j==5) {
					QLineF li = QLineF(l.p1()+QPointF((0.1*i+0.01*j)*l.length(), mid), l.p1()+QPointF((0.1*i+0.01*j)*l.length(), -mid));
					LineItem* tick = new LineItem(li, this);
					ticks.append(tick);
					continue;
				}
				QLineF li = QLineF(l.p1()+QPointF((0.1*i+0.01*j)*l.length(), min), l.p1()+QPointF((0.1*i+0.01*j)*l.length(), -min));
				LineItem* tick = new LineItem(li, this);
				ticks.append(tick);
			}
			QLineF li = QLineF(l.p1()+QPointF(0.1*i*l.length(), may), l.p1()+QPointF(0.1*i*l.length(), -may));
			LineItem* tick = new LineItem(li, this);
			ticks.append(tick);
		}
	}
	setPen2(QPen(Qt::transparent));
}

void RulerScale::setPen1(const QPen& p) {
	SimpleScale::setPen1(p);
	for (auto tick : ticks)
		tick->setPen1(p);
}

void RulerScale::setPen2(const QPen& p) {
	SimpleScale::setPen2(p);
	for (auto tick : ticks)
		tick->setPen2(p);
}

//class LegendItem
LegendItem::LegendItem(MarkerModel* m, const QPointF& origin, QGraphicsItem* parent) :
	QGraphicsRectItem(QRectF(origin, QSizeF(10, 10)), parent)
{
	model = m;
	QList<QString> labels;
	QList<QColor> colors, bgs;
	//Get data from model:
	for (int i=0; i<model->rowCount(); ++i) {
		QString label = model->at(i)->label() + "\t: " + QString().setNum(model->at(i)->count());
		labels.append(label);
		QColor color = model->at(i)->color1();
		colors.append(color);
		QColor bg = model->at(i)->color2();
		bgs.append(bg);
	}
	//Generate marks:
	for (int i=0; i<colors.size(); ++i) {
		QRectF r = QRectF(origin + QPointF(0, i*20), QSizeF(10, 10));
		QGraphicsEllipseItem* mark = new QGraphicsEllipseItem(r, this);
		QGraphicsEllipseItem* bg = new QGraphicsEllipseItem(r, mark);
		bg->setFlag(QGraphicsItem::ItemStacksBehindParent);
		QPen pen1 = QPen(QBrush(colors.at(i)), 2);
		QPen pen2 = QPen(QBrush(bgs.at(i)), 3);
		mark->setPen(pen1);
		bg->setPen(pen2);
		marks.append(mark);
	}
	//Generate texts:
	for (int i=0; i<labels.size(); ++i) {
		QGraphicsTextItem* text = new QGraphicsTextItem(labels.at(i), this);
		QFont font = text->font();
		font.setPointSize(12);
		text->setFont(font);
		QRectF base = marks.at(i)->boundingRect();
		text->setPos(base.topRight() + QPointF(10, -text->boundingRect().height()*0.3));
		text->setTextInteractionFlags(Qt::TextEditorInteraction);
		texts.append(text);
	}
	//Wrap them all:
	QPointF tl = origin;
	QPointF br = origin + QPointF(10+10+10*11,
		(marks.size()-1)*20+10);
	QRectF bound = QRectF(tl + QPointF(-10, -10), br + QPointF(10, 10));
	setRect(bound);

	//Default format:
	setPen(QPen(QBrush(Qt::black), 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
	setBrush(QBrush(Qt::white));
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

QRectF LegendItem::generateRect() const {
	QPointF tl = marks.at(0)->boundingRect().topLeft();
	QPointF br = texts.at(texts.size()-1)->boundingRect().bottomRight();
	return QRectF(tl + QPointF(-10, -10), br + QPointF(10, 10));
}

void LegendItem::updateRect() {
	setRect(generateRect());
}
