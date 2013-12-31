#include "stdafx.h"
#include "StateManager.h"
#include "RasterScene.h"


StateManager::StateManager(RasterScene *scn)
	: QObject(scn), fd()
{
	/*
	The class to manage Raster Scene state and behaviour.
	*/
	scene = scn;
	isDragged = false;
	hasTmpItem = false;
	click = 0;
	sequence = Idle;
}

StateManager::~StateManager(void)
{
}

void StateManager::StateChanged(AppState curState) {
	state = curState;

	if (hasTmpItem) {
		for (auto item : scene->items()) {
			if (tmpCircle == item)
				delete tmpCircle;
			else if (tmpLine == item)
				delete tmpLine;
		}
		hasTmpItem = false;
	}
	click = 0;

	if (AppState::Select == state) {
		disconnect(scene, &RasterScene::mouseEvent, this, 0);
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrSelect);
	}
	else if (AppState::Marker == state) {
		//QAction *emitter = qobject_cast<QAction*>(sender());
		//MarkerState mode = (MarkerState)emitter->data().toInt();
		//switch (mode) {
		//case MarkerState::Arrow:
		//	connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrMarkerArrow);
		//	break;
		//case MarkerState::Circle:
		//	connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrMarkerCircle);
		//	break;
		//case MarkerState::Rectangle:
		//	connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrMarkerRectangle);
		//	break;
		//}
	}
	else if (AppState::Ruler == state) {
		//QAction *emitter = qobject_cast<QAction*>(sender());
		//RulerState mode = (RulerState)emitter->data().toInt();
		//switch (mode) {
		//case RulerState::Line:
		//	connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerLine);
		//	break;
		//case RulerState::Rectangle:
		//	connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerRectangle);
		//	break;
		//case RulerState::Circle:
		//	connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerCircle);
		//	break;
		//case RulerState::Circle2:
		//	connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerCentertoCenter);
		//	break;
		//case RulerState::Polygon:
		//	connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerPolygon);
		//	break;
		//}
	}
	else if (AppState::Calibration == state) {
		disconnect(scene, &RasterScene::mouseEvent, this, 0);
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrCCalibrating);
	}
}

void StateManager::MarkerChanged(MarkerState mode) {
	if (AppState::Marker != state) return;
	disconnect(scene, &RasterScene::mouseEvent, this, 0);
	switch (mode) {
	case MarkerState::Arrow:
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrMarkerArrow);
		break;
	case MarkerState::Circle:
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrMarkerCircle);
		break;
	case MarkerState::Rectangle:
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrMarkerRectangle);
		break;
	}
}

void StateManager::RulerChanged(RulerState mode) {
	if (AppState::Ruler != state) return;
	disconnect(scene, &RasterScene::mouseEvent, this, 0);
	switch (mode) {
	case RulerState::Line:
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerLine);
		break;
	case RulerState::Rectangle:
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerRectangle);
		break;
	case RulerState::Circle:
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerCircle);
		break;
	case RulerState::Circle2:
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerCentertoCenter);
		break;
	case RulerState::Polygon:
		connect(scene, &RasterScene::mouseEvent, this, &StateManager::cmrRulerPolygon);
		break;
	}
}

void StateManager::cmrSelect(QGraphicsSceneMouseEvent *event, MouseState ms) {
	if (MouseState::Click == ms) {
		if (Qt::LeftButton != event->button()) return;
		p1 = event->scenePos();
		if (!scene->sceneRect().contains(p1)) return;
		isDragged = true;
		p2 = p1;
		for (auto item : scene->items())
			item->setSelected(false);
	}
	else if (MouseState::Move == ms) {
		if (!isDragged) return;
		p2 = event->scenePos();
		if (!scene->sceneRect().contains(p2)) return;
		QRectF r(p1, p2);
		QPen p(QBrush(Qt::blue), 1, Qt::DashLine);
		QBrush b(QColor(0, 0, 255, 64));
		if (hasTmpItem) delete tmpRect;
		tmpRect = new QGraphicsRectItem(r.normalized());
		tmpRect->setPen(p);
		tmpRect->setBrush(b);
		scene->addItem(tmpRect);
		hasTmpItem = true;
	}
	else if (MouseState::Release == ms) {
		if (Qt::LeftButton != event->button()) return;
		isDragged = false;
		if (hasTmpItem) delete tmpRect;
		hasTmpItem = false;
		p2 = (scene->sceneRect().contains(event->scenePos())) ? event->scenePos() : p2;
		QRectF r(p1, p2);
		for (QGraphicsItem* obj : scene->items(r, Qt::IntersectsItemShape))
			obj->setSelected(true);
	}
}

