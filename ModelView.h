#pragma once
#include "qabstractitemmodel.h"
#include "RasterSettings.h"

class ImageRaster;
class LineRuler;

//Placeholder for Markers Data
//struct MarkerData
//{
//	QString label;
//	int count;
//	QColor color;
//	bool visible;
//
//	MarkerData(QString l="", int c=0, QColor col=QColor("black"), bool v=true) :
//		label(l), count(c), color(col), visible(v), mainBranch(new Container) { }
//	void addItem(Container* leaf) {
//		mainBranch->addLeaf(leaf);
//	}
//private:
//	Container* mainBranch;
//};

//class MarkerData :
//	public Container
//{
//	//Deprecated...use MarkerBranch instead...
//	QString myLabel;
//	int myCount;
//	QColor myColor;
//	bool myVisible;
//public:
//	MarkerData(QString l="", int c=0, QColor col=QColor(), bool v=true) :
//		Container(), myLabel(l), myCount(c), myColor(col), myVisible(v) { }
//	~MarkerData() { }
//
//	QString label() const { return myLabel; }
//	int count() const { return myCount; }
//	QColor color() const { return myColor; }
//	bool visible() const { return myVisible; }
//
//	void setLabel(const QString l) { myLabel = l; }
//	void setCount(const int c) { myCount = c; }
//	void setColor(const QColor col) { myColor = col; }
//	void setVisible(const bool v) { myVisible = v; }
//};

class MarkerBranch :
	public mData,		//label
	public Format,		//Font, Inner & Outer Pen
	public Container	//leaves
{
	bool myVisible;
	int penWidth;
	int pixelSize;
public:
	MarkerBranch(bool v=true) :
		mData(), Format(), Container(), myVisible(v), penWidth(1), pixelSize(12) { }
	~MarkerBranch() { }

	int count() const { return leaves.count(); }

	bool visible() const { return myVisible; }
	void setVisible(const bool v);

	//Convenient methods:
	QColor color1() const { return myInPen.color(); }
	QColor color2() const { return myOutPen.color(); }
	int width()		const { return penWidth; }
	int fontSize()	const { return pixelSize; }

	void setColor1(const QColor& col);
	void setColor2(const QColor& col);
	void setWidth(int w);
	void setFontSize(int size);
	void setLabel(const QString& txt) override;
	void setFont(const QFont& f) override;
};

//The model for Markers
class MarkerModel :
	public QAbstractTableModel
{
	Q_OBJECT
	int col;
	std::vector<MarkerBranch*> myData;
public:
	MarkerModel(QObject *parent=0);
	~MarkerModel(void);
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex& index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

	MarkerBranch* at(int);
	void updateWidgets();
	bool insertBranch(int row, MarkerBranch* b, const QModelIndex& parent = QModelIndex());
signals:
	void labelChg(MarkerBranch*, QString, QString);
	void color1Chg(MarkerBranch*, QColor, QColor);
	void color2Chg(MarkerBranch*, QColor, QColor);
	void visibility(MarkerBranch*, bool);
	void fontChg(MarkerBranch*, QFont, QFont);
	void fontSizeChg(MarkerBranch*, int, int);
	void widthChg(MarkerBranch*, int, int);
};

//Basically a copy of ColorListEditor
class ColorListEditor :
	public QComboBox
{
	Q_OBJECT
	Q_PROPERTY(QColor color READ color WRITE setColor USER true)

	void populateList();
public:
	ColorListEditor(QWidget *widget=0);

	QColor color() const;
	void setColor(QColor c);
};

//A convenient widget which will be mapped to MarkerModel
//class MarkerWidget :
//	public QWidget
//{
//	Q_OBJECT
//	friend class ImageRaster;
//	QLabel lb1, lb2, lb3, lb4;
//	QGridLayout myLayout;
//	QLineEdit label;
//	QLineEdit count;
//	ColorListEditor color;
//	QCheckBox visible;
//	QPushButton first, before, next, last;
//	QPushButton set, add, del;
//public:
//	MarkerWidget(QWidget* parent=0);
//public slots:
//	void colorChanged(int);
//signals:
//	bool notifChanged();
//};


//The model for calibration profile:
class ProfileModel :
	public QAbstractTableModel
{
	Q_OBJECT
	std::vector<CalibrationProfile> myData;
public:
	ProfileModel(QObject* parent=0);
	~ProfileModel() {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex& index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

	CalibrationProfile at(int i);
	bool insertProfile(int row, CalibrationProfile profile, const QModelIndex& parent = QModelIndex());

	std::vector<CalibrationProfile> getData() {
		return myData;
	}
};

class RulerModel :
	public QAbstractTableModel
{
	//Base model for all rulers
	Q_OBJECT
	std::vector<LineRuler*> myData;
	QColor myColor1, myColor2;
	QFont myFont;
	int myPenWidth, myFontSize;
public:
	RulerModel(QObject* parent=0);
	~RulerModel();

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex& index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

	LineRuler* at(int);
	void updateWidgets();
	bool insertBranch(int row, LineRuler* b, const QModelIndex& parent = QModelIndex());

	std::vector<LineRuler*> branches() { return myData; }

	QColor color1() const { return myColor1; }
	QColor color2() const { return myColor2; }
	int penWidth()	const { return myPenWidth; }
	int fontSize()	const { return myFontSize; }
	QFont font() const	  { return myFont; }

	void setColor1(const QColor& col);
	void setColor2(const QColor& col);
	void setPenWidth(int w);
	void setFontSize(int size);
	void setFont(const QFont& f);
signals:
	void color1Chg(QColor, QColor);
	void color2Chg(QColor, QColor);
	void fontChg(QFont, QFont);
	void fontSizeChg(int, int);
	void penWidthChg(int, int);
};