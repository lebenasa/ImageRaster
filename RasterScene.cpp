#include "stdafx.h"
#include "RasterScene.h"
#include "StateManager.h"
#include "Arrow.h"

RasterScene::RasterScene(QObject *parent)
	: QGraphicsScene(parent)
{
	/*The Raster Scene.
	It provide a canvas where we put QGraphicsItem.
	*/
	manager = new StateManager(this);
	connectSignals();
}

RasterScene::~RasterScene(void)
{
}

void RasterScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	emit mouseEvent(event, MouseState::Click);
}

void RasterScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	emit mouseEvent(event, MouseState::Move);
}

void RasterScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	emit mouseEvent(event, MouseState::Release);
}

void RasterScene::stateInterface(AppState state) {
	emit stateChanged(state);
}

void RasterScene::markerInterface(MarkerState state) {
	emit markerChanged(state);
}

void RasterScene::rulerInterface(RulerState state) {
	emit rulerChanged(state);
}

void RasterScene::connectSignals() {
	connect(this, SIGNAL(stateChanged(AppState)), manager, SLOT(StateChanged(AppState)));
	connect(this, &RasterScene::markerChanged, manager, &StateManager::MarkerChanged);
	connect(this, &RasterScene::rulerChanged, manager, &StateManager::RulerChanged);
}

//class CropScene
CropScene::CropScene(const QString& img, QObject* parent) :
	QGraphicsScene(parent)
{
	myPix = QPixmap(img);
	addPixmap(myPix);
	setSceneRect(myPix.rect());
	crop_ok = false;
}

void CropScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mousePressEvent(event);
	if (event->button() == Qt::LeftButton && !crop_ok) {
		if (sceneRect().contains(event->pos()))
			p1 = event->pos();
	}
}

void CropScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mouseMoveEvent(event);
	if (event->button() == Qt::LeftButton && !crop_ok) {
		//if (sceneRect().contains(event->pos()))
		//	p2 = event->pos();
		//QList<QGraphicsItem*> is;
		//for (auto p : items())
		//	if (p == tmpRect)
		//		is.append(p);
		//for (auto p : is)
		//	delete p;
		//tmpRect = addRect(QRectF(p1, p2).normalized());
		//QPen pen = QPen(QBrush(Qt::black), 1, Qt::DashLine);
		//tmpRect->setPen(pen);
	}
}

void CropScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mouseReleaseEvent(event);
	if (event->button() == Qt::LeftButton && !crop_ok) {
		if (sceneRect().contains(event->pos()))
			p2 = event->pos();
		QRectF bound = QRectF(p1, p2).normalized();
		setSceneRect(bound);
		crop_ok = true;
	}
	else if (event->button() == Qt::RightButton && crop_ok) {
		setSceneRect(myPix.rect());
	}
}

QPixmap CropScene::cropped() {
	QImage img(width(), height(), QImage::Format_ARGB32);
	img.fill(Qt::transparent);
	QPainter painter(&img);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	render(&painter);
	p1 = QPointF();
	cropPix = QPixmap().fromImage(img);
	return cropPix;
}

//class BlendScene
BlendScene::BlendScene(const QString& source, const QPixmap& thumb, QObject* parent) :
	QGraphicsScene(parent)
{
	thumbnail = thumb;
	base = QPixmap(source);
	QGraphicsPixmapItem* bg = addPixmap(base);
	setSceneRect(bg->boundingRect());
	lastThumbPos = sceneRect().center() + QPointF(128, 128);
	lastAnchorPos = sceneRect().center();
	myText = new QGraphicsSimpleTextItem();
	myText->setPos(lastThumbPos + QPointF(0, 138));
	myText->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

RectItem* BlendScene::addRectItem(int width, int height) {
	RectItem* frame_anchor = new RectItem(QRectF(lastAnchorPos, QSizeF(width, height)));
	frame_anchor->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	addItem(frame_anchor);
	return frame_anchor;
}

CircleItem* BlendScene::addCircleItem(int width, int height) {
	CircleItem* frame_anchor = new CircleItem(QRectF(lastAnchorPos, QSizeF(width, height)));
	frame_anchor->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	addItem(frame_anchor);
	return frame_anchor;
}

ClipRect* BlendScene::addClipRect(int size) {
	ClipRect* frame_thumb = new ClipRect(thumbnail, QRectF(lastThumbPos, QSizeF(size, size)));
	frame_thumb->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	addItem(frame_thumb);
	return frame_thumb;
}

ClipCircle* BlendScene::addClipCircle(int size) {
	ClipCircle* frame_thumb = new ClipCircle(thumbnail, QRectF(lastThumbPos, QSizeF(size, size)));
	frame_thumb->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	addItem(frame_thumb);
	return frame_thumb;
}

FitRect* BlendScene::addFitRect(int width, int height) {
	FitRect* frame_thumb = new FitRect(thumbnail, QRectF(lastThumbPos, QSizeF(width, height)));
	frame_thumb->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	addItem(frame_thumb);
	return frame_thumb;
}

FitCircle* BlendScene::addFitCircle(int width , int height) {
	FitCircle* frame_thumb = new FitCircle(thumbnail, QRectF(lastThumbPos, QSizeF(width, height)));
	frame_thumb->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	addItem(frame_thumb);
	return frame_thumb;
}

void BlendScene::removeAnchor() {
	QList<QGraphicsItem*> pool;
	for (auto item : items()) {
		if (RectItem::Type == item->type() || CircleItem::Type == item->type()) {
			lastAnchorPos = item->boundingRect().topLeft();
			pool.append(item);
		}
	}
	for (auto i : pool)
		delete i;
}

void BlendScene::removeThumb() {
	QList<QGraphicsItem*> pool;
	for (auto item : items()) {
		if (ClipRect::Type == item->type() || ClipCircle::Type == item->type() ||
			FitRect::Type == item->type() || FitCircle::Type == item->type()) {
			lastThumbPos = item->boundingRect().topLeft();
			pool.append(item);
		}
	}
	for (auto i : pool)
		delete i;
}

void BlendScene::setPen1(const QPen& p) {
	for (auto item : items()) {
		if (auto i = qgraphicsitem_cast<RectItem*>(item)) {
			i->setPen1(p);
		}
		else if (auto i = qgraphicsitem_cast<CircleItem*>(item)) {
			i->setPen1(p);
		}
	}
}

void BlendScene::setPen2(const QPen& p) {
	for (auto item : items()) {
		if (auto i = qgraphicsitem_cast<RectItem*>(item)) {
			i->setPen2(p);
		}
		else if (auto i = qgraphicsitem_cast<CircleItem*>(item)) {
			i->setPen2(p);
		}
	}
}

void BlendScene::setFont(const QFont& f) {
	myText->setFont(f);
}

void BlendScene::setText(const QString& t) {
	myText->setText(t);
}

void BlendScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mousePressEvent(event);
}

void BlendScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mouseMoveEvent(event);
}

void BlendScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mouseReleaseEvent(event);
}
