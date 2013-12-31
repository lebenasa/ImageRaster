#include "stdafx.h"
#include "ModelView.h"
#include "Arrow.h"
#include "RasterSettings.h"

void MarkerBranch::setColor1(const QColor& col)	{
	myInPen.setColor(col);
	myInPen.setWidth(penWidth);
	for (auto p : leafItems()) {
		if (auto b = (ArrowMarker*)p)
			b->setPen1(myInPen);
	}
}

void MarkerBranch::setColor2(const QColor& col)	{
	myOutPen.setColor(col);
	for (auto p : leafItems()) {
		if (auto b = (ArrowMarker*)p)
			b->setPen2(myOutPen);
	}
}

void MarkerBranch::setWidth(int w) {
	penWidth = w;
	myInPen.setWidth(penWidth);
	for (auto p : leafItems()) {
		if (auto b = (ArrowMarker*)p) {
			b->setPen1(myInPen);
		}
	}
}

void MarkerBranch::setFontSize(int size) {
	pixelSize = size;
	QFont f = myFont;
	f.setPixelSize(size);
	myFont = f;
	for (auto p : leafItems()) {
		if (auto b = (ArrowMarker*)p)
			b->setFont(f);
	}
}

void MarkerBranch::setVisible(const bool v) {
	myVisible = v;
}

void MarkerBranch::setLabel(const QString& txt) {
	myLabel = txt;
	for (auto p : leafItems()) {
		if (auto b = (ArrowMarker*)p)
			b->setLabel(myLabel);
	}
}

void MarkerBranch::setFont(const QFont& f) {
	myFont = f;
	for (auto p : leafItems()) {
		if (auto b = (ArrowMarker*)p)
			b->setFont(myFont);
	}
}

MarkerModel::MarkerModel(QObject *parent)
	: QAbstractTableModel(parent), col(8)
{
}

MarkerModel::~MarkerModel(void)
{
}

int MarkerModel::rowCount(const QModelIndex& parent) const {
	return myData.size();
}

int MarkerModel::columnCount(const QModelIndex& parent) const {
	return col;
}

QVariant MarkerModel::data(const QModelIndex& index, int role) const {
	if (index.row() >= myData.size()) return QVariant();
	int c = index.column();
	if (Qt::CheckStateRole == role) {
		if (4 == c)
			return (myData.at(index.row())->visible()) ? Qt::Checked : Qt::Unchecked;
	}
	else if (Qt::DisplayRole == role || Qt::EditRole == role) {
		if (0 == c)
			return myData.at(index.row())->label();
		else if (1 == c)
			return myData.at(index.row())->count();
		else if (2 == c)
			return myData.at(index.row())->color1();
		else if (3 == c)
			return myData.at(index.row())->color2();
		else if (4 == c)
			return myData.at(index.row())->visible();
		else if (5 == c)
			return myData.at(index.row())->width();
		else if (6 == c)
			return myData.at(index.row())->font();
		else if (7 == c)
			return myData.at(index.row())->fontSize();
	}
	else if (Qt::DecorationRole == role) {
		if (2 == c)
			return myData.at(index.row())->color1();
		else if (3 == c)
			return myData.at(index.row())->color2();
	}
	else if (Qt::FontRole == role) {
		if (6 == c)
			return myData.at(index.row())->font();
	}
	return QVariant();
}

