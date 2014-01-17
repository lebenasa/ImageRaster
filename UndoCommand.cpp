#include "stdafx.h"
#include "UndoCommand.h"
#include "imageraster.h"
#include "RasterScene.h"
#include "ModelView.h"
#include "Arrow.h"

AddItem::AddItem(Marker* graphicsItem, RasterScene* scn, MarkerBranch* brc, QUndoCommand* parent) :
		QUndoCommand("Add item", parent), item(graphicsItem), branch(brc), scene(scn)
{
}

AddItem::~AddItem() {
	//delete item;
}

void AddItem::redo() {
	branch->addLeaf(item);
	if (auto p = dynamic_cast<QGraphicsItem*>(item))
		scene->addItem(p);
	else return;
}

void AddItem::undo() {
	branch->removeLeaf(item);
	if (auto p = dynamic_cast<QGraphicsItem*>(item))
		scene->removeItem(p);
	else return;
}

AddMarker::AddMarker(MarkerModel* m, ImageRaster* p, QUndoCommand* parent) :
	QUndoCommand("Add new marker data", parent)
{
	model = m;
	raster = p;
}

void AddMarker::undo() {
	model->removeRow(model->rowCount()-1);
	raster->lastMarker();
	raster->setMarker();
}

void AddMarker::redo() {
	model->insertRow(model->rowCount());
	if (1 == model->rowCount())
		raster->firstMarker();
	raster->setMarker();
}

RemoveMarker::RemoveMarker(MarkerModel* m, int i, ImageRaster* p, QUndoCommand* parent) :
	QUndoCommand("Remove current marker data", parent)
{
	model = m;
	index = i;
	raster = p;
}

void RemoveMarker::undo() {
	RasterScene* scene = raster->getScene();
	for (auto p : items) {
		scene->addItem(p);
	}
	items.clear();
	model->insertBranch(index, branch);
}

void RemoveMarker::redo() {
	RasterScene* scene = raster->getScene();
	for (auto p : model->at(index)->leafItems()) {
		if (auto b = (ArrowMarker*)p) {
			items.append(b);
			scene->removeItem(b);
		}
	}
	branch = model->at(index);
	model->removeRow(index);
	raster->lastMarker();
	raster->setMarker();
}

LabelChg::LabelChg(MarkerBranch* b, const QString& old, const QString& n, QUndoCommand* parent):
	QUndoCommand("Label changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void LabelChg::undo() {
	branch->setLabel(oldValue);
}

void LabelChg::redo() {
	branch->setLabel(newValue);
}

//bool LabelChg::mergeWith(const QUndoCommand* other) {
//	if (other->id() != id())
//        return false;
//    if (auto p = static_cast<const LabelChg*>(other)) {
//		if (p->oldValue == p->newValue) return true;
//		else if (p->oldValue == oldValue && p->newValue == newValue)
//			return true;
//		return false;
//	}
//	return false;
//}

Color1Chg::Color1Chg(MarkerBranch* b, const QColor& old, const QColor& n, QUndoCommand* parent):
	QUndoCommand("Primary color changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void Color1Chg::undo() {
	branch->setColor1(oldValue);
}

void Color1Chg::redo() {
	branch->setColor1(newValue);
}

//bool Color1Chg::mergeWith(const QUndoCommand* other) {
//	if (other->id() != id())
//        return false;
//    if (auto p = static_cast<const Color1Chg*>(other)) {
//		if (p->oldValue == p->newValue) return true;
//		else if (p->oldValue == oldValue && p->newValue == newValue)
//			return true;
//		return false;
//	}
//	return false;
//}

Color2Chg::Color2Chg(MarkerBranch* b, const QColor& old, const QColor& n, QUndoCommand* parent):
	QUndoCommand("Secondary color changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void Color2Chg::undo() {
	branch->setColor2(oldValue);
}

void Color2Chg::redo() {
	branch->setColor2(newValue);
}

//bool Color2Chg::mergeWith(const QUndoCommand* other) {
//	if (other->id() != id())
//        return false;
//    if (auto p = static_cast<const Color2Chg*>(other)) {
//		if (p->oldValue == p->newValue) return true;
//		else if (p->oldValue == oldValue && p->newValue == newValue)
//			return true;
//		return false;
//	}
//	return false;
//}

