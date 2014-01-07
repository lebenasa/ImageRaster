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

class CropScene:
	public QGraphicsScene
{
	Q_OBJECT
	QPixmap myPix, cropPix;
	QGraphicsRectItem *tmpRect;
	QPointF p1, p2;
	bool crop_ok;
public:
	CropScene(const QString& img, QObject* parent=0);
	~CropScene(void) { }

	QPixmap cropped() const { return cropPix; }
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); 
};

class BlendScene:
	public QGraphicsScene
{
	Q_OBJECT
	QPixmap thumbnail, base;
public:
	BlendScene(const QString& source, const QPixmap& thumb);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); 
};