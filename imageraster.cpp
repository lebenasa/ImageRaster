#include "stdafx.h"
#include "imageraster.h"
#include "RasterScene.h"
#include "nModeToolbar.h"
#include "StateManager.h"
#include "ModelView.h"
#include "MarkerForm.h"
#include "UndoCommand.h"
#include "Arrow.h"
#include "RasterSettings.h"
#include "ProfileForms.h"
#include "Forms.h"

ImageRaster::ImageRaster(QWidget *parent)
	: QMainWindow(parent), hasImage(false)
{
	ui.setupUi(this);
	QMetaObject::connectSlotsByName(this);
	scene = new RasterScene(this);
	modeToolbar = new nModeToolbar("Mode Select", this);
	loadSettings();
	createActions();
	createToolbars();
	//for debugging purpose:
	initScene(QDir::homePath()+"/oreimo.jpg");
	markerIndex = 0;
	modifier = 1.0;
}

ImageRaster::~ImageRaster()
{
	delete scene;
	delete modeToolbar;
}

void ImageRaster::createActions() {
	openImageAct = new QAction(QIcon(":/Resources/Open.png"), tr("&Open Image"), this);
	openImageAct->setStatusTip(tr("Open image from file"));
	openImageAct->setShortcut(QKeySequence::Open);
	saveImageAct = new QAction(QIcon(":/Resources/Save.png"), tr("&Save Image"), this);
	saveImageAct->setStatusTip(tr("Save and upload edited image"));
	saveImageAct->setShortcut(QKeySequence::Save);
	saveImageAct->setEnabled(false);

	connect(openImageAct, &QAction::triggered, this, &ImageRaster::openImage);

	undoStack = new QUndoStack(this);
	undoAct = undoStack->createUndoAction(this, tr("&Undo"));
	undoAct->setIcon(QIcon(":/Resources/Undo.png"));
	undoAct->setShortcut(QKeySequence::Undo);
	redoAct = undoStack->createRedoAction(this, tr("&Redo"));
	redoAct->setIcon(QIcon(":/Resources/Redo.png"));
	redoAct->setShortcut(QKeySequence::Redo);

	deleteItemAct = new QAction(QIcon(":/Resources/Delete.png"), tr("&Delete Item"), this);
	deleteItemAct->setStatusTip(tr("Delete item(s) from scene"));
	deleteItemAct->setShortcut(QKeySequence::Delete);

	zoomInAct = new QAction(QIcon(":/Resources/ZoomIn.png"), tr("Zoom In"), this);
	zoomInAct->setShortcut(QKeySequence(Qt::Key_PageUp));
	zoomOutAct = new QAction(QIcon(":/Resources/ZoomOut.png"), tr("Zoom Out"), this);
	zoomOutAct->setShortcut(QKeySequence(Qt::Key_PageDown));
	zoomToViewAct = new QAction(QIcon(":/Resources/ZoomFit.png"), tr("Fit to View"), this);
	zoomToViewAct->setShortcut(QKeySequence(Qt::Key_End));
	zoomToActualAct = new QAction(QIcon(":/Resources/ZoomActual.png"), tr("Actual Size"), this);
	zoomToActualAct->setShortcut(QKeySequence(Qt::Key_Home));

	zoomIndicator = new QLabel;
	statusBar()->addPermanentWidget(zoomIndicator);
	
	ui.mainToolBar->addAction(openImageAct);
	ui.mainToolBar->addAction(saveImageAct);
	ui.mainToolBar->addAction(deleteItemAct);
	ui.mainToolBar->addAction(undoAct);
	ui.mainToolBar->addAction(redoAct);
	ui.mainToolBar->addAction(deleteItemAct);
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction(zoomInAct);
	ui.mainToolBar->addAction(zoomOutAct);
	ui.mainToolBar->addAction(zoomToViewAct);
	ui.mainToolBar->addAction(zoomToActualAct);

	ui.menuFile->addAction(openImageAct);
	ui.menuFile->addAction(saveImageAct);
	ui.menuView->addAction(zoomInAct);
	ui.menuView->addAction(zoomOutAct);
	ui.menuView->addAction(zoomToViewAct);
	ui.menuView->addAction(zoomToActualAct);
	ui.menuEdit->addAction(undoAct);
	ui.menuEdit->addAction(redoAct);

	ui.menuTools->addAction(ui.actionScale);
	ui.menuTools->addAction(ui.actionBlend);
	ui.menuTools->addAction(ui.actionLegend);
}

