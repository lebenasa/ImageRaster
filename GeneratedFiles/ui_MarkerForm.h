/********************************************************************************
** Form generated from reading UI file 'MarkerForm.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKERFORM_H
#define UI_MARKERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "coloreditor.h"

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
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
    QFontComboBox *font;
    QLabel *label_8;
    QSpinBox *fontSize;
    QPushButton *apply;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_9;
    QFrame *frame;
    QGridLayout *gridLayout;
    QPushButton *first;
    QPushButton *add;
    QPushButton *last;
    QPushButton *rem;
    QPushButton *next;
    QPushButton *previous;
    QSpacerItem *horizontalSpacer;
    QPushButton *set;
    QLabel *position;
    QLabel *active;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(218, 465);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        tabWidget = new QTabWidget(Form);
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

        font = new QFontComboBox(tabWidgetPage2);
        font->setObjectName(QStringLiteral("font"));

        gridLayout_2->addWidget(font, 4, 1, 1, 1);

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

        apply = new QPushButton(Form);
        apply->setObjectName(QStringLiteral("apply"));

        verticalLayout->addWidget(apply);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_3);

        label_9 = new QLabel(Form);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout->addWidget(label_9);

        frame = new QFrame(Form);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(200, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(4);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        first = new QPushButton(frame);
        first->setObjectName(QStringLiteral("first"));
        sizePolicy1.setHeightForWidth(first->sizePolicy().hasHeightForWidth());
        first->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(first, 2, 0, 1, 1);

        add = new QPushButton(frame);
        add->setObjectName(QStringLiteral("add"));
        sizePolicy1.setHeightForWidth(add->sizePolicy().hasHeightForWidth());
        add->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(add, 3, 0, 1, 2);

        last = new QPushButton(frame);
        last->setObjectName(QStringLiteral("last"));
        sizePolicy1.setHeightForWidth(last->sizePolicy().hasHeightForWidth());
        last->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(last, 2, 3, 1, 1);

        rem = new QPushButton(frame);
        rem->setObjectName(QStringLiteral("rem"));
        sizePolicy1.setHeightForWidth(rem->sizePolicy().hasHeightForWidth());
        rem->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(rem, 3, 2, 1, 2);

        next = new QPushButton(frame);
        next->setObjectName(QStringLiteral("next"));
        sizePolicy1.setHeightForWidth(next->sizePolicy().hasHeightForWidth());
        next->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(next, 2, 2, 1, 1);

        previous = new QPushButton(frame);
        previous->setObjectName(QStringLiteral("previous"));
        sizePolicy1.setHeightForWidth(previous->sizePolicy().hasHeightForWidth());
        previous->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(previous, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        set = new QPushButton(frame);
        set->setObjectName(QStringLiteral("set"));
        sizePolicy1.setHeightForWidth(set->sizePolicy().hasHeightForWidth());
        set->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(set, 4, 1, 1, 2);

        position = new QLabel(frame);
        position->setObjectName(QStringLiteral("position"));
        position->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(position, 0, 3, 1, 1);

        active = new QLabel(frame);
        active->setObjectName(QStringLiteral("active"));

        gridLayout->addWidget(active, 0, 0, 1, 3);


        verticalLayout->addWidget(frame);

        QWidget::setTabOrder(label, count);
        QWidget::setTabOrder(count, color1);
        QWidget::setTabOrder(color1, color2);
        QWidget::setTabOrder(color2, weight);
        QWidget::setTabOrder(weight, font);
        QWidget::setTabOrder(font, fontSize);
        QWidget::setTabOrder(fontSize, first);
        QWidget::setTabOrder(first, previous);
        QWidget::setTabOrder(previous, next);
        QWidget::setTabOrder(next, last);
        QWidget::setTabOrder(last, add);
        QWidget::setTabOrder(add, rem);
        QWidget::setTabOrder(rem, set);

        retranslateUi(Form);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label1->setText(QApplication::translate("Form", "Label", 0));
        label_2->setText(QApplication::translate("Form", "Count", 0));
        checkBox->setText(QApplication::translate("Form", "Visible", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QApplication::translate("Form", "Data", 0));
        label_4->setText(QApplication::translate("Form", "Color 1", 0));
        label_5->setText(QApplication::translate("Form", "Color 2", 0));
        label_6->setText(QApplication::translate("Form", "Line Weight", 0));
        label_7->setText(QString());
        label_8->setText(QApplication::translate("Form", "Font Size", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage2), QApplication::translate("Form", "Format", 0));
        apply->setText(QApplication::translate("Form", "Apply", 0));
        label_9->setText(QApplication::translate("Form", "Control", 0));
#ifndef QT_NO_TOOLTIP
        first->setToolTip(QApplication::translate("Form", "First", 0));
#endif // QT_NO_TOOLTIP
        first->setText(QApplication::translate("Form", "<<", 0));
        add->setText(QApplication::translate("Form", "Add", 0));
#ifndef QT_NO_TOOLTIP
        last->setToolTip(QApplication::translate("Form", "Last", 0));
#endif // QT_NO_TOOLTIP
        last->setText(QApplication::translate("Form", ">>", 0));
        rem->setText(QApplication::translate("Form", "Remove", 0));
#ifndef QT_NO_TOOLTIP
        next->setToolTip(QApplication::translate("Form", "Next", 0));
#endif // QT_NO_TOOLTIP
        next->setText(QApplication::translate("Form", ">", 0));
#ifndef QT_NO_TOOLTIP
        previous->setToolTip(QApplication::translate("Form", "Previous", 0));
#endif // QT_NO_TOOLTIP
        previous->setText(QApplication::translate("Form", "<", 0));
        set->setText(QApplication::translate("Form", "Set", 0));
        position->setText(QApplication::translate("Form", "0/0", 0));
        active->setText(QApplication::translate("Form", "Current Marker:", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKERFORM_H