void StateManager::cmrMarkerArrow(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (Qt::RightButton == event->button()) {
		//TBA: Context menu
		return;
	}

	if (MouseState::Click == ms) {
		p1 = event->scenePos();
		if (!scene->sceneRect().contains(p1)) return;
		if (scene->items(p1).count() > 1) return;	//To ensure no overlap
		isDragged = true;
		p2 = p1 + QPointF(1, 1);					//To ensure a valid QLineF
	}
	else if (MouseState::Move == ms) {
		if (!isDragged) return;
		p2 = event->scenePos();
		if (scene->sceneRect().contains(p2)) {
			if (hasTmpItem) delete tmpArrMarker;
			tmpArrMarker = new ArrowMarker(QLineF(p1, p2));
			scene->addItem(tmpArrMarker);
			hasTmpItem = true;
		}
		else {
			if (hasTmpItem) delete tmpArrMarker;
			hasTmpItem = false;
			isDragged = false;
		}
	}
	else if (MouseState::Release == ms) {
		if (!isDragged) return;
		isDragged = false;
		if (hasTmpItem) delete tmpArrMarker;
		hasTmpItem = false;
		p2 = (scene->sceneRect().contains(event->scenePos())) ? event->scenePos() : p2;
		//Call create arrow marker action:
		ArrowMarker* marker = new ArrowMarker(QLineF(p1, p2));
		emit addMarker(marker);
	}
}

void StateManager::cmrMarkerRectangle(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (Qt::RightButton == event->button()) {
		return;
	}
	if (MouseState::Click == ms) {
		p1 = event->scenePos();
		if (!scene->sceneRect().contains(p1)) return;
		if (scene->items(p1).count() > 1) return;	//To ensure no overlap
		isDragged = true;
		p2 = p1 + QPointF(1, 1);					//To ensure a valid QLineF
	}
	else if (MouseState::Move == ms) {
		if (!isDragged) return;
		p2 = event->scenePos();
		if (scene->sceneRect().contains(p2)) {
			if (hasTmpItem) delete tmpRectMarker;
			tmpRectMarker = new RectMarker(QRectF(p1, p2).normalized());
			scene->addItem(tmpRectMarker);
			hasTmpItem = true;
		}
		else {
			if (hasTmpItem) delete tmpRectMarker;
			hasTmpItem = false;
			isDragged = false;
		}
	}
	else if (MouseState::Release == ms) {
		if (!isDragged) return;
		isDragged = false;
		if (hasTmpItem) delete tmpRectMarker;
		hasTmpItem = false;
		p2 = (scene->sceneRect().contains(event->scenePos())) ? event->scenePos() : p2;
		//Call create arrow marker action:
		RectMarker* marker = new RectMarker(QRectF(p1, p2).normalized());
		emit addMarker(marker);
	}
}

void StateManager::cmrMarkerCircle(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (Qt::RightButton == event->button()) {
		return;
	}
	if (MouseState::Click == ms) {
		p1 = event->scenePos();
		if (!scene->sceneRect().contains(p1)) return;
		if (scene->items(p1).count() > 1) return;	//To ensure no overlap
		isDragged = true;
		p2 = p1 + QPointF(1, 1);					//To ensure a valid QLineF
	}
	else if (MouseState::Move == ms) {
		if (!isDragged) return;
		p2 = event->scenePos();
		if (scene->sceneRect().contains(p2)) {
			if (hasTmpItem) delete tmpCircMarker;
			tmpCircMarker = new CircleMarker(QRectF(p1, p2).normalized());
			scene->addItem(tmpCircMarker);
			hasTmpItem = true;
		}
		else {
			if (hasTmpItem) delete tmpCircMarker;
			hasTmpItem = false;
			isDragged = false;
		}
	}
	else if (MouseState::Release == ms) {
		if (!isDragged) return;
		isDragged = false;
		if (hasTmpItem) delete tmpCircMarker;
		hasTmpItem = false;
		p2 = (scene->sceneRect().contains(event->scenePos())) ? event->scenePos() : p2;
		//Call create arrow marker action:
		CircleMarker* marker = new CircleMarker(QRectF(p1, p2).normalized());
		emit addMarker(marker);
	}
}

