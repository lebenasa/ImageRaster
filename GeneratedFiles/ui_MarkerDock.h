/********************************************************************************
** Form generated from reading UI file 'MarkerDock.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKERDOCK_H
#define UI_MARKERDOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "coloreditor.h"

QT_BEGIN_NAMESPACE

class Ui_MarkerDock
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QFormLayout *formLayout;
    QLabel *label1;
    QLineEdit *label;
    QLabel *label_2;
    QLineEdit *count;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox;
    QWidget *tabWidgetPage2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    ColorEditor *color1;
    QLabel *label_5;
    ColorEditor *color2;
    QLabel *label_6;
    QSpinBox *weight;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_7;
    QFontComboBox *font_;
    QLabel *label_8;
    QSpinBox *fontSize;
    QPushButton *apply;
    QSpacerItem *verticalSpacer_3;
    QTableView *view;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *active;
    QPushButton *add;
    QPushButton *rem;
    QLabel *position;

    void setupUi(QDockWidget *MarkerDock)
    {
        if (MarkerDock->objectName().isEmpty())
            MarkerDock->setObjectName(QStringLiteral("MarkerDock"));
        MarkerDock->resize(223, 453);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(dockWidgetContents);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(200, 0));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QStringLiteral("tabWidgetPage1"));
        formLayout = new QFormLayout(tabWidgetPage1);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label1 = new QLabel(tabWidgetPage1);
        label1->setObjectName(QStringLiteral("label1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label1);

        label = new QLineEdit(tabWidgetPage1);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label);

        label_2 = new QLabel(tabWidgetPage1);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        count = new QLineEdit(tabWidgetPage1);
        count->setObjectName(QStringLiteral("count"));
        count->setEnabled(true);
        count->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, count);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::LabelRole, verticalSpacer);

        checkBox = new QCheckBox(tabWidgetPage1);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, checkBox);

        tabWidget->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName(QStringLiteral("tabWidgetPage2"));
        gridLayout_2 = new QGridLayout(tabWidgetPage2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(tabWidgetPage2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        color1 = new ColorEditor(tabWidgetPage2);
        color1->setObjectName(QStringLiteral("color1"));

        gridLayout_2->addWidget(color1, 0, 1, 1, 1);

        label_5 = new QLabel(tabWidgetPage2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        color2 = new ColorEditor(tabWidgetPage2);
        color2->setObjectName(QStringLiteral("color2"));

        gridLayout_2->addWidget(color2, 1, 1, 1, 1);

        label_6 = new QLabel(tabWidgetPage2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        weight = new QSpinBox(tabWidgetPage2);
        weight->setObjectName(QStringLiteral("weight"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(weight->sizePolicy().hasHeightForWidth());
        weight->setSizePolicy(sizePolicy1);
        weight->setMinimum(1);

        gridLayout_2->addWidget(weight, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout_2->addItem(verticalSpacer_2, 3, 0, 1, 1);

        label_7 = new QLabel(tabWidgetPage2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(20, 20));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/Resources/Font.png")));
        label_7->setScaledContents(true);
        label_7->setWordWrap(false);

        gridLayout_2->addWidget(label_7, 4, 0, 1, 1);

        font_ = new QFontComboBox(tabWidgetPage2);
        font_->setObjectName(QStringLiteral("font_"));

        gridLayout_2->addWidget(font_, 4, 1, 1, 1);

        label_8 = new QLabel(tabWidgetPage2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setScaledContents(true);

        gridLayout_2->addWidget(label_8, 5, 0, 1, 1);

        fontSize = new QSpinBox(tabWidgetPage2);
        fontSize->setObjectName(QStringLiteral("fontSize"));
        sizePolicy1.setHeightForWidth(fontSize->sizePolicy().hasHeightForWidth());
        fontSize->setSizePolicy(sizePolicy1);
        fontSize->setMinimum(6);

        gridLayout_2->addWidget(fontSize, 5, 1, 1, 1);

        tabWidget->addTab(tabWidgetPage2, QString());

        verticalLayout->addWidget(tabWidget);

        apply = new QPushButton(dockWidgetContents);
        apply->setObjectName(QStringLiteral("apply"));

        verticalLayout->addWidget(apply);

        verticalSpacer_3 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_3);

        view = new QTableView(dockWidgetContents);
        view->setObjectName(QStringLiteral("view"));

        verticalLayout->addWidget(view);

        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(200, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(4);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        active = new QLabel(frame);
        active->setObjectName(QStringLiteral("active"));

        gridLayout->addWidget(active, 0, 0, 1, 3);

        add = new QPushButton(frame);
        add->setObjectName(QStringLiteral("add"));
        sizePolicy1.setHeightForWidth(add->sizePolicy().hasHeightForWidth());
        add->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(add, 2, 0, 1, 2);

        rem = new QPushButton(frame);
        rem->setObjectName(QStringLiteral("rem"));
        sizePolicy1.setHeightForWidth(rem->sizePolicy().hasHeightForWidth());
        rem->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(rem, 2, 2, 1, 2);

        position = new QLabel(frame);
        position->setObjectName(QStringLiteral("position"));
        position->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(position, 0, 3, 1, 1);


        verticalLayout->addWidget(frame);

        MarkerDock->setWidget(dockWidgetContents);

        retranslateUi(MarkerDock);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MarkerDock);
    } // setupUi

    void retranslateUi(QDockWidget *MarkerDock)
    {
        MarkerDock->setWindowTitle(QApplication::translate("MarkerDock", "Marker Data", 0));
        label1->setText(QApplication::translate("MarkerDock", "Label", 0));
        label_2->setText(QApplication::translate("MarkerDock", "Count", 0));
        checkBox->setText(QApplication::translate("MarkerDock", "Visible", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QApplication::translate("MarkerDock", "Data", 0));
        label_4->setText(QApplication::translate("MarkerDock", "Color 1", 0));
        label_5->setText(QApplication::translate("MarkerDock", "Color 2", 0));
        label_6->setText(QApplication::translate("MarkerDock", "Line Weight", 0));
        label_7->setText(QString());
        label_8->setText(QApplication::translate("MarkerDock", "Font Size", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage2), QApplication::translate("MarkerDock", "Format", 0));
        apply->setText(QApplication::translate("MarkerDock", "Apply", 0));
        active->setText(QApplication::translate("MarkerDock", "Current Marker:", 0));
        add->setText(QApplication::translate("MarkerDock", "Add", 0));
        rem->setText(QApplication::translate("MarkerDock", "Remove", 0));
        position->setText(QApplication::translate("MarkerDock", "0/0", 0));
    } // retranslateUi

};

namespace Ui {
    class MarkerDock: public Ui_MarkerDock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKERDOCK_H
