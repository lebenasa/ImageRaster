#pragma once
#include "qgraphicsscene.h"

class ImageRaster;
class StateManager;

class RasterScene :
	public QGraphicsScene
{
	Q_OBJECT
	void connectSignals();
	StateManager *manager;
	friend ImageRaster;
public:
	RasterScene(QObject *parent=0);
	~RasterScene(void);

public slots:
	void stateInterface(AppState);
	void markerInterface(MarkerState);
	void rulerInterface(RulerState);

signals:
	void stateChanged(AppState);
	void markerChanged(MarkerState);
	void rulerChanged(RulerState);
	void mouseEvent(QGraphicsSceneMouseEvent *event, MouseState state);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