Qt::ItemFlags MarkerModel::flags(const QModelIndex& index) const {
	int c = index.column();
	if (0 == c)
		return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	else if (1 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	else if (2 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (3 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (4 == c)
		return Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	else if (5 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (6 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (7 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	return 0;
}

QVariant MarkerModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (Qt::DisplayRole != role) return QVariant();
	if (Qt::Horizontal == orientation) {
		if (0 == section)
			return "Label";
		else if (1 == section)
			return "Count";
		else if (2 == section)
			return "Color1";
		else if (3 == section)
			return "Color2";
		else if (4 == section)
			return "Visible";
		else if (5 == section)
			return "Width";
		else if (6 == section)
			return "Font";
		else if (7 == section)
			return "Font Size";
	}
	return QString().number(section+1);
}

bool MarkerModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	int c = index.column();
	MarkerBranch* b = myData.at(index.row());
	if (Qt::CheckStateRole == role) {
		if (4 == c)
			if (value.toBool() != b->visible()) emit visibility(b, value.toBool());
		emit dataChanged(index, index);
		return true;
	}
	else if (Qt::EditRole == role) {
		if (0 == c)
			emit labelChg(b, b->label(), value.toString());
		else if (2 == c)
			emit color1Chg(b, b->color1(), qvariant_cast<QColor>(value));
		else if (3 == c)
			emit color2Chg(b, b->color2(), qvariant_cast<QColor>(value));
		else if (4 == c) {
			if (value.toBool() != b->visible()) emit visibility(b, value.toBool());
		}
		else if (5 == c)
			emit widthChg(b, b->width(), value.toInt());
		else if (6 == c)
			emit fontChg(b, b->font(), qvariant_cast<QFont>(value));
		else if (7 == c)
			emit fontSizeChg(b, b->fontSize(), value.toInt());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

bool MarkerModel::insertRows(int row, int count, const QModelIndex& parent) {
	beginInsertRows(parent, row, row+count-1);
	for (int i=row; i<row+count; ++i) {
		MarkerBranch *dat = new MarkerBranch();
		auto p = myData.begin()+i;
		myData.insert(p, dat);
	}
	endInsertRows();
	return true;
}

bool MarkerModel::insertBranch(int row, MarkerBranch* b, const QModelIndex& parent) {
	beginInsertRows(parent, row, row);
	for (int i=row; i<row+1; ++i) {
		auto p = myData.begin()+i;
		myData.insert(p, b);
	}
	endInsertRows();
	return true;
}

bool MarkerModel::removeRows(int row, int count, const QModelIndex& parent) {
	beginRemoveRows(parent, row, row+count-1);
	for (int i=row; i<row+count; ++i) {
		auto p = myData.begin()+i;
		myData.erase(p);
	}
	endRemoveRows();
	return true;
}

MarkerBranch* MarkerModel::at(int i) {
	if (myData.size() > i && 0 <= i)
		return myData.at(i);
	else return nullptr;
}

void MarkerModel::updateWidgets() {
	emit dataChanged(index(0, 0), index(rowCount()-1, columnCount()-1));
}
 
//MarkerWidget::MarkerWidget(QWidget* parent) :
//	QWidget(parent),
//	lb1("Label", this), lb2("Count", this), lb3("Color", this), lb4("Visible", this),
//	label(this), count(this), color(this), visible("", this),
//	first("<<", this), before("<", this), next(">", this), last(">>", this),
//	set("Set", this), add("Add", this), del("Remove", this),
//	myLayout(this)
//{
//	count.setReadOnly(true);
//	first.setMinimumWidth(30);
//	before.setMinimumWidth(30);
//	next.setMinimumWidth(30);
//	last.setMinimumWidth(30);
//	set.setMinimumWidth(30);
//	add.setMinimumWidth(30);
//	del.setMinimumWidth(30);
//	//first.setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
//	//before.setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
//	//next.setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
//	//last.setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
//	//set.setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
//	//add.setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
//	//del.setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
//	myLayout.addWidget(&lb1,	 0, 0, 1, 1, Qt::AlignLeft);
//	myLayout.addWidget(&label,	 0, 1, 1, 3, Qt::AlignLeft);
//	myLayout.addWidget(&lb2,	 1, 0, 1, 1, Qt::AlignLeft);
//	myLayout.addWidget(&count,	 1, 1, 1, 3, Qt::AlignLeft);
//	myLayout.addWidget(&lb3,	 2, 0, 1, 1, Qt::AlignLeft);
//	myLayout.addWidget(&color,	 2, 1, 1, 3, Qt::AlignLeft);
//	myLayout.addWidget(&lb4,	 3, 0, 1, 1, Qt::AlignLeft);
//	myLayout.addWidget(&visible, 3, 1, 1, 3, Qt::AlignLeft);
//	myLayout.addWidget(&first,	 4, 0, 1, 1);
//	myLayout.addWidget(&before,	 4, 1, 1, 1);
//	myLayout.addWidget(&next,	 4, 2, 1, 1);
//	myLayout.addWidget(&last,	 4, 3, 1, 1);
//	myLayout.addWidget(&add,	 5, 0, 1, 2);
//	myLayout.addWidget(&del,	 5, 2, 1, 2);
//	myLayout.addWidget(&set,	 6, 0, 1, 4);
//
//	connect(&color, SIGNAL(currentIndexChanged(int)), this, SLOT(colorChanged(int)));
//	connect(&visible, SIGNAL(stateChanged(int)), this, SLOT(colorChanged(int)));
//	setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
//}
//
//void MarkerWidget::colorChanged(int) {
//	emit notifChanged();
//}

ColorListEditor::ColorListEditor(QWidget* widget) :
	QComboBox(widget)
{
	populateList();
}

QColor ColorListEditor::color() const {
	return qvariant_cast<QColor>(itemData(currentIndex(), Qt::DecorationRole));
}

void ColorListEditor::setColor(QColor c) {
	setCurrentIndex(findData(c, int(Qt::DecorationRole)));
}

void ColorListEditor::populateList() {
	QStringList colorNames = QColor::colorNames();
	for (int i=0; i<colorNames.size(); ++i) {
		QColor color(colorNames[i]);
		insertItem(i, colorNames[i]);
		setItemData(i, color, Qt::DecorationRole);
	}
}

ProfileModel::ProfileModel(QObject* parent) :
	QAbstractTableModel(parent)
{
}

int ProfileModel::columnCount(const QModelIndex& parent) const {
	return 3;
}

int ProfileModel::rowCount(const QModelIndex& parent) const {
	return myData.size();
}

QVariant ProfileModel::data(const QModelIndex& index, int role) const {
	if (index.row() >= myData.size()) return QVariant();
	int c = index.column();
	if (Qt::DisplayRole == role || Qt::EditRole == role) {
		if (0 == c)
			return myData.at(index.row()).qname();
		else if (1 == c)
			return myData.at(index.row()).x();
		else if (2 == c)
			return myData.at(index.row()).y();
	}
	return QVariant();
}

Qt::ItemFlags ProfileModel::flags(const QModelIndex& index) const {
	int c = index.column();
	if (0 == c)
		return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	else if (1 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (2 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	return 0;
}

QVariant ProfileModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (Qt::DisplayRole != role) return QVariant();
	if (Qt::Horizontal == orientation) {
		if (0 == section)
			return "Name";
		else if (1 == section)
			return "X";
		else if (2 == section)
			return "Y";
	}
	return QString().number(section+1);
}

bool ProfileModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	int c = index.column();
	CalibrationProfile* b = &myData.at(index.row());
	if (Qt::EditRole == role) {
		if (0 == c)
			b->setName(value.toString());
		else if (1 == c)
			b->setX(value.toInt());
		else if (2 == c)
			b->setY(value.toInt());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

bool ProfileModel::insertRows(int row, int count, const QModelIndex& parent) {
	beginInsertRows(parent, row, row+count-1);
	for (int i=row; i<row+count; ++i) {
		CalibrationProfile dat;
		auto p = myData.begin()+i;
		myData.insert(p, dat);
	}
	endInsertRows();
	return true;
}

bool ProfileModel::removeRows(int row, int count, const QModelIndex& parent) {
	beginRemoveRows(parent, row, row+count-1);
	for (int i=row; i<row+count; ++i) {
		auto p = myData.begin()+i;
		myData.erase(p);
	}
	endRemoveRows();
	return true;
}

CalibrationProfile ProfileModel::at(int i) {
	if (myData.size() > i && 0 <= i)
		return myData.at(i);
	else return nullptr;
}

bool ProfileModel::insertProfile(int row, CalibrationProfile profile, const QModelIndex& parent) {
	beginInsertRows(parent, row, row);
	for (int i=row; i<row+1; ++i) {
		auto p = myData.begin()+i;
		myData.insert(p, profile);
	}
	endInsertRows();
	return true;
}

//class RulerModel:
//MVC model for rulers
RulerModel::RulerModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	myColor1 = QColor(Qt::black);
	myColor2 = QColor(Qt::white);
	myPenWidth = 1;
	myFont = QFont("Courrier");
	myFontSize = 12;
}

RulerModel::~RulerModel(void)
{
}

int RulerModel::rowCount(const QModelIndex& parent) const {
	return myData.size();
}

int RulerModel::columnCount(const QModelIndex& parent) const {
	return 11;
}

QVariant RulerModel::data(const QModelIndex& index, int role) const {
	if (index.row() >= myData.size()) return QVariant();
	int c = index.column();

	if (Qt::DisplayRole == role || Qt::EditRole == role) {
		if (0 == c)
			return myData.at(index.row())->length();
		else if (1 == c)
			return myData.at(index.row())->width();
		else if (2 == c)
			return myData.at(index.row())->height();
		else if (3 == c)
			return myData.at(index.row())->radius();
		else if (4 == c)
			return myData.at(index.row())->area();
		else if (5 == c)
			return myColor1;
		else if (6 == c)
			return myColor2;
		else if (7 == c)
			return myPenWidth;
		else if (8 == c)
			return myFont;
		else if (9 == c)
			return myFontSize;
		else if (10 == c)
			return myData.at(index.row())->text();
	}
	else if (Qt::DecorationRole == role) {
		if (5 == c)
			return myColor1;
		else if (6 == c)
			return myColor2;
	}
	else if (Qt::FontRole == role) {
		if (8 == c)
			return myFont;
	}
	return QVariant();
}

Qt::ItemFlags RulerModel::flags(const QModelIndex& index) const {
	int c = index.column();
	if (0 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	else if (1 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	else if (2 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	else if (3 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	else if (4 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	else if (5 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (6 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (7 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (8 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (9 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	else if (10 == c)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	return 0;
}

QVariant RulerModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (Qt::DisplayRole != role) return QVariant();
	if (Qt::Horizontal == orientation) {
		if (0 == section)
			return tr("Length") + QString::fromLatin1(" (µm)");
		else if (1 == section)
			return tr("Width") + QString::fromLatin1(" (µm)");
		else if (2 == section)
			return tr("Height") + QString::fromLatin1(" (µm)");
		else if (3 == section)
			return tr("Radius") + QString::fromLatin1(" (µm)");
		else if (4 == section)
			return tr("Area") + QString::fromLatin1(" (µm²)");
		else if (5 == section)
			return "Color";
		else if (6 == section)
			return "Outline";
		else if (7 == section)
			return "Line Weight";
		else if (8 == section)
			return "Font";
		else if (9 == section)
			return "Font Size";
		else if (10 == section)
			return "Text";
	}
	return QString().number(section+1);
}

bool RulerModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	int c = index.column();
	LineRuler* branch = myData.at(index.row());
	if (Qt::EditRole == role) {
		if (0 == c)
			branch->setLength(value.toInt());
		else if (1 == c)
			branch->setWidth(value.toInt());
		else if (2 == c)
			branch->setHeight(value.toInt());
		else if (3 == c)
			branch->setRadius(value.toInt());
		else if (4 == c)
			branch->setArea(value.toInt());
		else if (5 == c)
			emit color1Chg(color1(), qvariant_cast<QColor>(value));
		else if (6 == c)
			emit color2Chg(color2(), qvariant_cast<QColor>(value));
		else if (7 == c)
			emit penWidthChg(penWidth(), value.toInt());
		else if (8 == c)
			emit fontChg(font(), qvariant_cast<QFont>(value));
		else if (9 == c)
			emit fontSizeChg(fontSize(), value.toInt());
		else if (10 == c)
			branch->setText(value.toString());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

bool RulerModel::insertRows(int row, int count, const QModelIndex& parent) {
	beginInsertRows(parent, row, row+count-1);
	for (int i=row; i<row+count; ++i) {
		LineRuler* branch = new LineRuler(QLineF());
		auto p = myData.begin() + i;
		myData.insert(p, branch);
	}
	endInsertRows();
	return true;
}

bool RulerModel::insertBranch(int row, LineRuler* b, const QModelIndex& parent) {
	beginInsertRows(parent, row, row);
	for (int i=row; i<row+1; ++i) {
		auto p = myData.begin() + i;
		myData.insert(p, b);
	}
	endInsertRows();
	return true;
}

bool RulerModel::removeRows(int row, int count, const QModelIndex& parent) {
	beginRemoveRows(parent, row, row+count-1);
	for (int i=row; i<row+count; ++i) {
		auto p = myData.begin() + i;
		myData.erase(p);
	}
	endRemoveRows();
	return true;
}

LineRuler* RulerModel::at(int i) {
	if (myData.size() > i && 0 <= i)
		return myData.at(i);
	else return nullptr;
}

void RulerModel::updateWidgets() {
	emit dataChanged(index(0, 0), index(rowCount()-1, columnCount()-1));
}

void RulerModel::setColor1(const QColor& col)	{
	myColor1 = col;
	QPen p = QPen(col);
	p.setWidth(myPenWidth);
	for (auto r : myData) {
		r->setPen1(p);
	}
}

void RulerModel::setColor2(const QColor& col)	{
	myColor2 = col;
	QPen p = QPen(col);
	for (auto r : myData) {
		r->setPen2(p);
	}
}

void RulerModel::setFont(const QFont& f) {
	myFont = f;
	myFont.setPixelSize(myFontSize);
	for (auto r : myData) {
		r->setFont(f);
	}
}

void RulerModel::setFontSize(int size) {
	myFontSize = size;
	setFont(myFont);
}

void RulerModel::setPenWidth(int w) {
	myPenWidth = w;
	setColor1(myColor1);
	setColor2(myColor2);
}