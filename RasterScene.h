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
	bool isDragged;
	bool crop_ok;
	double zoom;
	QRectF bound;
public:
	CropScene(const QString& img, QObject* parent=0);
	~CropScene(void) { }

	QPixmap cropped();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
};

class RectItem;
class CircleItem;
class ClipRect;
class ClipCircle;
class FitRect;
class FitCircle;
class BlendScene:
	public QGraphicsScene
{
	QPixmap thumbnail, base;
	QPointF lastAnchorPos, lastThumbPos;
	QGraphicsSimpleTextItem *myText;
public:
	BlendScene(const QString& source, const QPixmap& thumb, QObject* parent=0);

	RectItem* addRectItem(int width, int height);
	CircleItem* addCircleItem(int width, int height);
	ClipRect* addClipRect(int size);
	ClipCircle* addClipCircle(int size);
	FitRect* addFitRect(int width, int height);
	FitCircle* addFitCircle(int width , int height);

	QPointF lastAnchorTL() const { return lastAnchorPos; }
	QPointF lastThumbTL() const { return lastThumbPos;  }
	QPointF lastTextTL() const { return myText->pos(); }

	QPointF AnchorPos() const;
	QPointF ThumbPos() const;
	QPointF TextPos() const { return myText->pos(); }
	QGraphicsItem* getAnchor();
	QGraphicsItem* getThumb();
	QGraphicsSimpleTextItem* getText() { return myText; }

	void removeAnchor();
	void removeThumb();

	void setPen1(const QPen& p);
	void setPen2(const QPen& p);
	void setFont(const QFont& f);
	void setText(const QString&);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};