void ImageRaster::createToolbars() {
	addToolBar(Qt::LeftToolBarArea, modeToolbar);
	modeToolbar->setEnabled(false);

	//Init Editor Factory:
	QItemEditorFactory *factory = new QItemEditorFactory;
	QItemEditorCreatorBase *colorListCreator =
		new QStandardItemEditorCreator<ColorListEditor>();
	QItemEditorCreatorBase *stringCreator =
		new QStandardItemEditorCreator<QLineEdit>();

	factory->registerEditor(QVariant::Color, colorListCreator);
	factory->registerEditor(QVariant::String, stringCreator);
	QItemEditorFactory::setDefaultFactory(factory);

	//Create View:
	markerDock = new MarkerDock(this);
	markerDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
	markerModel = new MarkerModel(this);
	markerDock->view->setModel(markerModel);
	mapMarker = new QDataWidgetMapper(this);
	mapMarker->setModel(markerModel);
	mapMarker->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	//mapMarker->addMapping(&markerWidget->label, 0);
	//mapMarker->addMapping(&markerWidget->count, 1);
	//mapMarker->addMapping(&markerWidget->color, 2);
	//mapMarker->addMapping(&markerWidget->visible, 3);
	mapMarker->addMapping(markerDock->label, 0);
	mapMarker->addMapping(markerDock->count, 1);
	mapMarker->addMapping(markerDock->color1, 2);
	mapMarker->addMapping(markerDock->color2, 3);
	mapMarker->addMapping(markerDock->checkBox, 4);
	mapMarker->addMapping(markerDock->weight, 5);
	mapMarker->addMapping(markerDock->font_, 6);
	mapMarker->addMapping(markerDock->fontSize, 7);

	markerDock->view->resizeColumnsToContents();
	markerDock->view->hideColumn(5);
	markerDock->view->hideColumn(6);
	markerDock->view->hideColumn(7);
	addDockWidget(Qt::RightDockWidgetArea, markerDock);
	mapMarker->toFirst();
	setMarker();
	markerDock->hide();
	appendMarker();
	appendMarker();
	firstMarker();

	//Profile manager:
	profileModel = new ProfileModel(this);
	profileDock = new QDockWidget(tr("Calibration Profile"), this);
	profileForm = new ProfileForm(profileDock);
	mapProfile = new QDataWidgetMapper(this);
	profileForm->ui->view->setModel(profileModel);
	mapProfile->setModel(profileModel);
	mapProfile->addMapping(profileForm->ui->x, 1);
	mapProfile->addMapping(profileForm->ui->y, 2);
	profileDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
	profileDock->setWidget(profileForm);
	addDockWidget(Qt::RightDockWidgetArea, profileDock);
	profileDock->hide();
	for (auto profile : mySettings->getProfiles())
		profileModel->insertProfile(profileModel->rowCount(), profile);
	mapProfile->toFirst();

	//Line Ruler:
	lrModel = new RulerModel(this);
	lrDock = new RulerDock(this);
	lrDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
	mapLR = new QDataWidgetMapper(this);
	mapLR->setModel(lrModel);
	lrDock->view->setModel(lrModel);
	lrDock->num1->setText(tr("Length") + QString::fromLatin1(" (µm)"));
	lrDock->num2->hide();
	lrDock->num3->hide();
	lrDock->data2->hide();
	lrDock->data3->hide();
	mapLR->addMapping(lrDock->data1, 0);
	mapLR->addMapping(lrDock->color1, 5);
	mapLR->addMapping(lrDock->color2, 6);
	mapLR->addMapping(lrDock->penWidth, 7);
	mapLR->addMapping(lrDock->font_, 8);
	mapLR->addMapping(lrDock->fontSize, 9);
	mapLR->addMapping(lrDock->text, 10);
	addDockWidget(Qt::RightDockWidgetArea, lrDock);
	lrDock->view->hideColumn(1);
	lrDock->view->hideColumn(2);
	lrDock->view->hideColumn(3);
	lrDock->view->hideColumn(4);
	lrDock->view->hideColumn(5);
	lrDock->view->hideColumn(6);
	lrDock->view->hideColumn(7);
	lrDock->view->hideColumn(8);
	lrDock->view->hideColumn(9);
	//lrDock->view->hideColumn(10);
	lrDock->hide();

	//RectRuler:
	rrModel = new RulerModel(this);
	rrDock = new RulerDock(this);
	rrDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
	mapRR = new QDataWidgetMapper(this);
	mapRR->setModel(rrModel);
	rrDock->view->setModel(rrModel);
	rrDock->num1->setText(tr("Width") + QString::fromLatin1(" (µm)"));
	rrDock->num2->setText(tr("Height") + QString::fromLatin1(" (µm)"));
	//rrDock->num1->setText(tr("Area") + QString::fromLatin1(" (µm)"));
	rrDock->num3->hide();
	rrDock->data3->hide();
	mapRR->addMapping(rrDock->data1, 1);
	mapRR->addMapping(rrDock->data2, 2);
	//mapRR->addMapping(rrDock->data3, 4);
	mapRR->addMapping(rrDock->color1, 5);
	mapRR->addMapping(rrDock->color2, 6);
	mapRR->addMapping(rrDock->penWidth, 7);
	mapRR->addMapping(rrDock->font_, 8);
	mapRR->addMapping(rrDock->fontSize, 9);
	mapRR->addMapping(rrDock->text, 10);
	addDockWidget(Qt::RightDockWidgetArea, rrDock);
	rrDock->view->hideColumn(0);
	rrDock->view->hideColumn(3);
	rrDock->view->hideColumn(4);
	rrDock->view->hideColumn(5);
	rrDock->view->hideColumn(6);
	rrDock->view->hideColumn(7);
	rrDock->view->hideColumn(8);
	rrDock->view->hideColumn(9);
	//rrDock->view->hideColumn(10);
	rrDock->hide();

	//CircleRuler:
	crModel = new RulerModel(this);
	crDock = new RulerDock(this);
	crDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
	mapCR = new QDataWidgetMapper(this);
	mapCR->setModel(crModel);
	crDock->view->setModel(crModel);
	crDock->num1->setText(tr("Radius") + QString::fromLatin1(" (µm)"));
	crDock->num2->hide();
	crDock->data2->hide();
	crDock->num3->hide();
	crDock->data3->hide();
	mapCR->addMapping(crDock->data1, 3);
	mapCR->addMapping(crDock->color1, 5);
	mapCR->addMapping(crDock->color2, 6);
	mapCR->addMapping(crDock->penWidth, 7);
	mapCR->addMapping(crDock->font_, 8);
	mapCR->addMapping(crDock->fontSize, 9);
	mapCR->addMapping(crDock->text, 10);
	addDockWidget(Qt::RightDockWidgetArea, crDock);
	crDock->view->hideColumn(0);
	crDock->view->hideColumn(1);
	crDock->view->hideColumn(2);
	crDock->view->hideColumn(4);
	crDock->view->hideColumn(5);
	crDock->view->hideColumn(6);
	crDock->view->hideColumn(7);
	crDock->view->hideColumn(8);
	crDock->view->hideColumn(9);
	//crDock->view->hideColumn(10);
	crDock->hide();

	//Circle2Ruler:
	tcModel = new RulerModel(this);
	tcDock = new RulerDock(this);
	tcDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
	mapTC = new QDataWidgetMapper(this);
	mapTC->setModel(tcModel);
	tcDock->view->setModel(tcModel);
	tcDock->num1->setText(tr("Length") + QString::fromLatin1(" (µm)"));
	tcDock->num2->hide();
	tcDock->num3->hide();
	tcDock->data2->hide();
	tcDock->data3->hide();
	mapTC->addMapping(tcDock->data1, 0);
	mapTC->addMapping(tcDock->color1, 5);
	mapTC->addMapping(tcDock->color2, 6);
	mapTC->addMapping(tcDock->penWidth, 7);
	mapTC->addMapping(tcDock->font_, 8);
	mapTC->addMapping(tcDock->fontSize, 9);
	mapTC->addMapping(tcDock->text, 10);
	addDockWidget(Qt::RightDockWidgetArea, tcDock);
	tcDock->view->hideColumn(1);
	tcDock->view->hideColumn(2);
	tcDock->view->hideColumn(3);
	tcDock->view->hideColumn(4);
	tcDock->view->hideColumn(5);
	tcDock->view->hideColumn(6);
	tcDock->view->hideColumn(7);
	tcDock->view->hideColumn(8);
	tcDock->view->hideColumn(9);
	//tcDock->view->hideColumn(10);
	tcDock->hide();

	//PolyRuler:
	prModel = new RulerModel(this);
	prDock = new RulerDock(this);
	prDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
	mapPR = new QDataWidgetMapper(this);
	mapPR->setModel(prModel);
	prDock->view->setModel(prModel);
	prDock->num1->setText(tr("Length") + QString::fromLatin1(" (µm)"));
	prDock->num2->setText(tr("Area") + QString::fromLatin1(" (µm²)"));
	prDock->num3->hide();
	prDock->data3->hide();
	mapPR->addMapping(prDock->data1, 0);
	mapPR->addMapping(prDock->data2, 4);
	mapPR->addMapping(prDock->color1, 5);
	mapPR->addMapping(prDock->color2, 6);
	mapPR->addMapping(prDock->penWidth, 7);
	mapPR->addMapping(prDock->font_, 8);
	mapPR->addMapping(prDock->fontSize, 9);
	mapPR->addMapping(prDock->text, 10);
	addDockWidget(Qt::RightDockWidgetArea, prDock);
	//prDock->view->hideColumn(0);
	prDock->view->hideColumn(1);
	prDock->view->hideColumn(2);
	prDock->view->hideColumn(3);
	prDock->view->hideColumn(5);
	prDock->view->hideColumn(6);
	prDock->view->hideColumn(7);
	prDock->view->hideColumn(8);
	prDock->view->hideColumn(9);
	//prDock->view->hideColumn(10);
	prDock->hide();

	profileBar = new QToolBar(this);
	profileCombo = new QComboBox(profileBar);
	profileBar->addWidget(new QLabel("Profile:   ", profileBar));
	profileBar->addWidget(profileCombo);
	profileCombo->setModel(profileModel);
	modCombo = new QComboBox(profileBar);
	modCombo->addItem(QString::fromLatin1("µm"), Qt::DisplayRole);
	modCombo->addItem("mm", Qt::DisplayRole);
	modCombo->addItem("cm", Qt::DisplayRole);
	modCombo->addItem("m", Qt::DisplayRole);
	profileBar->addSeparator();
	profileBar->addWidget(new QLabel("Unit:	  ", profileBar));
	profileBar->addWidget(modCombo);
	addToolBar(Qt::TopToolBarArea, profileBar);
	profileBar->hide();

	//Scale:
	scaleDock = new ScaleDock(this);
	addDockWidget(Qt::RightDockWidgetArea, scaleDock);
	scaleDock->hide();
}

