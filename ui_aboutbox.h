/********************************************************************************
** Form generated from reading UI file 'aboutbox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTBOX_H
#define UI_ABOUTBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutBox
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QDialogButtonBox *btnClose;

    void setupUi(QDialog *AboutBox)
    {
        if (AboutBox->objectName().isEmpty())
            AboutBox->setObjectName(QString::fromUtf8("AboutBox"));
        AboutBox->setWindowModality(Qt::NonModal);
        AboutBox->resize(310, 225);
        gridLayout = new QGridLayout(AboutBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(AboutBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label);

        btnClose = new QDialogButtonBox(AboutBox);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setOrientation(Qt::Horizontal);
        btnClose->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(btnClose);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AboutBox);
        QObject::connect(btnClose, SIGNAL(clicked(QAbstractButton*)), AboutBox, SLOT(close()));

        QMetaObject::connectSlotsByName(AboutBox);
    } // setupUi

    void retranslateUi(QDialog *AboutBox)
    {
        AboutBox->setWindowTitle(QCoreApplication::translate("AboutBox", "About", nullptr));
        label->setText(QCoreApplication::translate("AboutBox", "Fritz control and configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutBox: public Ui_AboutBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTBOX_H
