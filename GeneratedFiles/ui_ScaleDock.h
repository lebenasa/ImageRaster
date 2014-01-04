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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScaleDock
{
public:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QCheckBox *left_;
    QCheckBox *bottomleft;
    QCheckBox *bottomright;
    QCheckBox *topleft;
    QCheckBox *center;
    QCheckBox *top;
    QCheckBox *topright;
    QCheckBox *bottom;
    QCheckBox *right;
    QLabel *label;
    QComboBox *length;
    QComboBox *unit;
    QComboBox *style_;
    QSpacerItem *verticalSpacer;

    void setupUi(QDockWidget *ScaleDock)
    {
        if (ScaleDock->objectName().isEmpty())
            ScaleDock->setObjectName(QStringLiteral("ScaleDock"));
        ScaleDock->resize(171, 317);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 4, 0, 1, 1);

        label_4 = new QLabel(dockWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 6, 0, 1, 1);

        frame_2 = new QFrame(dockWidgetContents);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        frame = new QFrame(frame_2);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        left_ = new QCheckBox(frame);
        left_->setObjectName(QStringLiteral("left_"));

        gridLayout->addWidget(left_, 1, 0, 1, 1);

        bottomleft = new QCheckBox(frame);
        bottomleft->setObjectName(QStringLiteral("bottomleft"));

        gridLayout->addWidget(bottomleft, 2, 0, 1, 1);

        bottomright = new QCheckBox(frame);
        bottomright->setObjectName(QStringLiteral("bottomright"));

        gridLayout->addWidget(bottomright, 2, 2, 1, 1);

        topleft = new QCheckBox(frame);
        topleft->setObjectName(QStringLiteral("topleft"));

        gridLayout->addWidget(topleft, 0, 0, 1, 1);

        center = new QCheckBox(frame);
        center->setObjectName(QStringLiteral("center"));

        gridLayout->addWidget(center, 1, 1, 1, 1);

        top = new QCheckBox(frame);
        top->setObjectName(QStringLiteral("top"));

        gridLayout->addWidget(top, 0, 1, 1, 1);

        topright = new QCheckBox(frame);
        topright->setObjectName(QStringLiteral("topright"));

        gridLayout->addWidget(topright, 0, 2, 1, 1);

        bottom = new QCheckBox(frame);
        bottom->setObjectName(QStringLiteral("bottom"));

        gridLayout->addWidget(bottom, 2, 1, 1, 1);

        right = new QCheckBox(frame);
        right->setObjectName(QStringLiteral("right"));

        gridLayout->addWidget(right, 1, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);


        gridLayout_3->addWidget(frame_2, 1, 0, 1, 1);

        label = new QLabel(dockWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        length = new QComboBox(dockWidgetContents);
        length->setObjectName(QStringLiteral("length"));
        length->setEditable(true);

        gridLayout_3->addWidget(length, 3, 0, 1, 1);

        unit = new QComboBox(dockWidgetContents);
        unit->setObjectName(QStringLiteral("unit"));

        gridLayout_3->addWidget(unit, 5, 0, 1, 1);

        style_ = new QComboBox(dockWidgetContents);
        style_->setObjectName(QStringLiteral("style_"));

        gridLayout_3->addWidget(style_, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 8, 0, 1, 1);

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
        label_3->setText(QApplication::translate("ScaleDock", "Length (\302\265m):", 0));
        label_2->setText(QApplication::translate("ScaleDock", "Unit:", 0));
        label_4->setText(QApplication::translate("ScaleDock", "Style:", 0));
        left_->setText(QString());
        bottomleft->setText(QString());
        bottomright->setText(QString());
        topleft->setText(QString());
        center->setText(QString());
        top->setText(QString());
        topright->setText(QString());
        bottom->setText(QString());
        right->setText(QString());
        label->setText(QApplication::translate("ScaleDock", "Position (center=moveable):", 0));
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
        unit->clear();
        unit->insertItems(0, QStringList()
         << QApplication::translate("ScaleDock", "\302\265m", 0)
         << QApplication::translate("ScaleDock", "mm", 0)
         << QApplication::translate("ScaleDock", "cm", 0)
         << QApplication::translate("ScaleDock", "m", 0)
        );
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