void ImageRaster::connectSignals() {
	connect(zoomInAct, &QAction::triggered, this, &ImageRaster::zoomIn);
	connect(zoomOutAct, &QAction::triggered, this, &ImageRaster::zoomOut);
	connect(zoomToViewAct, &QAction::triggered, this, &ImageRaster::zoomToView);
	connect(zoomToActualAct, &QAction::triggered, this, &ImageRaster::zoomToActual);

	connect(saveImageAct, &QAction::triggered, this, &ImageRaster::saveImage);

	connect(modeToolbar, &nModeToolbar::ModeChanged, scene, &RasterScene::stateInterface);
	connect(modeToolbar, &nModeToolbar::RulerChanged, scene, &RasterScene::rulerInterface);
	connect(modeToolbar, &nModeToolbar::MarkerChanged, scene, &RasterScene::markerInterface);
	connect(modeToolbar, &nModeToolbar::ModeChanged, this, &ImageRaster::sceneModeChanged);

	connect(markerDock->view->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)),
		mapMarker, SLOT(setCurrentModelIndex(QModelIndex)));

	connect(markerDock->add, &QPushButton::clicked, this, &ImageRaster::appendMarker);
	connect(markerDock->rem, &QPushButton::clicked, this, &ImageRaster::delMarker);

	connect(scene->manager, &StateManager::addMarker, this, &ImageRaster::addMarker);
	connect(undoAct, &QAction::triggered, this, &ImageRaster::updateMarker);
	connect(redoAct, &QAction::triggered, this, &ImageRaster::updateMarker);
	connect(markerDock->apply, &QPushButton::clicked, mapMarker, &QDataWidgetMapper::submit);
	connect(markerDock->apply, &QPushButton::clicked, this, &ImageRaster::refreshIndicator);
	connect(markerModel, &MarkerModel::labelChg, this, &ImageRaster::labelChg);
	connect(markerModel, &MarkerModel::color1Chg, this, &ImageRaster::color1Chg);
	connect(markerModel, &MarkerModel::color2Chg, this, &ImageRaster::color2Chg);
	connect(markerModel, &MarkerModel::visibility, this, &ImageRaster::visibility);
	connect(markerModel, &MarkerModel::fontChg, this, &ImageRaster::fontChg);
	connect(markerModel, &MarkerModel::fontSizeChg, this, &ImageRaster::fontSizeChg);
	connect(markerModel, &MarkerModel::widthChg, this, &ImageRaster::widthChg);

	connect(profileForm->ui->view->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), 
		mapProfile, SLOT(setCurrentModelIndex(QModelIndex)));
	connect(profileCombo, SIGNAL(currentIndexChanged(int)),
		mapProfile, SLOT(setCurrentIndex(int)));
	connect(profileCombo, SIGNAL(currentIndexChanged(int)),
		this, SLOT(updateRulers()));
	connect(modCombo, SIGNAL(currentIndexChanged(int)),
		this, SLOT(updateModifier(int)));
	modCombo->setCurrentIndex(0);
	connect(profileForm->ui->add, &QPushButton::clicked, this, &ImageRaster::appendProfile);
	connect(profileForm->ui->remove, &QPushButton::clicked, this, &ImageRaster::removeProfile);
	connect(profileForm->ui->calibrate, &QPushButton::clicked, this, &ImageRaster::calibrateProfile);

	connect(scene->manager, &StateManager::sendCalibration, this, &ImageRaster::receiveCalibration);

	connect(lrDock->view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
		mapLR, SLOT(setCurrentModelIndex(QModelIndex)));
	connect(scene->manager, &StateManager::addLR, this, &ImageRaster::addLR);
	connect(lrModel, &RulerModel::color1Chg, this, &ImageRaster::rColor1Chg);
	connect(lrModel, &RulerModel::color2Chg, this, &ImageRaster::rColor2Chg);
	connect(lrModel, &RulerModel::fontChg, this, &ImageRaster::rFontChg);
	connect(lrModel, &RulerModel::fontSizeChg, this, &ImageRaster::rFontSizeChg);
	connect(lrModel, &RulerModel::penWidthChg, this, &ImageRaster::rWidthChg);
	connect(lrDock->default_, &QPushButton::clicked, this, &ImageRaster::defaultText);

	connect(rrDock->view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
		mapRR, SLOT(setCurrentModelIndex(QModelIndex)));
	connect(scene->manager, &StateManager::addRR, this, &ImageRaster::addRR);
	connect(rrModel, &RulerModel::color1Chg, this, &ImageRaster::rColor1Chg);
	connect(rrModel, &RulerModel::color2Chg, this, &ImageRaster::rColor2Chg);
	connect(rrModel, &RulerModel::fontChg, this, &ImageRaster::rFontChg);
	connect(rrModel, &RulerModel::fontSizeChg, this, &ImageRaster::rFontSizeChg);
	connect(rrModel, &RulerModel::penWidthChg, this, &ImageRaster::rWidthChg);
	connect(rrDock->default_, &QPushButton::clicked, this, &ImageRaster::defaultText);

	connect(crDock->view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
		mapCR, SLOT(setCurrentModelIndex(QModelIndex)));
	connect(scene->manager, &StateManager::addCR, this, &ImageRaster::addCR);
	connect(crModel, &RulerModel::color1Chg, this, &ImageRaster::rColor1Chg);
	connect(crModel, &RulerModel::color2Chg, this, &ImageRaster::rColor2Chg);
	connect(crModel, &RulerModel::fontChg, this, &ImageRaster::rFontChg);
	connect(crModel, &RulerModel::fontSizeChg, this, &ImageRaster::rFontSizeChg);
	connect(crModel, &RulerModel::penWidthChg, this, &ImageRaster::rWidthChg);
	connect(crDock->default_, &QPushButton::clicked, this, &ImageRaster::defaultText);

	connect(tcDock->view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
		mapTC, SLOT(setCurrentModelIndex(QModelIndex)));
	connect(scene->manager, &StateManager::addTC, this, &ImageRaster::addTC);
	connect(tcModel, &RulerModel::color1Chg, this, &ImageRaster::rColor1Chg);
	connect(tcModel, &RulerModel::color2Chg, this, &ImageRaster::rColor2Chg);
	connect(tcModel, &RulerModel::fontChg, this, &ImageRaster::rFontChg);
	connect(tcModel, &RulerModel::fontSizeChg, this, &ImageRaster::rFontSizeChg);
	connect(tcModel, &RulerModel::penWidthChg, this, &ImageRaster::rWidthChg);
	connect(tcDock->default_, &QPushButton::clicked, this, &ImageRaster::defaultText);

	connect(prDock->view->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
		mapPR, SLOT(setCurrentModelIndex(QModelIndex)));
	connect(scene->manager, &StateManager::addPR, this, &ImageRaster::addPR);
	connect(prModel, &RulerModel::color1Chg, this, &ImageRaster::rColor1Chg);
	connect(prModel, &RulerModel::color2Chg, this, &ImageRaster::rColor2Chg);
	connect(prModel, &RulerModel::fontChg, this, &ImageRaster::rFontChg);
	connect(prModel, &RulerModel::fontSizeChg, this, &ImageRaster::rFontSizeChg);
	connect(prModel, &RulerModel::penWidthChg, this, &ImageRaster::rWidthChg);
	connect(prDock->default_, &QPushButton::clicked, this, &ImageRaster::defaultText);

	connect(scaleDock, &ScaleDock::checked_changed, this, &ImageRaster::addScale);
	connect(scaleDock->rem, &QPushButton::clicked, this, &ImageRaster::hideScale);
}

