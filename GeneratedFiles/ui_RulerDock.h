/********************************************************************************
** Form generated from reading UI file 'RulerDock.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULERDOCK_H
#define UI_RULERDOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "coloreditor.h"

QT_BEGIN_NAMESPACE

class Ui_RulerDock
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFormLayout *formLayout;
    QLabel *label;
    QPushButton *default_;
    QSpacerItem *verticalSpacer;
    QLabel *num1;
    QLineEdit *data1;
    QLabel *num2;
    QLineEdit *data2;
    QLabel *num3;
    QLineEdit *data3;
    QPlainTextEdit *text;
    QWidget *tab_2;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    ColorEditor *color1;
    QLabel *label_6;
    ColorEditor *color2;
    QLabel *label_7;
    QSpinBox *penWidth;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_8;
    QFontComboBox *font_;
    QLabel *label_9;
    QSpinBox *fontSize;
    QFrame *line;
    QTableView *view;

    void setupUi(QDockWidget *RulerDock)
    {
        if (RulerDock->objectName().isEmpty())
            RulerDock->setObjectName(QStringLiteral("RulerDock"));
        RulerDock->resize(221, 464);
        RulerDock->setStyleSheet(QStringLiteral(""));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(dockWidgetContents);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 219, 440));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(180, 0));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        formLayout = new QFormLayout(tab);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetNoConstraint);
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        default_ = new QPushButton(tab);
        default_->setObjectName(QStringLiteral("default_"));
        sizePolicy.setHeightForWidth(default_->sizePolicy().hasHeightForWidth());
        default_->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::FieldRole, default_);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer);

        num1 = new QLabel(tab);
        num1->setObjectName(QStringLiteral("num1"));

        formLayout->setWidget(4, QFormLayout::LabelRole, num1);

        data1 = new QLineEdit(tab);
        data1->setObjectName(QStringLiteral("data1"));
        data1->setReadOnly(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, data1);

        num2 = new QLabel(tab);
        num2->setObjectName(QStringLiteral("num2"));

        formLayout->setWidget(6, QFormLayout::LabelRole, num2);

        data2 = new QLineEdit(tab);
        data2->setObjectName(QStringLiteral("data2"));
        data2->setReadOnly(true);

        formLayout->setWidget(6, QFormLayout::FieldRole, data2);

        num3 = new QLabel(tab);
        num3->setObjectName(QStringLiteral("num3"));

        formLayout->setWidget(7, QFormLayout::LabelRole, num3);

        data3 = new QLineEdit(tab);
        data3->setObjectName(QStringLiteral("data3"));
        data3->setReadOnly(true);

        formLayout->setWidget(7, QFormLayout::FieldRole, data3);

        text = new QPlainTextEdit(tab);
        text->setObjectName(QStringLiteral("text"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(text->sizePolicy().hasHeightForWidth());
        text->setSizePolicy(sizePolicy1);
        text->setMinimumSize(QSize(0, 1));
        text->setMaximumSize(QSize(16777215, 100));

        formLayout->setWidget(1, QFormLayout::SpanningRole, text);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        formLayout_2 = new QFormLayout(tab_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        color1 = new ColorEditor(tab_2);
        color1->setObjectName(QStringLiteral("color1"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, color1);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        color2 = new ColorEditor(tab_2);
        color2->setObjectName(QStringLiteral("color2"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, color2);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_7);

        penWidth = new QSpinBox(tab_2);
        penWidth->setObjectName(QStringLiteral("penWidth"));
        penWidth->setMinimum(1);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, penWidth);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(3, QFormLayout::LabelRole, verticalSpacer_3);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_8);

        font_ = new QFontComboBox(tab_2);
        font_->setObjectName(QStringLiteral("font_"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, font_);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_9);

        fontSize = new QSpinBox(tab_2);
        fontSize->setObjectName(QStringLiteral("fontSize"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, fontSize);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        line = new QFrame(scrollAreaWidgetContents);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        view = new QTableView(scrollAreaWidgetContents);
        view->setObjectName(QStringLiteral("view"));

        verticalLayout_2->addWidget(view);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        RulerDock->setWidget(dockWidgetContents);

        retranslateUi(RulerDock);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RulerDock);
    } // setupUi

    void retranslateUi(QDockWidget *RulerDock)
    {
        RulerDock->setWindowTitle(QApplication::translate("RulerDock", "Measurement", 0));
        label->setText(QApplication::translate("RulerDock", "Text", 0));
        default_->setText(QApplication::translate("RulerDock", "Default Text", 0));
        num1->setText(QApplication::translate("RulerDock", "num1", 0));
        num2->setText(QApplication::translate("RulerDock", "num2", 0));
        num3->setText(QApplication::translate("RulerDock", "num3", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("RulerDock", "Data", 0));
        label_5->setText(QApplication::translate("RulerDock", "Color", 0));
        label_6->setText(QApplication::translate("RulerDock", "Outline", 0));
        label_7->setText(QApplication::translate("RulerDock", "Border-size", 0));
        label_8->setText(QApplication::translate("RulerDock", "Font", 0));
        label_9->setText(QApplication::translate("RulerDock", "Font Size", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("RulerDock", "Format", 0));
    } // retranslateUi

};

namespace Ui {
    class RulerDock: public Ui_RulerDock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULERDOCK_H