FontChg::FontChg(MarkerBranch* b, const QFont& old, const QFont& n, QUndoCommand* parent):
	QUndoCommand("Font changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void FontChg::undo() {
	branch->setFont(oldValue);
}

void FontChg::redo() {
	branch->setFont(newValue);
}

//bool FontChg::mergeWith(const QUndoCommand* other) {
//	if (other->id() != id())
//        return false;
//    if (auto p = static_cast<const FontChg*>(other)) {
//		if (p->oldValue == p->newValue) return true;
//		else if (p->oldValue == oldValue && p->newValue == newValue)
//			return true;
//		return false;
//	}
//	return false;
//}

WidthChg::WidthChg(MarkerBranch* b, const int& old, const int& n, QUndoCommand* parent):
	QUndoCommand("Pen width changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void WidthChg::undo() {
	branch->setWidth(oldValue);
}

void WidthChg::redo() {
	branch->setWidth(newValue);
}

//bool WidthChg::mergeWith(const QUndoCommand* other) {
//	if (other->id() != id())
//        return false;
//    if (auto p = static_cast<const WidthChg*>(other)) {
//		if (p->oldValue == p->newValue) return true;
//		else if (p->oldValue == oldValue && p->newValue == newValue)
//			return true;
//		return false;
//	}
//	return false;
//}

FontSizeChg::FontSizeChg(MarkerBranch* b, const int& old, const int& n, QUndoCommand* parent):
	QUndoCommand("Font size changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void FontSizeChg::undo() {
	branch->setFontSize(oldValue);
}

void FontSizeChg::redo() {
	branch->setFontSize(newValue);
}

//bool FontSizeChg::mergeWith(const QUndoCommand* other) {
//	if (other->id() != id())
//        return false;
//    if (auto p = static_cast<const FontSizeChg*>(other)) {
//		if (p->oldValue == p->newValue) return true;
//		else if (p->oldValue == oldValue && p->newValue == newValue)
//			return true;
//		return false;
//	}
//	return false;
//}

Visibility::Visibility(MarkerBranch* b, bool v, ImageRaster* r, QUndoCommand* parent):
	QUndoCommand("Visibility changed", parent)
{
	branch = b;
	value = v;
	raster = r;
}

void Visibility::undo() {
	branch->setVisible(!value);
	raster->chgVisibility(branch, !value);
}

void Visibility::redo() {
	branch->setVisible(value);
	raster->chgVisibility(branch, value);
}

//bool Visibility::mergeWith(const QUndoCommand* other) {
//	if (other->id() != id())
//        return false;
//    if (auto p = static_cast<const Visibility*>(other)) {
//		if (p->value == value) return true;
//		return false;
//	}
//	return false;
//}

AddRuler::AddRuler(LineRuler* ruler_, RulerModel* model_, ImageRaster* parent_) :
	QUndoCommand(), ruler(ruler_), model(model_), parent(parent_)
{
}

void AddRuler::undo() {
	parent->sceneRemoveItem(ruler);
	model->removeRow(model->rowCount()-1);
	update();
}

void AddRuler::redo() {
	parent->sceneAddItem(ruler);
	model->insertBranch(model->rowCount(), ruler);
	update();
}

AddLineRuler::AddLineRuler(LineRuler* ruler_, RulerModel* model_, ImageRaster* parent_) :
	AddRuler(ruler_, model_, parent_)
{
	setText("Line Measurement");
}

void AddLineRuler::update() {
	parent->updateLR();
}

AddRectRuler::AddRectRuler(RectRuler* ruler_, RulerModel* model_, ImageRaster* parent_) :
	AddRuler(ruler_, model_, parent_)
{
	setText("Rectangle Measurement");
}

void AddRectRuler::update() {
	parent->updateRR();
}

AddCircleRuler::AddCircleRuler(CircleRuler* ruler_, RulerModel* model_, ImageRaster* parent_) :
	AddRuler(ruler_, model_, parent_)
{
	setText("Circle Measurement");
}

void AddCircleRuler::update() {
	parent->updateCR();
}

