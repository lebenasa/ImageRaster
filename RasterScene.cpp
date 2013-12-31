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