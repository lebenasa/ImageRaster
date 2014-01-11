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
	QGraphicsPixmapItem* pix_item = addPixmap(myPix);
	pix_item->setAcceptHoverEvents(true);
	setSceneRect(myPix.rect());
	crop_ok = false;
	isDragged = false;
	zoom = 1.0;
}

void CropScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	if (event->button() == Qt::LeftButton && !crop_ok) {
		p1 = event->scenePos();
		isDragged = true;
	}
	QGraphicsScene::mousePressEvent(event);
}

void CropScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	if (!crop_ok && isDragged) {
		p2 = event->scenePos();
		QList<QGraphicsItem*> is;
		for (auto p : items())
			if (p == tmpRect)
				is.append(p);
		for (auto p : is)
			delete p;
		QPen pen = QPen(QBrush(Qt::black), 1, Qt::DashLine);
		tmpRect = new QGraphicsRectItem(QRectF(p1, p2).normalized());
		tmpRect->setPen(pen);
		addItem(tmpRect);
	}
	QGraphicsScene::mouseMoveEvent(event);
}

void CropScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	if (!crop_ok && isDragged) {
		p2 = event->scenePos();
		bound = QRectF(p1, p2).normalized();
		QList<QGraphicsItem*> is;
		for (auto p : items())
			if (p == tmpRect)
				is.append(p);
		for (auto p : is)
			delete p;
		QPen pen = QPen(QBrush(Qt::black), 1, Qt::DashLine);
		tmpRect = new QGraphicsRectItem(QRectF(p1, p2).normalized());
		tmpRect->setPen(pen);
		addItem(tmpRect);
		crop_ok = true;
		isDragged = false;
	}
	else if (event->button() == Qt::RightButton && crop_ok) {
		delete tmpRect;
		crop_ok = false;
	}
	QGraphicsScene::mouseReleaseEvent(event);
}

void CropScene::wheelEvent(QWheelEvent* event) {
	QPoint delta = event->angleDelta();
	if (delta.x() >= 0 && delta.y() >= 0) {
		if (zoom >= 16.0)
			return;
		if (zoom < 1.0)
			zoom += 0.05;
		else if (zoom >= 1.0 && zoom < 3.0)
			zoom += .25;
		else if (zoom >= 3.0)
			zoom += .5;

		for (auto view : views())
			view->setTransform(QTransform::fromScale(zoom, zoom), false);
	}
	else {
		if (zoom <= .1)
			return;
		if (zoom <= 1.0)
			zoom -= 0.05;
		else if (zoom > 1.0 && zoom <= 3.0)
			zoom -= .25;
		else if (zoom > 3.0)
			zoom -= .5;

		for (auto view : views())
			view->setTransform(QTransform::fromScale(zoom, zoom), false);
	}
	event->accept();
}


QPixmap CropScene::cropped() {
	QImage img = myPix.toImage();
	cropPix = QPixmap::fromImage(img.copy(bound.toRect()));
	return cropPix;
}

//class BlendScene
BlendScene::BlendScene(const QString& source, const QPixmap& thumb, QObject* parent) :
	QGraphicsScene(parent)
{
	thumbnail = thumb;
	base = QPixmap(source);
	QGraphicsPixmapItem* bg = addPixmap(base);
	setSceneRect(base.rect());
	lastThumbPos = QPointF(0, 0);
	lastAnchorPos = QPointF(150, 150);
	myText = new QGraphicsSimpleTextItem("");
	myText->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
	addItem(myText);
	myText->setPos(lastThumbPos + QPointF(100, 138));
	addCircleItem(32, 32);
	addClipCircle(128);
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
			lastAnchorPos = item->sceneTransform().map(item->boundingRect().topLeft());
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
			lastThumbPos = item->sceneTransform().map(item->boundingRect().topLeft());
			pool.append(item);
		}
	}
	for (auto i : pool)
		delete i;
}

QPointF BlendScene::AnchorPos() const {
	for (auto item : items()) {
		if (RectItem::Type == item->type() || CircleItem::Type == item->type()) {
			return item->sceneTransform().map(item->pos());
		}
	}
}

QPointF BlendScene::ThumbPos() const {
	for (auto item : items()) {
		if (ClipRect::Type == item->type() || ClipCircle::Type == item->type() ||
			FitRect::Type == item->type() || FitCircle::Type == item->type()) {
			return item->sceneTransform().map(item->pos());
		}
	}
}

QGraphicsItem* BlendScene::getAnchor() {
	for (auto item : items()) {
		if (RectItem::Type == item->type() || CircleItem::Type == item->type()) {
			return item;
		}
	}
}

QGraphicsItem* BlendScene::getThumb() {
	for (auto item : items()) {
		if (ClipRect::Type == item->type() || ClipCircle::Type == item->type() ||
			FitRect::Type == item->type() || FitCircle::Type == item->type()) {
			return item;
		}
	}
}

void BlendScene::setPen1(const QPen& p) {
	for (auto item : items()) {
		if (auto i = dynamic_cast<RectItem*>(item)) {
			i->setPen1(p);
		}
		else if (auto i = dynamic_cast<CircleItem*>(item)) {
			i->setPen1(p);
		}
	}
}

void BlendScene::setPen2(const QPen& p) {
	for (auto item : items()) {
		if (auto i = dynamic_cast<RectItem*>(item)) {
			i->setPen2(p);
		}
		else if (auto i = dynamic_cast<CircleItem*>(item)) {
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