void StateManager::cmrRulerLine(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (Qt::RightButton == event->button()) {
		//TBA: Context menu
		return;
	}

	if (MouseState::Click == ms) {
		p1 = event->scenePos();
		if (!scene->sceneRect().contains(p1)) return;
		if (scene->items(p1).count() > 1) return;	//To ensure no overlap
		isDragged = true;
		p2 = p1 + QPointF(1, 1);					//To ensure a valid QLineF
	}
	else if (MouseState::Move == ms) {
		if (!isDragged) return;
		p2 = event->scenePos();
		if (scene->sceneRect().contains(p2)) {
			if (hasTmpItem) delete tmpLineRuler;
			tmpLineRuler = new LineRuler(QLineF(p1, p2));
			scene->addItem(tmpLineRuler);
			hasTmpItem = true;
		}
		else {
			if (hasTmpItem) delete tmpLineRuler;
			hasTmpItem = false;
			isDragged = false;
		}
	}
	else if (MouseState::Release == ms) {
		if (!isDragged) return;
		isDragged = false;
		if (hasTmpItem) delete tmpLineRuler;
		hasTmpItem = false;
		p2 = (scene->sceneRect().contains(event->scenePos())) ? event->scenePos() : p2;
		//Call create arrow marker action:
		QLineF line = QLineF(p1, p2);
		if (line.length() < 5.0)
			return;
		LineRuler* ruler = new LineRuler(QLineF(p1, p2));
		emit addLR(ruler);
	}

}

void StateManager::cmrRulerRectangle(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (Qt::RightButton == event->button()) {
		return;
	}
	if (MouseState::Click == ms) {
		p1 = event->scenePos();
		if (!scene->sceneRect().contains(p1)) return;
		if (scene->items(p1).count() > 1) return;	//To ensure no overlap
		isDragged = true;
		p2 = p1 + QPointF(1, 1);					//To ensure a valid QLineF
	}
	else if (MouseState::Move == ms) {
		if (!isDragged) return;
		p2 = event->scenePos();
		if (scene->sceneRect().contains(p2)) {
			if (hasTmpItem) delete tmpRectRuler;
			tmpRectRuler = new RectRuler(QRectF(p1, p2).normalized());
			scene->addItem(tmpRectRuler);
			hasTmpItem = true;
		}
		else {
			if (hasTmpItem) delete tmpRectRuler;
			hasTmpItem = false;
			isDragged = false;
		}
	}
	else if (MouseState::Release == ms) {
		if (!isDragged) return;
		isDragged = false;
		if (hasTmpItem) delete tmpRectRuler;
		hasTmpItem = false;
		p2 = (scene->sceneRect().contains(event->scenePos())) ? event->scenePos() : p2;
		//Call create arrow marker action:
		RectRuler* ruler = new RectRuler(QRectF(p1, p2).normalized());
		emit addRR(ruler);
	}
}

void StateManager::cmrRulerCircle(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (Qt::RightButton == event->button()) {
		return;
	}
	if (MouseState::Click == ms) {
		if (!scene->sceneRect().contains(event->scenePos())) return;
		if (scene->items(event->scenePos()).count() > 1) return;	//To ensure no overlap
		QPen pen = QPen(Qt::black);
		pen.setWidth(2);
		if (0 == click) {
			p1 = event->scenePos();
			++click;
			tmpCircle = new QGraphicsEllipseItem(rectFromCenter(p1));
			tmpCircle->setPen(pen);
			scene->addItem(tmpCircle);
			hasTmpItem = true;
		}
		else if (1 == click) {
			p2 = event->scenePos();
			++click;
			QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rectFromCenter(p2), tmpCircle);
			item->setPen(pen);
			scene->addItem(item);
		}
		else if (2 == click) {
			p3 = event->scenePos();
			click = 0;
			delete tmpCircle;
			hasTmpItem = false;
			CircleRuler* ruler = new CircleRuler(rectFrom3Point(p1, p2, p3));
			emit addCR(ruler);
		}
	}
	else if (MouseState::Move == ms) {
	}
	else if (MouseState::Release == ms) {
	}
}

