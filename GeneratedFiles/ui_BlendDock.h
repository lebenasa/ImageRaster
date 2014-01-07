/********************************************************************************
** Form generated from reading UI file 'BlendDock.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLENDDOCK_H
#define UI_BLENDDOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "coloreditor.h"

QT_BEGIN_NAMESPACE

class Ui_BlendDock
{
public:
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QFormLayout *formLayout;
    QLabel *label_2;
    QSpinBox *thumbSize;
    QLabel *label_3;
    QSpinBox *anchorSize;
    QLabel *label_4;
    ColorEditor *color1;
    QLabel *label_5;
    ColorEditor *color2;
    QLabel *label_6;
    QSpinBox *lineweight;
    QLabel *label_7;
    QPlainTextEdit *text;

    void setupUi(QDockWidget *BlendDock)
    {
        if (BlendDock->objectName().isEmpty())
            BlendDock->setObjectName(QStringLiteral("BlendDock"));
        BlendDock->resize(233, 286);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMaximumSize(QSize(300, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        thumbSize = new QSpinBox(frame);
        thumbSize->setObjectName(QStringLiteral("thumbSize"));

        formLayout->setWidget(0, QFormLayout::FieldRole, thumbSize);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        anchorSize = new QSpinBox(frame);
        anchorSize->setObjectName(QStringLiteral("anchorSize"));

        formLayout->setWidget(1, QFormLayout::FieldRole, anchorSize);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        color1 = new ColorEditor(frame);
        color1->setObjectName(QStringLiteral("color1"));

        formLayout->setWidget(2, QFormLayout::FieldRole, color1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        color2 = new ColorEditor(frame);
        color2->setObjectName(QStringLiteral("color2"));

        formLayout->setWidget(3, QFormLayout::FieldRole, color2);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

        lineweight = new QSpinBox(frame);
        lineweight->setObjectName(QStringLiteral("lineweight"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineweight);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_7);

        text = new QPlainTextEdit(frame);
        text->setObjectName(QStringLiteral("text"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(text->sizePolicy().hasHeightForWidth());
        text->setSizePolicy(sizePolicy2);
        text->setMaximumSize(QSize(300, 16777215));

        formLayout->setWidget(6, QFormLayout::SpanningRole, text);


        horizontalLayout->addWidget(frame);

        BlendDock->setWidget(dockWidgetContents);
#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(thumbSize);
        label_3->setBuddy(anchorSize);
        label_4->setBuddy(color1);
        label_5->setBuddy(color2);
        label_6->setBuddy(lineweight);
#endif // QT_NO_SHORTCUT

        retranslateUi(BlendDock);

        QMetaObject::connectSlotsByName(BlendDock);
    } // setupUi

    void retranslateUi(QDockWidget *BlendDock)
    {
        BlendDock->setWindowTitle(QApplication::translate("BlendDock", "Thumbnail Editor", 0));
        label_2->setText(QApplication::translate("BlendDock", "Thumbnail size:", 0));
        label_3->setText(QApplication::translate("BlendDock", "Anchor size:", 0));
        label_4->setText(QApplication::translate("BlendDock", "Border color:", 0));
        label_5->setText(QApplication::translate("BlendDock", "Outline color:", 0));
        label_6->setText(QApplication::translate("BlendDock", "Border thickness:", 0));
        label_7->setText(QApplication::translate("BlendDock", "Text:", 0));
    } // retranslateUi

};

namespace Ui {
    class BlendDock: public Ui_BlendDock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLENDDOCK_H
