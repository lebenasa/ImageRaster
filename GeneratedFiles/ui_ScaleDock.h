/********************************************************************************
** Form generated from reading UI file 'ScaleDock.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALEDOCK_H
#define UI_SCALEDOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScaleDock
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QPushButton *rem;
    QLabel *label;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QRadioButton *topleft;
    QRadioButton *top;
    QRadioButton *bottomright;
    QRadioButton *bottom;
    QRadioButton *bottomleft;
    QRadioButton *left_;
    QRadioButton *center;
    QRadioButton *right;
    QRadioButton *topright;
    QLabel *label_5;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_4;
    QRadioButton *topleft_2;
    QRadioButton *top_2;
    QRadioButton *bottomright_2;
    QRadioButton *bottom_2;
    QRadioButton *bottomleft_2;
    QRadioButton *left_2;
    QRadioButton *center_2;
    QRadioButton *right_2;
    QRadioButton *topright_2;
    QLabel *label_6;
    QLabel *label_3;
    QComboBox *length;
    QLabel *label_2;
    QComboBox *unit;
    QLabel *label_4;
    QComboBox *style_;
    QSpacerItem *verticalSpacer;
    QButtonGroup *horizontalGroup;
    QButtonGroup *verticalGroup;

    void setupUi(QDockWidget *ScaleDock)
    {
        if (ScaleDock->objectName().isEmpty())
            ScaleDock->setObjectName(QStringLiteral("ScaleDock"));
        ScaleDock->resize(230, 367);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        rem = new QPushButton(dockWidgetContents);
        rem->setObjectName(QStringLiteral("rem"));

        verticalLayout->addWidget(rem);

        label = new QLabel(dockWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        frame_5 = new QFrame(dockWidgetContents);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_5);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        frame_2 = new QFrame(frame_5);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        frame = new QFrame(frame_2);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        topleft = new QRadioButton(frame);
        horizontalGroup = new QButtonGroup(ScaleDock);
        horizontalGroup->setObjectName(QStringLiteral("horizontalGroup"));
        horizontalGroup->addButton(topleft);
        topleft->setObjectName(QStringLiteral("topleft"));

        gridLayout->addWidget(topleft, 0, 0, 1, 1);

        top = new QRadioButton(frame);
        horizontalGroup->addButton(top);
        top->setObjectName(QStringLiteral("top"));

        gridLayout->addWidget(top, 0, 1, 1, 1);

        bottomright = new QRadioButton(frame);
        horizontalGroup->addButton(bottomright);
        bottomright->setObjectName(QStringLiteral("bottomright"));

        gridLayout->addWidget(bottomright, 2, 2, 1, 1);

        bottom = new QRadioButton(frame);
        horizontalGroup->addButton(bottom);
        bottom->setObjectName(QStringLiteral("bottom"));

        gridLayout->addWidget(bottom, 2, 1, 1, 1);

        bottomleft = new QRadioButton(frame);
        horizontalGroup->addButton(bottomleft);
        bottomleft->setObjectName(QStringLiteral("bottomleft"));
        bottomleft->setChecked(true);

        gridLayout->addWidget(bottomleft, 2, 0, 1, 1);

        left_ = new QRadioButton(frame);
        horizontalGroup->addButton(left_);
        left_->setObjectName(QStringLiteral("left_"));
        left_->setEnabled(false);

        gridLayout->addWidget(left_, 1, 0, 1, 1);

        center = new QRadioButton(frame);
        horizontalGroup->addButton(center);
        center->setObjectName(QStringLiteral("center"));

        gridLayout->addWidget(center, 1, 1, 1, 1);

        right = new QRadioButton(frame);
        horizontalGroup->addButton(right);
        right->setObjectName(QStringLiteral("right"));
        right->setEnabled(false);

        gridLayout->addWidget(right, 1, 2, 1, 1);

        topright = new QRadioButton(frame);
        horizontalGroup->addButton(topright);
        topright->setObjectName(QStringLiteral("topright"));

        gridLayout->addWidget(topright, 0, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(frame_2);

        frame_3 = new QFrame(frame_5);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        frame_4 = new QFrame(frame_3);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        sizePolicy1.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy1);
        frame_4->setFrameShape(QFrame::Box);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_4);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        topleft_2 = new QRadioButton(frame_4);
        verticalGroup = new QButtonGroup(ScaleDock);
        verticalGroup->setObjectName(QStringLiteral("verticalGroup"));
        verticalGroup->addButton(topleft_2);
        topleft_2->setObjectName(QStringLiteral("topleft_2"));

        gridLayout_4->addWidget(topleft_2, 0, 0, 1, 1);

        top_2 = new QRadioButton(frame_4);
        verticalGroup->addButton(top_2);
        top_2->setObjectName(QStringLiteral("top_2"));
        top_2->setEnabled(false);

        gridLayout_4->addWidget(top_2, 0, 1, 1, 1);

        bottomright_2 = new QRadioButton(frame_4);
        verticalGroup->addButton(bottomright_2);
        bottomright_2->setObjectName(QStringLiteral("bottomright_2"));

        gridLayout_4->addWidget(bottomright_2, 2, 2, 1, 1);

        bottom_2 = new QRadioButton(frame_4);
        verticalGroup->addButton(bottom_2);
        bottom_2->setObjectName(QStringLiteral("bottom_2"));
        bottom_2->setEnabled(false);

        gridLayout_4->addWidget(bottom_2, 2, 1, 1, 1);

        bottomleft_2 = new QRadioButton(frame_4);
        verticalGroup->addButton(bottomleft_2);
        bottomleft_2->setObjectName(QStringLiteral("bottomleft_2"));
        bottomleft_2->setChecked(true);

        gridLayout_4->addWidget(bottomleft_2, 2, 0, 1, 1);

        left_2 = new QRadioButton(frame_4);
        verticalGroup->addButton(left_2);
        left_2->setObjectName(QStringLiteral("left_2"));

        gridLayout_4->addWidget(left_2, 1, 0, 1, 1);

        center_2 = new QRadioButton(frame_4);
        verticalGroup->addButton(center_2);
        center_2->setObjectName(QStringLiteral("center_2"));

        gridLayout_4->addWidget(center_2, 1, 1, 1, 1);

        right_2 = new QRadioButton(frame_4);
        verticalGroup->addButton(right_2);
        right_2->setObjectName(QStringLiteral("right_2"));

        gridLayout_4->addWidget(right_2, 1, 2, 1, 1);

        topright_2 = new QRadioButton(frame_4);
        verticalGroup->addButton(topright_2);
        topright_2->setObjectName(QStringLiteral("topright_2"));

        gridLayout_4->addWidget(topright_2, 0, 2, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_4);


        gridLayout_3->addWidget(frame_4, 1, 0, 1, 1);

        label_6 = new QLabel(frame_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(frame_3);


        verticalLayout->addWidget(frame_5);

        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        length = new QComboBox(dockWidgetContents);
        length->setObjectName(QStringLiteral("length"));
        length->setEditable(true);

        verticalLayout->addWidget(length);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        unit = new QComboBox(dockWidgetContents);
        unit->setObjectName(QStringLiteral("unit"));

        verticalLayout->addWidget(unit);

        label_4 = new QLabel(dockWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        style_ = new QComboBox(dockWidgetContents);
        style_->setObjectName(QStringLiteral("style_"));

        verticalLayout->addWidget(style_);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        ScaleDock->setWidget(dockWidgetContents);
        QWidget::setTabOrder(topleft, top);
        QWidget::setTabOrder(top, topright);
        QWidget::setTabOrder(topright, left_);
        QWidget::setTabOrder(left_, center);
        QWidget::setTabOrder(center, right);
        QWidget::setTabOrder(right, bottomleft);
        QWidget::setTabOrder(bottomleft, bottom);
        QWidget::setTabOrder(bottom, bottomright);
        QWidget::setTabOrder(bottomright, length);
        QWidget::setTabOrder(length, unit);
        QWidget::setTabOrder(unit, style_);

        retranslateUi(ScaleDock);

        QMetaObject::connectSlotsByName(ScaleDock);
    } // setupUi

    void retranslateUi(QDockWidget *ScaleDock)
    {
        ScaleDock->setWindowTitle(QApplication::translate("ScaleDock", "Scale Editor", 0));
        rem->setText(QApplication::translate("ScaleDock", "Hide Scale", 0));
        label->setText(QApplication::translate("ScaleDock", "Position (center=moveable):", 0));
        topleft->setText(QString());
        top->setText(QString());
        bottomright->setText(QString());
        bottom->setText(QString());
        bottomleft->setText(QString());
        left_->setText(QString());
        center->setText(QString());
        right->setText(QString());
        topright->setText(QString());
        label_5->setText(QApplication::translate("ScaleDock", "Horizontal:", 0));
        topleft_2->setText(QString());
        top_2->setText(QString());
        bottomright_2->setText(QString());
        bottom_2->setText(QString());
        bottomleft_2->setText(QString());
        left_2->setText(QString());
        center_2->setText(QString());
        right_2->setText(QString());
        topright_2->setText(QString());
        label_6->setText(QApplication::translate("ScaleDock", "Vertical:", 0));
        label_3->setText(QApplication::translate("ScaleDock", "Length:", 0));
        length->clear();
        length->insertItems(0, QStringList()
         << QApplication::translate("ScaleDock", "1", 0)
         << QApplication::translate("ScaleDock", "5", 0)
         << QApplication::translate("ScaleDock", "10", 0)
         << QApplication::translate("ScaleDock", "50", 0)
         << QApplication::translate("ScaleDock", "100", 0)
         << QApplication::translate("ScaleDock", "500", 0)
         << QApplication::translate("ScaleDock", "1000", 0)
         << QApplication::translate("ScaleDock", "5000", 0)
         << QApplication::translate("ScaleDock", "10000", 0)
         << QApplication::translate("ScaleDock", "50000", 0)
        );
        label_2->setText(QApplication::translate("ScaleDock", "Unit:", 0));
        unit->clear();
        unit->insertItems(0, QStringList()
         << QApplication::translate("ScaleDock", "\302\265m", 0)
         << QApplication::translate("ScaleDock", "mm", 0)
         << QApplication::translate("ScaleDock", "cm", 0)
         << QApplication::translate("ScaleDock", "m", 0)
        );
        label_4->setText(QApplication::translate("ScaleDock", "Style:", 0));
        style_->clear();
        style_->insertItems(0, QStringList()
         << QApplication::translate("ScaleDock", "Bar", 0)
         << QApplication::translate("ScaleDock", "Ruler", 0)
         << QApplication::translate("ScaleDock", "Simple Line", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class ScaleDock: public Ui_ScaleDock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALEDOCK_H