void StateManager::cmrRulerCentertoCenter(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (Qt::RightButton == event->button()) {
		return;
	}
	if (MouseState::Click == ms) {
		if (!scene->sceneRect().contains(event->scenePos())) return;
		if (scene->items(event->scenePos()).count() > 1) return;	//To ensure no overlap
		QPen pen = QPen(Qt::black);
		pen.setWidth(2);
		if (0 == click) {
			p1 = event->scenePos();
			++click;
			tmpCircle = new QGraphicsEllipseItem(rectFromCenter(p1));
			tmpCircle->setPen(pen);
			scene->addItem(tmpCircle);
			hasTmpItem = true;
		}
		else if (1 == click) {
			p2 = event->scenePos();
			++click;
			QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rectFromCenter(p2), tmpCircle);
			item->setPen(pen);
			scene->addItem(item);
		}
		else if (2 == click) {
			p3 = event->scenePos();
			++click;
			delete tmpCircle;
			tmpCircle = new QGraphicsEllipseItem(rectFrom3Point(p1, p2, p3), tmpCircle);
			tmpCircle->setPen(pen);
			scene->addItem(tmpCircle);
		}
		else if (3 == click) {
			p4 = event->scenePos();
			++click;
			QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rectFromCenter(p4), tmpCircle);
			item->setPen(pen);
			scene->addItem(item);
		}
		else if (4 == click) {
			p5 = event->scenePos();
			++click;
			QGraphicsEllipseItem* item = new QGraphicsEllipseItem(rectFromCenter(p5), tmpCircle);
			item->setPen(pen);
			scene->addItem(item);
		}
		else if (5 == click) {
			p6 = event->scenePos();
			click = 0;
			delete tmpCircle;
			hasTmpItem = false;
			Circle2Ruler* ruler = new Circle2Ruler(rectFrom3Point(p1, p2, p3), rectFrom3Point(p4, p5, p6));
			emit addTC(ruler);
		}
	}
	else if (MouseState::Move == ms) {

	}
	else if (MouseState::Release == ms) {

	}
}

void StateManager::cmrRulerPolygon(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (MouseState::Click == ms) {
		if (!scene->sceneRect().contains(event->scenePos())) return;
		if (scene->items(event->scenePos()).count() > 1) return;	//To ensure no overlap
		QPen pen = QPen(Qt::black);
		pen.setWidth(2);
		if (0 == click) {
			p1 = event->scenePos();
			p3 = p1;
			polyBuilder.clear();
			polyBuilder << p1;
			++click;
		}
		else if (click > 0) {
			if (event->button() == Qt::RightButton && polyBuilder.count() > 2) {
				delete tmpLine;
				hasTmpItem = false;
				click = 0;
				polyBuilder << p3;
				PolyRuler* ruler = new PolyRuler(polyBuilder);
				emit addPR(ruler);
			}
			else {
				p2 = event->scenePos();
				++click;
				if (!hasTmpItem) {
					tmpLine = new QGraphicsLineItem(QLineF(p1, p2));
					tmpLine->setPen(pen);
					scene->addItem(tmpLine);
					hasTmpItem = true;
				}
				else {
					QGraphicsLineItem *item = new QGraphicsLineItem(QLineF(p1, p2), tmpLine);
					item->setPen(pen);
					//scene->addItem(item);
				}
				polyBuilder << p2;
				p1 = p2;
			}
		}
	}
	else if (MouseState::Move == ms) {
	}
	else if (MouseState::Release == ms) {
	}
}

