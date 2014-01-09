#include "stdafx.h"
#include "RasterScene.h"
#include "StateManager.h"

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