void ImageRaster::loadSettings() {
	mySettings = new GlobalSettings();
	QSettings settings("Miconos", "ImageRaster");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());
}

void ImageRaster::openImage() {
	QFileDialog openFileDg(this);
	openFileDg.setFileMode(QFileDialog::ExistingFile);
	openFileDg.setNameFilter("Portable Network Graphics File (*.png);;JPEG File-Format (*.jpg);;Bitmap File (*.bmp)");
	//openFileDg.setDirectory(QDir::home());
	openFileDg.setViewMode(QFileDialog::Detail);
	QString imgName;
	if (openFileDg.exec())
		imgName = openFileDg.selectedFiles().at(0);
    if (imgName != "") {
        if (hasImage) {
            ImageRaster *other = new ImageRaster;
            other->show();
            other->initScene(imgName);
        }
        else {
            initScene(imgName);
        }
    }
}

void ImageRaster::initScene(const QString& imgName) {
	QPixmap pix(imgName);
	originalSize = QSizeF(pix.width(), pix.height());

	QGraphicsPixmapItem* pix_item = new QGraphicsPixmapItem(pix);
	pix_item->setAcceptHoverEvents(true);
	scene->addItem(pix_item);
	scene->setSceneRect(pix.rect());

	ui.graphicsView->setScene(scene);
	ui.graphicsView->show();
	modeToolbar->setEnabled(true);

	zoom = 1.0;
	hasImage = true;
	saveImageAct->setEnabled(true);
	setWindowTitle("Image Raster - " + imgName);
	zoomIndicator->setText(QString().number(zoom*100)+"%");
	image = imgName;

	connectSignals();
	scene->stateInterface(AppState::Select);
}

void ImageRaster::saveImage() {
	QFileDialog saveDg(this);
	saveDg.setAcceptMode(QFileDialog::AcceptSave);
	saveDg.setFileMode(QFileDialog::AnyFile);
	//saveDg.setDirectory(QDir::home());
	saveDg.setNameFilter("Portable Network Graphics File (*.png);;JPEG File-Format (*.jpg);;Bitmap File (*.bmp)");
	saveDg.setOption(QFileDialog::DontUseNativeDialog);
	QString imgName;
	//QString imgName = QFileDialog::getSaveFileName(this, "Save Edited Image",
	//	QDir::homePath(), "Images (*.png *.jpg *.bmp *.gif)");
	if (saveDg.exec())
		imgName = saveDg.selectedFiles().at(0);
	if (image == imgName) {
		if (1 == QMessageBox::warning(this, "Overwrite Original Image", 
			"Will overwrite your original image. Continue?", QMessageBox::Ok, QMessageBox::Cancel))
			return;
	}
	scene->clearSelection();
	QImage img(scene->width(), scene->height(), QImage::Format_ARGB32);
	img.fill(Qt::transparent);
	QPainter painter(&img);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	scene->render(&painter);
	img.save(imgName);
}

void ImageRaster::deleteItem() {
}

void ImageRaster::zoomIn() {
	if (zoom >= 16.0)
        return;
    if (zoom < 1.0)
        zoom += 0.05;
    else if (zoom >= 1.0 && zoom < 3.0)
        zoom += .25;
    else if (zoom >= 3.0)
        zoom += .5;

    ui.graphicsView->setTransform(QTransform::fromScale(zoom, zoom), false);
	zoomIndicator->setText(QString().number(zoom*100)+"%");
}

void ImageRaster::zoomOut() {
	if (zoom <= .1)
        return;
    if (zoom <= 1.0)
        zoom -= 0.05;
    else if (zoom > 1.0 && zoom <= 3.0)
        zoom -= .25;
    else if (zoom > 3.0)
        zoom -= .5;

    ui.graphicsView->setTransform(QTransform::fromScale(zoom, zoom), false);
	zoomIndicator->setText(QString().number(zoom*100)+"%");
}

void ImageRaster::zoomToView() {
	if ((0.9*this->width()/originalSize.width()) >= 1) {
        zoom = 1.0;
		if (zoom*originalSize.height() > (.9*this->height())) {
			int z = qRound((.9*this->height()/originalSize.height())*10);
            zoom = 1.0*z/10;
        }
    }
    else {
		int z = qRound((0.9*this->width()/originalSize.width())*10);
        zoom = 1.0*z/10;
        if (zoom*originalSize.height() > (.9*this->height())) {
            int z = qRound((.9*this->height()/originalSize.height())*10);
            zoom = 1.0*z/10;
        }
    }
    ui.graphicsView->setTransform(QTransform::fromScale(zoom, zoom), false);
	zoomIndicator->setText(QString().number(zoom*100)+"%");
}