void StateManager::cmrCCalibrating(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (sequence == Idle) return;
	if (Qt::RightButton == event->button()) {
		return;
	}
	if (MouseState::Click == ms) {
		if (Start == sequence) {
			p1 = event->scenePos();
			if (!scene->sceneRect().contains(p1)) return;
			if (hasTmpItem) {
				delete tmpLine;
				hasTmpItem = false;
			}
			sequence = Click1;
		}
		else if (Click1 == sequence) {
			p2 = event->scenePos();
			if (!scene->sceneRect().contains(p2)) return;
			if (hasTmpItem) {
				delete tmpRect;
				hasTmpItem = false;
			}
			sequence = Move;
			emit sendCalibration(abs(p1.x()-p2.x()));
		}
		else if (Move == sequence) {
			p1 = event->scenePos();
			if (!scene->sceneRect().contains(p1)) return;
			if (hasTmpItem) {
				delete tmpLine;
				hasTmpItem = false;
			}
			sequence = Click2;
		}
		else if (Click2 == sequence) {
			p2 = event->scenePos();
			if (!scene->sceneRect().contains(p2)) return;
			if (hasTmpItem) {
				delete tmpRect;
				hasTmpItem = false;
			}
			sequence = Idle;
			emit sendCalibration(abs(p1.y()-p2.y()));
		}
	}
	else if (MouseState::Move == ms) {
		if (Start == sequence) {
			p3 = event->scenePos();
			if (!scene->sceneRect().contains(p3)) return;
			QLineF line = QLineF(p3.x(), 0, p3.x(), scene->height());
			if (hasTmpItem)
				delete tmpLine;
			QPen red = QPen(QBrush(Qt::red), 2);
			tmpLine = new QGraphicsLineItem(line);
			tmpLine->setPen(red);
			scene->addItem(tmpLine);
			hasTmpItem = true;
		}
		else if (Click1 == sequence) {
			p4 = event->scenePos();
			if (!scene->sceneRect().contains(p4)) return;
			QRectF rect;
			if (p4.x() > p3.x())
				rect.setRect(p3.x(), 0, p4.x()-p3.x(), scene->height());
			else
				rect.setRect(p4.x(), 0, p3.x()-p4.x(), scene->height());
			if (hasTmpItem)
				delete tmpRect;
			QPen red = QPen(QBrush(Qt::red), 2);
			QBrush tr_red = QBrush(QColor(255, 0, 0, 64));
			tmpRect = new QGraphicsRectItem(rect.normalized());
			tmpRect->setPen(red);
			tmpRect->setBrush(tr_red);
			scene->addItem(tmpRect);
			hasTmpItem = true;
		}
		else if (Move == sequence) {
			p3 = event->scenePos();
			if (!scene->sceneRect().contains(p3)) return;
			QLineF line = QLineF(0, p3.y(), scene->width(), p3.y());
			if (hasTmpItem)
				delete tmpLine;
			QPen red = QPen(QBrush(Qt::red), 2);
			tmpLine = new QGraphicsLineItem(line);
			tmpLine->setPen(red);
			scene->addItem(tmpLine);
			hasTmpItem = true;
		}
		else if (Click2 == sequence) {
			p4 = event->scenePos();
			if (!scene->sceneRect().contains(p4)) return;
			QRectF rect;
			if (p4.x() > p3.x())
				rect.setRect(0, p3.y(), scene->width(), p4.y()-p3.y());
			else
				rect.setRect(0, p4.y(), scene->width(), p3.y()-p4.y());
			if (hasTmpItem)
				delete tmpRect;
			QPen red = QPen(QBrush(Qt::red), 2);
			QBrush tr_red = QBrush(QColor(255, 0, 0, 64));
			tmpRect = new QGraphicsRectItem(rect.normalized());
			tmpRect->setPen(red);
			tmpRect->setBrush(tr_red);
			scene->addItem(tmpRect);
			hasTmpItem = true;
		}
	}
	else if (MouseState::Release == ms) {
	}
}

void StateManager::cmrCIdle(QGraphicsSceneMouseEvent *event, MouseState ms)	{
	if (MouseState::Click == ms) {

	}
	else if (MouseState::Move == ms) {

	}
	else if (MouseState::Release == ms) {

	}
}

QRectF StateManager::rectFrom3Point(const QPointF& pa, const QPointF& pb, const QPointF& pc) {
	 QList<double> X, Y;
    X << pa.x() << pb.x() << pc.x();
    Y << pa.y() << pb.y() << pc.y();
    qSort(X.begin(), X.end());
    qSort(Y.begin(), Y.end());
    QPointF rect_tl(X[0], Y[0]);
    QPointF rect_br(X[2], Y[2]);
    QRectF result(rect_tl, rect_br);
    QPointF center = result.center();
    if (result.height() > result.width()) {
        QPointF fin_tl(center.x()-result.height()/2, center.y()-result.height()/2);
        result.setRect(fin_tl.x(), fin_tl.y(), result.height(), result.height());
    }
    else {
        QPointF fin_tl(center.x()-result.width()/2, center.y()-result.width()/2);
        result.setRect(fin_tl.x(), fin_tl.y(), result.width(), result.width());
    }
    return result;
}

QRectF StateManager::rectFromCenter(const QPointF& pa) {
	QPointF tl = pa - QPointF(5, 5);
	return QRectF(tl, QSizeF(10, 10));
}

