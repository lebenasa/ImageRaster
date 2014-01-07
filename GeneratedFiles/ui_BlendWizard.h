/********************************************************************************
** Form generated from reading UI file 'BlendWizard.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLENDWIZARD_H
#define UI_BLENDWIZARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWizard>
#include <QtWidgets/QWizardPage>
#include "coloreditor.h"

QT_BEGIN_NAMESPACE

class Ui_BlendWizard
{
public:
    QWizardPage *Blend1;
    QVBoxLayout *verticalLayout;
    QWizardPage *Blend2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *browse;
    QPushButton *browseButton;
    QWizardPage *Blend3;
    QGridLayout *gridLayout;
    QGraphicsView *view1;
    QWizardPage *Blend4;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *style;
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
    QGraphicsView *view2;

    void setupUi(QWizard *BlendWizard)
    {
        if (BlendWizard->objectName().isEmpty())
            BlendWizard->setObjectName(QStringLiteral("BlendWizard"));
        BlendWizard->resize(623, 455);
        BlendWizard->setWizardStyle(QWizard::AeroStyle);
        Blend1 = new QWizardPage();
        Blend1->setObjectName(QStringLiteral("Blend1"));
        verticalLayout = new QVBoxLayout(Blend1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        BlendWizard->setPage(0, Blend1);
        Blend2 = new QWizardPage();
        Blend2->setObjectName(QStringLiteral("Blend2"));
        horizontalLayout = new QHBoxLayout(Blend2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        browse = new QLineEdit(Blend2);
        browse->setObjectName(QStringLiteral("browse"));

        horizontalLayout->addWidget(browse);

        browseButton = new QPushButton(Blend2);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        horizontalLayout->addWidget(browseButton);

        BlendWizard->setPage(1, Blend2);
        Blend3 = new QWizardPage();
        Blend3->setObjectName(QStringLiteral("Blend3"));
        gridLayout = new QGridLayout(Blend3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        view1 = new QGraphicsView(Blend3);
        view1->setObjectName(QStringLiteral("view1"));
        view1->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));

        gridLayout->addWidget(view1, 0, 0, 1, 1);

        BlendWizard->setPage(2, Blend3);
        Blend4 = new QWizardPage();
        Blend4->setObjectName(QStringLiteral("Blend4"));
        horizontalLayout_2 = new QHBoxLayout(Blend4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        frame = new QFrame(Blend4);
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
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(75, 0));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        style = new QComboBox(frame);
        style->setObjectName(QStringLiteral("style"));
        style->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, style);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        thumbSize = new QSpinBox(frame);
        thumbSize->setObjectName(QStringLiteral("thumbSize"));

        formLayout->setWidget(1, QFormLayout::FieldRole, thumbSize);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        anchorSize = new QSpinBox(frame);
        anchorSize->setObjectName(QStringLiteral("anchorSize"));

        formLayout->setWidget(2, QFormLayout::FieldRole, anchorSize);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        color1 = new ColorEditor(frame);
        color1->setObjectName(QStringLiteral("color1"));

        formLayout->setWidget(3, QFormLayout::FieldRole, color1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        color2 = new ColorEditor(frame);
        color2->setObjectName(QStringLiteral("color2"));

        formLayout->setWidget(4, QFormLayout::FieldRole, color2);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        lineweight = new QSpinBox(frame);
        lineweight->setObjectName(QStringLiteral("lineweight"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineweight);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        text = new QPlainTextEdit(frame);
        text->setObjectName(QStringLiteral("text"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(text->sizePolicy().hasHeightForWidth());
        text->setSizePolicy(sizePolicy2);
        text->setMaximumSize(QSize(200, 16777215));

        formLayout->setWidget(7, QFormLayout::SpanningRole, text);


        horizontalLayout_2->addWidget(frame);

        view2 = new QGraphicsView(Blend4);
        view2->setObjectName(QStringLiteral("view2"));
        view2->setMinimumSize(QSize(0, 250));

        horizontalLayout_2->addWidget(view2);

        BlendWizard->setPage(3, Blend4);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(style);
        label_2->setBuddy(thumbSize);
        label_3->setBuddy(anchorSize);
        label_4->setBuddy(color1);
        label_5->setBuddy(color2);
        label_6->setBuddy(lineweight);
#endif // QT_NO_SHORTCUT

        retranslateUi(BlendWizard);

        QMetaObject::connectSlotsByName(BlendWizard);
    } // setupUi

    void retranslateUi(QWizard *BlendWizard)
    {
        BlendWizard->setWindowTitle(QApplication::translate("BlendWizard", "Blend", 0));
        Blend1->setTitle(QApplication::translate("BlendWizard", "Blend Wizard", 0));
        Blend1->setSubTitle(QApplication::translate("BlendWizard", "Blend is ImageRaster utility to create professional looking thumbnail for your image. Press next to continue.", 0));
        Blend2->setTitle(QApplication::translate("BlendWizard", "Open Image for Thumbnail", 0));
        browseButton->setText(QApplication::translate("BlendWizard", "Browse", 0));
        Blend3->setTitle(QApplication::translate("BlendWizard", "Crop", 0));
        Blend3->setSubTitle(QApplication::translate("BlendWizard", "Select part of the image that will be presented as thumbnail. Unnecessary part will be neglected. You can press right mouse button on image to reset selection.", 0));
        Blend4->setTitle(QApplication::translate("BlendWizard", "Style & Position Editor", 0));
        Blend4->setSubTitle(QApplication::translate("BlendWizard", "Here you can change your thumbnail appearance and add it to the scene. Note that you can't change thumbnail style after you close this wizard.", 0));
        label->setText(QApplication::translate("BlendWizard", "Style:", 0));
        style->clear();
        style->insertItems(0, QStringList()
         << QApplication::translate("BlendWizard", "Circle (clip)", 0)
         << QApplication::translate("BlendWizard", "Box (clip)", 0)
         << QApplication::translate("BlendWizard", "Circle (strectch)", 0)
         << QApplication::translate("BlendWizard", "Box (stretch)", 0)
         << QApplication::translate("BlendWizard", "Ellipse", 0)
         << QApplication::translate("BlendWizard", "Rectangle", 0)
        );
        label_2->setText(QApplication::translate("BlendWizard", "Thumbnail size:", 0));
        label_3->setText(QApplication::translate("BlendWizard", "Anchor size:", 0));
        label_4->setText(QApplication::translate("BlendWizard", "Border color:", 0));
        label_5->setText(QApplication::translate("BlendWizard", "Outline color:", 0));
        label_6->setText(QApplication::translate("BlendWizard", "Border thickness:", 0));
        label_7->setText(QApplication::translate("BlendWizard", "Text:", 0));
    } // retranslateUi

};

namespace Ui {
    class BlendWizard: public Ui_BlendWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLENDWIZARD_H
