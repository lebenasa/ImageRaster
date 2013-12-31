/********************************************************************************
** Form generated from reading UI file 'RulerForm.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RULERFORM_H
#define UI_RULERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "coloreditor.h"

QT_BEGIN_NAMESPACE

class Ui_RulerForm
{
public:
    QGridLayout *gridLayout;
    QFrame *line;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_10;
    QFrame *line_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFormLayout *formLayout;
    QLabel *labelNum1;
    QLineEdit *num1;
    QLabel *labelNum2;
    QLineEdit *num2;
    QLabel *labelNum3;
    QLineEdit *num3;
    QLabel *label1;
    QPlainTextEdit *label;
    QPushButton *pushButton;
    QWidget *tab_2;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    ColorEditor *color1;
    QLabel *label_5;
    ColorEditor *color2;
    QLabel *label_6;
    QSpinBox *lineWeight;
    QLabel *label_7;
    QFontComboBox *font;
    QLabel *label_8;
    QSpinBox *fontSize;

    void setupUi(QWidget *RulerForm)
    {
        if (RulerForm->objectName().isEmpty())
            RulerForm->setObjectName(QStringLiteral("RulerForm"));
        RulerForm->resize(291, 374);
        gridLayout = new QGridLayout(RulerForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        line = new QFrame(RulerForm);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 1, 1, 3);

        label_9 = new QLabel(RulerForm);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 3, 1, 1, 1);

        label_11 = new QLabel(RulerForm);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 3, 3, 1, 1);

        label_10 = new QLabel(RulerForm);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 3, 2, 1, 1);

        line_2 = new QFrame(RulerForm);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 4, 1, 1, 3);

        tabWidget = new QTabWidget(RulerForm);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        formLayout = new QFormLayout(tab);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelNum1 = new QLabel(tab);
        labelNum1->setObjectName(QStringLiteral("labelNum1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelNum1);

        num1 = new QLineEdit(tab);
        num1->setObjectName(QStringLiteral("num1"));
        num1->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, num1);

        labelNum2 = new QLabel(tab);
        labelNum2->setObjectName(QStringLiteral("labelNum2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelNum2);

        num2 = new QLineEdit(tab);
        num2->setObjectName(QStringLiteral("num2"));
        num2->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, num2);

        labelNum3 = new QLabel(tab);
        labelNum3->setObjectName(QStringLiteral("labelNum3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelNum3);

        num3 = new QLineEdit(tab);
        num3->setObjectName(QStringLiteral("num3"));
        num3->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, num3);

        label1 = new QLabel(tab);
        label1->setObjectName(QStringLiteral("label1"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label1);

        label = new QPlainTextEdit(tab);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, label);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(5, QFormLayout::LabelRole, pushButton);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        formLayout_2 = new QFormLayout(tab_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_4);

        color1 = new ColorEditor(tab_2);
        color1->setObjectName(QStringLiteral("color1"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, color1);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        color2 = new ColorEditor(tab_2);
        color2->setObjectName(QStringLiteral("color2"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, color2);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_6);

        lineWeight = new QSpinBox(tab_2);
        lineWeight->setObjectName(QStringLiteral("lineWeight"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lineWeight);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_7);

        font = new QFontComboBox(tab_2);
        font->setObjectName(QStringLiteral("font"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, font);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_8);

        fontSize = new QSpinBox(tab_2);
        fontSize->setObjectName(QStringLiteral("fontSize"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, fontSize);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 3);


        retranslateUi(RulerForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RulerForm);
    } // setupUi

    void retranslateUi(QWidget *RulerForm)
    {
        RulerForm->setWindowTitle(QApplication::translate("RulerForm", "Form", 0));
        label_9->setText(QString());
        label_11->setText(QApplication::translate("RulerForm", "Measurement 0/0", 0));
        label_10->setText(QString());
        labelNum1->setText(QApplication::translate("RulerForm", "Num1", 0));
        labelNum2->setText(QApplication::translate("RulerForm", "Num2", 0));
        labelNum3->setText(QApplication::translate("RulerForm", "Num3", 0));
        label1->setText(QApplication::translate("RulerForm", "Label", 0));
        pushButton->setText(QApplication::translate("RulerForm", "Default Label", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("RulerForm", "Data", 0));
        label_4->setText(QApplication::translate("RulerForm", "Color", 0));
        label_5->setText(QApplication::translate("RulerForm", "Outline", 0));
        label_6->setText(QApplication::translate("RulerForm", "Line Weight", 0));
        label_7->setText(QApplication::translate("RulerForm", "Font", 0));
        label_8->setText(QApplication::translate("RulerForm", "Font Size", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("RulerForm", "Format", 0));
    } // retranslateUi

};

namespace Ui {
    class RulerForm: public Ui_RulerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RULERFORM_H
