#pragma once
#include "Arrow.h"

class RasterScene;
class ImageRaster;

class StateManager :
	public QObject
{
	Q_OBJECT
public:
	StateManager(RasterScene *scn);
	~StateManager(void);

	AppState state;

public slots:
	void StateChanged(AppState curState);
	void MarkerChanged(MarkerState);
	void RulerChanged(RulerState);

	//CMR : Click-Move-Release
	void cmrSelect(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrMarkerArrow(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrMarkerRectangle(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrMarkerCircle(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrRulerLine(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrRulerRectangle(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrRulerCircle(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrRulerCentertoCenter(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrRulerPolygon(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrCCalibrating(QGraphicsSceneMouseEvent *event, MouseState ms);

	void cmrCIdle(QGraphicsSceneMouseEvent *event, MouseState ms);

signals:
	void addMarker(Marker*);
	void addLR(LineRuler*);
	void addRR(RectRuler*);
	void addCR(CircleRuler*);
	void addTC(Circle2Ruler*);
	void addPR(PolyRuler*);
	void sendCalibration(int);

private:
	RasterScene *scene;
	friend class ImageRaster;

	//Internal state:
	bool isDragged;
	bool hasTmpItem;
	Format fd;
	mData md;
	int cStatus;
	int click;

	enum CalibSeq {
		Start, Click1, Move, Click2, Idle
	} sequence;

	//Temporary shapes:
	QGraphicsRectItem *tmpRect;
	QGraphicsEllipseItem *tmpCircle;
	QGraphicsLineItem *tmpLine;

	ArrowMarker *tmpArrMarker;
	RectMarker *tmpRectMarker;
	CircleMarker *tmpCircMarker;

	LineRuler *tmpLineRuler;
	RectRuler *tmpRectRuler;
	CircleRuler *tmpCircleRuler;

	//Store event pos:
	QPointF p1, p2, p3, p4, p5, p6;
	QPolygonF polyBuilder;

	QRectF rectFrom3Point(const QPointF&, const QPointF&, const QPointF&);
	QRectF rectFromCenter(const QPointF&);
};