AddCircle2Ruler::AddCircle2Ruler(Circle2Ruler* ruler_, RulerModel* model_, ImageRaster* parent_) :
	AddRuler(ruler_, model_, parent_)
{
	setText("Center-to-Center Measurement");
}

void AddCircle2Ruler::update() {
	parent->updateTC();
}

AddPolyRuler::AddPolyRuler(PolyRuler* ruler_, RulerModel* model_, ImageRaster* parent_) :
	AddRuler(ruler_, model_, parent_)
{
	setText("Polygon Measurement");
}

void AddPolyRuler::update() {
	parent->updatePR();
}

RColor1Chg::RColor1Chg(RulerModel* b, const QColor& old, const QColor& n, QUndoCommand* parent):
	QUndoCommand("Primary color changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void RColor1Chg::undo() {
	branch->setColor1(oldValue);
}

void RColor1Chg::redo() {
	branch->setColor1(newValue);
}

RColor2Chg::RColor2Chg(RulerModel* b, const QColor& old, const QColor& n, QUndoCommand* parent):
	QUndoCommand("Secondary color changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void RColor2Chg::undo() {
	branch->setColor2(oldValue);
}

void RColor2Chg::redo() {
	branch->setColor2(newValue);
}

RFontChg::RFontChg(RulerModel* b, const QFont& old, const QFont& n, QUndoCommand* parent):
	QUndoCommand("Font changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void RFontChg::undo() {
	branch->setFont(oldValue);
}

void RFontChg::redo() {
	branch->setFont(newValue);
}

RWidthChg::RWidthChg(RulerModel* b, const int& old, const int& n, QUndoCommand* parent):
	QUndoCommand("Pen width changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void RWidthChg::undo() {
	branch->setPenWidth(oldValue);
}

void RWidthChg::redo() {
	branch->setPenWidth(newValue);
}

RFontSizeChg::RFontSizeChg(RulerModel* b, const int& old, const int& n, QUndoCommand* parent):
	QUndoCommand("Font size changed", parent)
{
	branch = b;
	oldValue = old;
	newValue = n;
}

void RFontSizeChg::undo() {
	branch->setFontSize(oldValue);
}

void RFontSizeChg::redo() {
	branch->setFontSize(newValue);
}

RemoveItems::RemoveItems(QList<QGraphicsItem*> list, ImageRaster* ir, QUndoCommand* parent):
	QUndoCommand("Delete items", parent) 
{
	items = list;
	raster = ir;
	QList<LineRuler*> lr, rr, cr, tc, pr;
	rulers.insert(LineRuler::Type, lr);
	rulers.insert(RectRuler::Type, rr);
	rulers.insert(CircleRuler::Type, cr);
	rulers.insert(Circle2Ruler::Type, tc);
	rulers.insert(PolyRuler::Type, pr);

	RasterScene* scene = raster->getScene();
	for (auto item : items) {
		if (auto i = dynamic_cast<ArrowMarker*>(item)) {
			if (i->parentItem() != nullptr)
				continue;
			QPair<ArrowMarker*, Container*> pair;
			pair.first = i;
			pair.second = i->getBranch();
			markers.append(pair);
		}
		else if (rulers.contains(item->type())) {
			if (item->parentItem() != nullptr)
				continue;
			rulers[item->type()].append((LineRuler*)item);
		}
		else {
			if (item->parentItem() != nullptr)
				continue;
			EE.append(item);
		}
	}
}

void RemoveItems::undo() {
	RasterScene* scene = raster->getScene();
	for (auto p : markers) {
		p.second->addLeaf(p.first);
		scene->addItem(p.first);
	}
	for (auto i = rulers.begin(); i != rulers.end(); ++i) {
		for (auto p : i.value()) {
			raster->addRuler(i.key(), p);
			scene->addItem(p);
		}
	}
	for (auto p : EE)
		scene->addItem(p);
}

void RemoveItems::redo() {
	RasterScene* scene = raster->getScene();
	for (auto p : markers) {
		p.first->unbranch();
		scene->removeItem(p.first);
	}
	for (auto i = rulers.begin(); i != rulers.end(); ++i) {
		for (auto p : i.value()) {
			raster->deleteRuler(p);
			scene->removeItem(p);
		}
	}
	for (auto p : EE)
		scene->removeItem(p);
}
