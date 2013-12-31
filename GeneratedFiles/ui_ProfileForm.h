/********************************************************************************
** Form generated from reading UI file 'ProfileForm.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEFORM_H
#define UI_PROFILEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uiProfileForm
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPushButton *remove;
    QLabel *label;
    QPushButton *calibrate;
    QPushButton *add;
    QLineEdit *x;
    QLineEdit *y;
    QSpacerItem *verticalSpacer;
    QListView *view;

    void setupUi(QWidget *uiProfileForm)
    {
        if (uiProfileForm->objectName().isEmpty())
            uiProfileForm->setObjectName(QStringLiteral("uiProfileForm"));
        uiProfileForm->resize(266, 292);
        uiProfileForm->setMaximumSize(QSize(16777215, 500));
        gridLayout = new QGridLayout(uiProfileForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(uiProfileForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        remove = new QPushButton(uiProfileForm);
        remove->setObjectName(QStringLiteral("remove"));

        gridLayout->addWidget(remove, 2, 2, 1, 1);

        label = new QLabel(uiProfileForm);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        calibrate = new QPushButton(uiProfileForm);
        calibrate->setObjectName(QStringLiteral("calibrate"));

        gridLayout->addWidget(calibrate, 1, 2, 1, 1);

        add = new QPushButton(uiProfileForm);
        add->setObjectName(QStringLiteral("add"));

        gridLayout->addWidget(add, 0, 2, 1, 1);

        x = new QLineEdit(uiProfileForm);
        x->setObjectName(QStringLiteral("x"));

        gridLayout->addWidget(x, 4, 1, 1, 2);

        y = new QLineEdit(uiProfileForm);
        y->setObjectName(QStringLiteral("y"));

        gridLayout->addWidget(y, 5, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        view = new QListView(uiProfileForm);
        view->setObjectName(QStringLiteral("view"));

        gridLayout->addWidget(view, 0, 0, 4, 2);

        QWidget::setTabOrder(view, add);
        QWidget::setTabOrder(add, calibrate);
        QWidget::setTabOrder(calibrate, remove);
        QWidget::setTabOrder(remove, x);
        QWidget::setTabOrder(x, y);

        retranslateUi(uiProfileForm);

        QMetaObject::connectSlotsByName(uiProfileForm);
    } // setupUi

    void retranslateUi(QWidget *uiProfileForm)
    {
        uiProfileForm->setWindowTitle(QApplication::translate("uiProfileForm", "Calibration Profile", 0));
        label_2->setText(QApplication::translate("uiProfileForm", "Y Ratio:", 0));
        remove->setText(QApplication::translate("uiProfileForm", "Remove", 0));
        label->setText(QApplication::translate("uiProfileForm", "X Ratio:", 0));
        calibrate->setText(QApplication::translate("uiProfileForm", "Calibrate", 0));
        add->setText(QApplication::translate("uiProfileForm", "Add", 0));
    } // retranslateUi

};

namespace Ui {
    class uiProfileForm: public Ui_uiProfileForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEFORM_H
