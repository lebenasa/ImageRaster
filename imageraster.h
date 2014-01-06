#ifndef IMAGERASTER_H
#define IMAGERASTER_H

#include <QtWidgets/QMainWindow>
#include "ui_imageraster.h"
#include "ui_RulerDock.h"
#include "ui_MarkerDock.h"

class RasterScene;
class ColorToolbar;
class FontToolbar;
class nModeToolbar;
class StateManager;
class MarkerDock;
class MarkerModel;
class MarkerWidget;
class MarkerForm;
class MarkerBranch;
class Marker;
class GlobalSettings;
class ProfileForm;
class ProfileModel;
class Ruler;
class LineRuler;
class RectRuler;
class CircleRuler;
class Circle2Ruler;
class PolyRuler;
class RulerModel;
class RulerDock;
class ScaleDock;

class ImageRaster : public QMainWindow
{
	Q_OBJECT

public:
	ImageRaster(QWidget *parent = 0);
	~ImageRaster();
	RasterScene* getScene() { return scene; }
	void sceneAddItem(QGraphicsItem* item);
	void sceneRemoveItem(QGraphicsItem* item);

	enum ScaleType {
		Bar, Line, Simple };

private:
	Ui::ImageRasterClass ui;
	RasterScene *scene;
	void initScene(const QString&);

	//Params:
	bool hasImage;
	QSizeF originalSize;
	double zoom;
	QString image;

	//Init UI:
	void createActions();
	void createToolbars();

	void connectSignals();
	void loadSettings();
	std::vector<QObject*> myObjects;

	//Toolbars:
	ColorToolbar *colorToolbar;
	FontToolbar *fontToolbar;
	nModeToolbar *modeToolbar;

	//Actions:
	QAction *openImageAct;
	QAction *saveImageAct;
	QUndoStack *undoStack;
	QAction *undoAct;
	QAction *redoAct;
	QAction *deleteItemAct;
	QAction *zoomInAct;
	QAction *zoomOutAct;
	QAction *zoomToViewAct;
	QAction *zoomToActualAct;
	QLabel *zoomIndicator;

	//Widgets:
	//Markers:
	MarkerModel *markerModel;
	MarkerDock *markerDock;
	QDataWidgetMapper *mapMarker;
	//Calibration:
	ProfileModel *profileModel;
	ProfileForm *profileForm;
	QDataWidgetMapper *mapProfile;
	QDockWidget *profileDock;
	QToolBar *profileBar;
	QComboBox *profileCombo;
	QComboBox *modCombo;

	//LineRuler:
	RulerModel *lrModel;
	QDataWidgetMapper *mapLR;
	RulerDock *lrDock;
	//RectRuler :
	RulerModel *rrModel;
	QDataWidgetMapper *mapRR;
	RulerDock *rrDock;
	//CircleRuler:
	RulerModel *crModel;
	QDataWidgetMapper *mapCR;
	RulerDock *crDock;
	//Circle2Ruler:
	RulerModel *tcModel;
	QDataWidgetMapper *mapTC;
	RulerDock *tcDock;
	//PolygonRuler:
	RulerModel *prModel;
	QDataWidgetMapper *mapPR;
	RulerDock *prDock;

	//Features:
	ScaleDock *scaleDock;

	//Formats:
	int markerIndex;

	//Settings:
	GlobalSettings* mySettings;

	//Enums:
	enum CalibrationStatus {
		X, Y, Idle
	} cStatus;
	int tmpX;
	double modifier;

protected:
	void closeEvent(QCloseEvent *event);

public slots:
	void openImage();
	void saveImage();
	void deleteItem();
	void zoomIn();
	void zoomOut();
	void zoomToActual();
	void zoomToView();
	void sceneModeChanged(AppState);
	void firstMarker();
	void prevMarker();
	void nextMarker();
	void lastMarker();
	void appendMarker();
	void delMarker();
	void setMarker();

	void addMarker(Marker*);
	void updateMarker();
	void refreshIndicator();
	void chgVisibility(MarkerBranch*, bool);

	void labelChg(MarkerBranch*, QString, QString);
	void color1Chg(MarkerBranch*, QColor, QColor);
	void color2Chg(MarkerBranch*, QColor, QColor);
	void visibility(MarkerBranch*, bool);
	void fontChg(MarkerBranch*, QFont, QFont);
	void fontSizeChg(MarkerBranch*, int, int);
	void widthChg(MarkerBranch*, int, int);

	void appendProfile();
	void removeProfile();
	void calibrateProfile();
	void receiveCalibration(int pixel);
	void endCalibration();

	void addLR(LineRuler*);
	void updateLR();

	void rColor1Chg(QColor, QColor);
	void rColor2Chg(QColor, QColor);
	void rFontChg(QFont, QFont);
	void rFontSizeChg(int, int);
	void rWidthChg(int, int);
	void defaultText();

	void addRR(RectRuler*);
	void updateRR();

	void addCR(CircleRuler*);
	void updateCR();

	void addTC(Circle2Ruler*);
	void updateTC();

	void addPR(PolyRuler*);
	void updatePR();

	void updateRulers();
	void updateModifier(int);

	void on_actionScale_triggered();
	void addScale(int, int);
	void hideScale();
};

#endif // IMAGERASTER_H