void ImageRaster::zoomToActual() {
	zoom = 1.0;
	ui.graphicsView->setTransform(QTransform::fromScale(zoom, zoom), false);
	zoomIndicator->setText(QString().number(zoom*100)+"%");
}

void ImageRaster::sceneModeChanged(AppState state) {
	markerDock->hide();
	profileDock->hide();
	lrDock->hide();
	rrDock->hide();
	crDock->hide();
	tcDock->hide();
	prDock->hide();
	profileBar->hide();
	if (AppState::Marker == state) {
		markerDock->show();
	}
	else if (AppState::Calibration == state) {
		profileDock->show();
	}
	else if (AppState::Ruler == state) {
		profileBar->show();
		if (RulerState::Line == modeToolbar->rState)
			lrDock->show();
		else if (RulerState::Rectangle == modeToolbar->rState)
			rrDock->show();
		else if (RulerState::Circle == modeToolbar->rState)
			crDock->show();
		else if (RulerState::Circle2 == modeToolbar->rState)
			tcDock->show();
		else if (RulerState::Polygon == modeToolbar->rState)
			prDock->show();
	}
}

void ImageRaster::firstMarker() {
	mapMarker->toFirst();
	refreshIndicator();
}

void ImageRaster::prevMarker() {
	mapMarker->toPrevious();
	refreshIndicator();
}

void ImageRaster::nextMarker() {
	mapMarker->toNext();
	refreshIndicator();
}

void ImageRaster::lastMarker() {
	mapMarker->toLast();
	refreshIndicator();
}

void ImageRaster::appendMarker() {
	AddMarker *cmd = new AddMarker(markerModel, this);
	undoStack->push(cmd);
	refreshIndicator();
}

void ImageRaster::delMarker() {
	RemoveMarker *cmd = new RemoveMarker(markerModel, mapMarker->currentIndex(), this);
	undoStack->push(cmd);
	refreshIndicator();
	//QMessageBox::StandardButton res =
	//	QMessageBox::warning(this, "Remove Markers", 
	//	QString("Delete Marker %0 %1. Are you sure?").arg(mapMarker->currentIndex()+1).arg(markerModel->at(mapMarker->currentIndex())->label()));
	//if (QMessageBox::Ok == res) {
	//	markerModel->removeRow(mapMarker->currentIndex());
	//}
}

void ImageRaster::setMarker() {
	markerIndex = mapMarker->currentIndex();
	refreshIndicator();
}

void ImageRaster::addMarker(Marker* p) {
	MarkerBranch* b = markerModel->at(mapMarker->currentIndex());
	QFont f = b->font();
	f.setPixelSize(b->fontSize());
	p->setFont(f);
	QPen base = QPen(b->color1());
	base.setWidth(b->width());
	p->setPen1(base);
	p->setPen2(QPen(b->color2()));
	p->setLabel(b->label());
	AddItem *cmd = new AddItem(p, scene, b);
	undoStack->push(cmd);
	updateMarker();
}

void ImageRaster::updateMarker() {
	markerModel->updateWidgets();
	refreshIndicator();
}

void ImageRaster::refreshIndicator() {
	markerDock->position->setText(QString("%1/%2").arg(mapMarker->currentIndex()+1).arg(markerModel->rowCount()));
	if (mapMarker->currentIndex() >= 0 && mapMarker->currentIndex() < markerModel->rowCount())
		markerDock->active->setText(QString("Current Marker: %1 %2").arg(mapMarker->currentIndex()+1).arg(
		"("+markerModel->at(mapMarker->currentIndex())->label()+")"));
	else
		markerDock->active->setText("No marker profile selected");
}

void ImageRaster::chgVisibility(MarkerBranch* cont, bool v) {
	for (auto p : cont->leafItems()) {
		if (auto item = (ArrowMarker*)p) {
			if (v) scene->addItem(item);
			else scene->removeItem(item);
		}
	}
}

void ImageRaster::labelChg(MarkerBranch* b, QString old, QString n) {
	if (old == n) return;
	LabelChg *cmd = new LabelChg(b, old, n);
	undoStack->push(cmd);
}

void ImageRaster::color1Chg(MarkerBranch* b, QColor old, QColor n) {
	if (old == n) return;
	Color1Chg* cmd = new Color1Chg(b, old, n);
	undoStack->push(cmd);
}

void ImageRaster::color2Chg(MarkerBranch* b, QColor old, QColor n) {
	if (old == n) return;
	Color2Chg* cmd = new Color2Chg(b, old, n);
	undoStack->push(cmd);
}

void ImageRaster::visibility(MarkerBranch* b, bool v) {
	Visibility* cmd = new Visibility(b, v, this);
	undoStack->push(cmd);
}

void ImageRaster::fontChg(MarkerBranch* b, QFont old, QFont n) {
	if (old == n) return;
	FontChg* cmd = new FontChg(b, old, n);
	undoStack->push(cmd);
}

void ImageRaster::fontSizeChg(MarkerBranch* b, int old, int n) {
	if (old == n) return;
	FontSizeChg* cmd = new FontSizeChg(b, old, n);
	undoStack->push(cmd);
}

void ImageRaster::widthChg(MarkerBranch* b, int old, int n) {
	if (old == n) return;
	WidthChg* cmd = new WidthChg(b, old, n);
	undoStack->push(cmd);
}

void ImageRaster::appendProfile() {
	CalibrationProfile prof;
	prof.setName("empty");
	profileModel->insertProfile(profileModel->rowCount(), prof);
}

void ImageRaster::removeProfile() {
	if (QMessageBox::warning(this, tr("Delete Profile"), tr("Are you sure? This action is not undoable."),
		QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
		profileModel->removeRow(mapProfile->currentIndex());
}

void ImageRaster::calibrateProfile() {
	profileDock->setEnabled(false);
	modeToolbar->setEnabled(false);
	ui.mainToolBar->setEnabled(false);
	ui.menuBar->setEnabled(false);
	cStatus = X;
	scene->manager->sequence = StateManager::Start;
}

void ImageRaster::receiveCalibration(int pixel) {
	bool ok;
	if (X == cStatus) {
		int x = QInputDialog::getInt(this, tr("Input Length"), tr("Length") + QString::fromLatin1(" (µm)"), 0,
			1, 999999, 10, &ok);
		if (ok) {
			int modifierX = (1.0*originalSize.width()/pixel) * x;
			tmpX = modifierX;
			cStatus = Y;
		}
		else
			endCalibration();
	}
	else if (Y == cStatus) {
		int y = QInputDialog::getInt(this, tr("Input Length"), tr("Length") + QString::fromLatin1(" (µm)"), 0,
			1, 999999, 10, &ok);
		if (ok) {
			int modifierY = (1.0*originalSize.height()/pixel) * y;
			profileModel->setData(profileModel->index(mapProfile->currentIndex(), 1), tmpX);
			profileModel->setData(profileModel->index(mapProfile->currentIndex(), 2), modifierY);
			endCalibration();
		}
		else
			endCalibration();
	}
}

void ImageRaster::endCalibration() {
	profileDock->setEnabled(true);
	modeToolbar->setEnabled(true);
	ui.mainToolBar->setEnabled(true);
	ui.menuBar->setEnabled(true);
	cStatus = Idle;
	scene->manager->sequence = StateManager::Idle;
}

void ImageRaster::closeEvent(QCloseEvent *event) {
	mySettings->WriteSettings(profileModel->getData());
	QSettings settings("Miconos", "ImageRaster");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());
	event->accept();
	QMainWindow::closeEvent(event);
}

void ImageRaster::sceneAddItem(QGraphicsItem* item) {
	scene->addItem(item);
}

void ImageRaster::sceneRemoveItem(QGraphicsItem* item) {
	scene->removeItem(item);
}

void ImageRaster::addLR(LineRuler* r) {
	//Apply Format:
	QPen pen1 = QPen(lrModel->color1());
	pen1.setWidth(lrModel->penWidth());
	QPen pen2 = QPen(lrModel->color2());
	QFont f = lrModel->font();
	f.setPixelSize(lrModel->fontSize());
	r->setPen1(pen1);
	r->setPen2(pen2);
	r->setFont(f);
	//Register to model via QUndoCommand:
	AddLineRuler* add = new AddLineRuler(r, lrModel, this);
	undoStack->push(add);
	mapLR->toLast();
}

void ImageRaster::updateLR() {
	int modifierX = profileModel->at(mapProfile->currentIndex()).x();
	int modifierY = profileModel->at(mapProfile->currentIndex()).y();
	for (int i=0; i<lrModel->rowCount(); ++i) {
		if (auto b = (LineRuler*)lrModel->at(i)) {
			QLineF line = b->line();
			double r_length = sqrt(pow(line.dx()*modifierX, 2)+pow(line.dy()*modifierY, 2));
			if (b->length() == r_length && b->mod() == modifier)
				continue;
			b->setMod(modifier);
			lrModel->setData(lrModel->index(i, 0), r_length);
			lrModel->setData(lrModel->index(i, 10), b->defaultText());
		}
	}
}

void ImageRaster::addRR(RectRuler* r) {
	//Apply Format:
	QPen pen1 = QPen(rrModel->color1());
	pen1.setWidth(rrModel->penWidth());
	QPen pen2 = QPen(rrModel->color2());
	QFont f = rrModel->font();
	f.setPixelSize(rrModel->fontSize());
	r->setPen1(pen1);
	r->setPen2(pen2);
	r->setFont(f);
	//Register to model via QUndoCommand:
	AddRectRuler* add = new AddRectRuler(r, rrModel, this);
	undoStack->push(add);
	mapRR->toLast();
}

void ImageRaster::updateRR() {
	int modifierX = profileModel->at(mapProfile->currentIndex()).x();
	int modifierY = profileModel->at(mapProfile->currentIndex()).y();
	for (int i=0; i<rrModel->rowCount(); ++i) {
		if (auto b = (RectRuler*)rrModel->at(i)) {
			QRectF r = b->rect();
			double r_width = 1.0 * r.width() * modifierX;
			double r_height = 1.0 * r.height() * modifierY;
			if (b->width() == r_width && b->height() == r_height && b->mod() == modifier)
				continue;
			b->setMod(modifier);
			rrModel->setData(rrModel->index(i, 1), r_width);
			rrModel->setData(rrModel->index(i, 2), r_height);
			rrModel->setData(rrModel->index(i, 10), b->defaultText());
		}
	}
}

void ImageRaster::addCR(const QRectF& r) {
	//Recalculate circle using calibration data:
	int modifierX = profileModel->at(mapProfile->currentIndex()).x();
	int modifierY = profileModel->at(mapProfile->currentIndex()).y();
	QPointF center = r.topLeft() + QPointF(r.width()/2, r.height()/2);
	double radius = r.width()/2;
	double r1 = radius * modifierX;
	double r2 = radius * modifierY;
	QPointF TL = QPointF(center.x()-r1, center.y()-r2);
	QRectF circle = QRectF(TL, QSizeF(r1, r2));
	CircleRuler* ruler = new CircleRuler(circle);
	scene->addItem(ruler);
	ruler->setRadius(radius);

	//Apply Format:
	QPen pen1 = QPen(crModel->color1());
	pen1.setWidth(crModel->penWidth());
	QPen pen2 = QPen(crModel->color2());
	QFont f = crModel->font();
	f.setPixelSize(crModel->fontSize());
	ruler->setPen1(pen1);
	ruler->setPen2(pen2);
	ruler->setFont(f);
	//Register to model via QUndoCommand:
	AddCircleRuler* add = new AddCircleRuler(ruler, crModel, this);
	undoStack->push(add);
	mapCR->toLast();
}

void ImageRaster::updateCR() {
	int modifierX = profileModel->at(mapProfile->currentIndex()).x();
	int modifierY = profileModel->at(mapProfile->currentIndex()).y();
	for (int i=0; i<crModel->rowCount(); ++i) {
		if (auto b = (CircleRuler*)crModel->at(i)) {
			QRectF r = b->rect();
			double r_radius = b->radius();
			if (b->radius() == r_radius && b->mod() == modifier)
				continue;
			b->setMod(modifier);
			crModel->setData(crModel->index(i, 3), r_radius);
			crModel->setData(crModel->index(i, 10), b->defaultText());
		}
	}
}

void ImageRaster::addTC(Circle2Ruler* r) {
	//Apply Format:
	QPen pen1 = QPen(tcModel->color1());
	pen1.setWidth(tcModel->penWidth());
	QPen pen2 = QPen(tcModel->color2());
	QFont f = tcModel->font();
	f.setPixelSize(tcModel->fontSize());
	r->setPen1(pen1);
	r->setPen2(pen2);
	r->setFont(f);
	//Register to model via QUndoCommand:
	AddCircle2Ruler* add = new AddCircle2Ruler(r, tcModel, this);
	undoStack->push(add);
	mapTC->toLast();
}

void ImageRaster::updateTC() {
	int modifierX = profileModel->at(mapProfile->currentIndex()).x();
	int modifierY = profileModel->at(mapProfile->currentIndex()).y();
	for (int i=0; i<tcModel->rowCount(); ++i) {
		if (auto b = (Circle2Ruler*)tcModel->at(i)) {
			QLineF line = b->line();
			double r_length = sqrt(pow(line.dx()*modifierX, 2)+pow(line.dy()*modifierY, 2));
			if (b->length() == r_length && b->mod() == modifier)
				continue;
			b->setMod(modifier);
			tcModel->setData(tcModel->index(i, 0), r_length);
			tcModel->setData(tcModel->index(i, 10), b->defaultText());
		}
	}
}

void ImageRaster::addPR(PolyRuler* r) {
	//Apply Format:
	QPen pen1 = QPen(prModel->color1());
	pen1.setWidth(prModel->penWidth());
	QPen pen2 = QPen(prModel->color2());
	QFont f = prModel->font();
	f.setPixelSize(prModel->fontSize());
	r->setPen1(pen1);
	r->setPen2(pen2);
	r->setFont(f);
	//Register to model via QUndoCommand:
	AddPolyRuler* add = new AddPolyRuler(r, prModel, this);
	undoStack->push(add);
	mapPR->toLast();
}

void ImageRaster::updatePR() {
	int modifierX = profileModel->at(mapProfile->currentIndex()).x();
	int modifierY = profileModel->at(mapProfile->currentIndex()).y();
	for (int index=0; index<prModel->rowCount(); ++index) {
		if (auto b = (PolyRuler*)prModel->at(index)) {
			QPolygonF poly = b->rect();
			QGraphicsPolygonItem* p = new QGraphicsPolygonItem(poly);
			QRectF r = p->boundingRect();
			QImage img(r.width(), r.height(), QImage::Format_Mono);
			img.fill(Qt::white);
			QPainter paint(&img);
			paint.setBrush(Qt::black);
			QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem;
			p->paint(&paint, option);

			//Count black pixel:
			int count = 0;
			for (int i=0; i<img.width(); ++i) {
				for (int j=0; j<img.height(); ++j) {
					if (img.pixel(i, j) == qRgb(0, 0, 0)) {
						++count;
					}
				}
			}
			double r_area = 1.0 * count * (modifierX * modifierY);
			delete p;
			delete option;

			//Calculate length:
			QPointF last;
			double r_length = 0.0;
			for (auto point : poly) {
				if (point == *poly.begin()) {
					last = point;
					continue;
				}
				QLineF line = QLineF(last, point);
				r_length += sqrt(pow(line.dx()*modifierX, 2)+pow(line.dy()*modifierY, 2));
				last = point;
			}

			if (b->area() == r_area && b->length() == r_length && b->mod() == modifier)
				continue;
			b->setMod(modifier);
			prModel->setData(prModel->index(index, 0), r_length);
			prModel->setData(prModel->index(index, 4), r_area);
			prModel->setData(prModel->index(index, 10), b->defaultText());
		}
	}
}

void ImageRaster::rColor1Chg(QColor old, QColor n) {
	if (old == n) return;
	RulerModel* model = (RulerModel*)sender();
	RColor1Chg* cmd = new RColor1Chg(model, old, n);
	undoStack->push(cmd);
}

void ImageRaster::rColor2Chg(QColor old, QColor n) {
	if (old == n) return;
	RulerModel* model = (RulerModel*)sender();
	RColor2Chg* cmd = new RColor2Chg(model, old, n);
	undoStack->push(cmd);
}

void ImageRaster::rFontChg(QFont old, QFont n) {
	if (old == n) return;
	RulerModel* model = (RulerModel*)sender();
	RFontChg* cmd = new RFontChg(model, old, n);
	undoStack->push(cmd);
}

void ImageRaster::rFontSizeChg(int old, int n) {
	if (old == n) return;
	RulerModel* model = (RulerModel*)sender();
	RFontSizeChg* cmd = new RFontSizeChg(model, old, n);
	undoStack->push(cmd);
}

void ImageRaster::rWidthChg(int old, int n) {
	if (old == n) return;
	RulerModel* model = (RulerModel*)sender();
	RWidthChg* cmd = new RWidthChg(model, old, n);
	undoStack->push(cmd);
}

void ImageRaster::defaultText() {
	if (RulerState::Line == modeToolbar->rState) {
		LineRuler* lr = lrModel->at(mapLR->currentIndex());
		lrModel->setData(lrModel->index(mapLR->currentIndex(), 10), lr->defaultText());
	}
	else if (RulerState::Rectangle == modeToolbar->rState) {
		RectRuler* rr = (RectRuler*)rrModel->at(mapRR->currentIndex());
		rrModel->setData(rrModel->index(mapRR->currentIndex(), 10), rr->defaultText());
	}
	else if (RulerState::Circle == modeToolbar->rState) {
		CircleRuler* lr = (CircleRuler*)lrModel->at(mapLR->currentIndex());
		crModel->setData(lrModel->index(mapCR->currentIndex(), 10), lr->defaultText());
	}
	else if (RulerState::Circle2 == modeToolbar->rState) {
		Circle2Ruler* lr = (Circle2Ruler*)lrModel->at(mapLR->currentIndex());
		tcModel->setData(lrModel->index(mapTC->currentIndex(), 10), lr->defaultText());
	}
	else if (RulerState::Polygon == modeToolbar->rState) {
		PolyRuler* lr = (PolyRuler*)lrModel->at(mapLR->currentIndex());
		prModel->setData(lrModel->index(mapPR->currentIndex(), 10), lr->defaultText());
	}
}

void ImageRaster::updateRulers() {
	updateLR();
	updateRR();
	updateCR();
	updateTC();
	updatePR();
}

void ImageRaster::updateModifier(int i) {
	rData::Unit u = (rData::Unit)i;
	if (rData::Unit::Micrometer == u)
		modifier = 1.0;
	else if (rData::Unit::Milimeter == u)
		modifier = 0.001;
	else if (rData::Unit::Centimeter == u)
		modifier = 0.0001;
	else if (rData::Unit::Meter == u)
		modifier = 0.000001;
	updateRulers();
}

void ImageRaster::on_actionScale_triggered() {
	scaleDock->show();
}

void ImageRaster::addScale(int h, int v) {
	//Collect data from scaleDock:
	QString unit;
	double mod;
	rData scale;
	scale.setMod((rData::Unit)scaleDock->unit->currentIndex());

	ScaleType type = (ScaleType)scaleDock->style_->currentIndex();
	int len = scaleDock->length->currentText().toInt();
	mod = scale.mod();
	unit = scale.unit();

	//Generate line based on s1 and s2:
	double xPixel = len/mod / profileModel->at(mapProfile->currentIndex()).x();
	double yPixel = len/mod / profileModel->at(mapProfile->currentIndex()).y();

	double wa = 0.1*scene->width();
	double wm = 0.5*scene->width();
	double wb = 0.9*scene->width();
	double ha = 0.1*scene->height();
	double hm = 0.5*scene->height();
	double hb = 0.9*scene->height();

	QLineF hTL = QLineF(QPointF(wa, ha), QPointF(wa+xPixel, ha));
	QLineF hBL = QLineF(QPointF(wa, hb), QPointF(wa+xPixel, hb));
	QLineF hT  = QLineF(QPointF(wm-0.5*xPixel, ha), QPointF(wm+0.5*xPixel, ha));
	QLineF hC  = QLineF(QPointF(wm-0.5*xPixel, hm), QPointF(wm+0.5*xPixel, hm));
	QLineF hB  = QLineF(QPointF(wm-0.5*xPixel, hb), QPointF(wm+0.5*xPixel, hb));
	QLineF hTR = QLineF(QPointF(wb-xPixel, ha), QPointF(wb, ha));
	QLineF hBR = QLineF(QPointF(wb-xPixel, hb), QPointF(wb, hb));
	QLineF hL;	//!!!
	QLineF hR;	//!!!

	QLineF vTL = QLineF(QPointF(wa, ha), QPointF(wa, ha+yPixel));
	QLineF vTR = QLineF(QPointF(wb, ha), QPointF(wb, ha+yPixel));
	QLineF vL  = QLineF(QPointF(wa, hm-0.5*yPixel), QPointF(wa, hm+0.5*yPixel));
	QLineF vC  = QLineF(QPointF(wm, hm-0.5*yPixel), QPointF(wm, hm+0.5*yPixel));
	QLineF vR  = QLineF(QPointF(wb, hm-0.5*yPixel), QPointF(wb, hm+0.5*yPixel));
	QLineF vBL = QLineF(QPointF(wa, hb-yPixel), QPointF(wa, hb));
	QLineF vBR = QLineF(QPointF(wb, hb-yPixel), QPointF(wb, hb));
	QLineF vT; //!!!
	QLineF vB; //!!!

	hideScale();

	//A ***HUGE*** logic tree (I really despise this kind of things):
	if (ScaleType::Bar == type) {
		BarScale* sc, *sv;
		if (0 == h)
			sc = new BarScale(hTL);
		else if (1 == h)
			sc = new BarScale(hT);
		else if (2 == h)
			sc = new BarScale(hTR);
		else if (3 == h)
			sc = new BarScale(hL);
		else if (4 == h) {
			sc = new BarScale(hC);
			sc->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
		}
		else if (5 == h)
			sc = new BarScale(hR);
		else if (6 == h)
			sc = new BarScale(hBL);
		else if (7 == h)
			sc = new BarScale(hB);
		else if (8 == h)
			sc = new BarScale(hBR);
		sc->setText("0", QString().setNum(len) + unit);
		scene->addItem(sc);

		if (0 == v)
			sv = new BarScale(vTL);
		else if (1 == v)
			sv = new BarScale(vT);
		else if (2 == v)
			sv = new BarScale(vTR);
		else if (3 == v)
			sv = new BarScale(vL);
		else if (4 == v) {
			sv = new BarScale(vC);
			sv->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
		}
		else if (5 == v)
			sv = new BarScale(vR);
		else if (6 == v)
			sv = new BarScale(vBL);
		else if (7 == v)
			sv = new BarScale(vB);
		else if (8 == v)
			sv = new BarScale(vBR);
		sv->setText("0", QString().setNum(len) + unit);
		scene->addItem(sv);
	}
	else if (ScaleType::Line == type) {
		RulerScale* sc, *sv;
		if (0 == h)
			sc = new RulerScale(hTL);
		else if (1 == h)
			sc = new RulerScale(hT);
		else if (2 == h)
			sc = new RulerScale(hTR);
		else if (3 == h)
			sc = new RulerScale(hL);
		else if (4 == h) {
			sc = new RulerScale(hC);
			sc->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
		}
		else if (5 == h)
			sc = new RulerScale(hR);
		else if (6 == h)
			sc = new RulerScale(hBL);
		else if (7 == h)
			sc = new RulerScale(hB);
		else if (8 == h)
			sc = new RulerScale(hBR);
		sc->setText("0", QString().setNum(len) + unit);
		scene->addItem(sc);

		if (0 == v)
			sv = new RulerScale(vTL);
		else if (1 == v)
			sv = new RulerScale(vT);
		else if (2 == v)
			sv = new RulerScale(vTR);
		else if (3 == v)
			sv = new RulerScale(vL);
		else if (4 == v) {
			sv = new RulerScale(vC);
			sv->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
		}
		else if (5 == v)
			sv = new RulerScale(vR);
		else if (6 == v)
			sv = new RulerScale(vBL);
		else if (7 == v)
			sv = new RulerScale(vB);
		else if (8 == v)
			sv = new RulerScale(vBR);
		sv->setText("0", QString().setNum(len) + unit);
		scene->addItem(sv);
	}
	else if (ScaleType::Simple == type) {
		SimpleScale* sc, *sv;
		if (0 == h)
			sc = new SimpleScale(hTL);
		else if (1 == h)
			sc = new SimpleScale(hT);
		else if (2 == h)
			sc = new SimpleScale(hTR);
		else if (3 == h)
			sc = new SimpleScale(hL);
		else if (4 == h) {
			sc = new SimpleScale(hC);
			sc->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
		}
		else if (5 == h)
			sc = new SimpleScale(hR);
		else if (6 == h)
			sc = new SimpleScale(hBL);
		else if (7 == h)
			sc = new SimpleScale(hB);
		else if (8 == h)
			sc = new SimpleScale(hBR);
		sc->setText("0", QString().setNum(len) + unit);
		scene->addItem(sc);

		if (0 == v)
			sv = new SimpleScale(vTL);
		else if (1 == v)
			sv = new SimpleScale(vT);
		else if (2 == v)
			sv = new SimpleScale(vTR);
		else if (3 == v)
			sv = new SimpleScale(vL);
		else if (4 == v) {
			sv = new SimpleScale(vC);
			sv->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
		}
		else if (5 == v)
			sv = new SimpleScale(vR);
		else if (6 == v)
			sv = new SimpleScale(vBL);
		else if (7 == v)
			sv = new SimpleScale(vB);
		else if (8 == v)
			sv = new SimpleScale(vBR);
		sv->setText("0", QString().setNum(len) + unit);
		scene->addItem(sv);
	}
}

void ImageRaster::hideScale() {
	//Delete previous (if any) scale item:
	QList<QGraphicsItem*> items;
	for (auto p : scene->items()) {
		if (BarScale::Type == p->type() || RulerScale::Type == p->type() || SimpleScale::Type == p->type()) {
			items.append(p);
		}
	}
	for (auto p : items)
		delete p;
}

void ImageRaster::on_actionLegend_triggered() {
	//Delete existing legend (if exist):
	QList<QGraphicsItem*> l;
	for (auto i : scene->items()) {
		if (LegendItem::Type == i->type())
			l.append(i);
	}
	for (auto i : l)
		delete i;
	QPointF origin = QPointF(0.1*scene->width(), 0.1*scene->height());
	LegendItem* legend = new LegendItem(markerModel, origin);
	scene->addItem(legend);
}