/********************************************************************************
** Form generated from reading UI file 'authen.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHEN_H
#define UI_AUTHEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_authen
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *authen)
    {
        if (authen->objectName().isEmpty())
            authen->setObjectName("authen");
        authen->resize(494, 388);
        label = new QLabel(authen);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 80, 81, 20));
        label_2 = new QLabel(authen);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 200, 121, 20));
        lineEdit = new QLineEdit(authen);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(50, 120, 401, 26));
        lineEdit_2 = new QLineEdit(authen);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(50, 250, 401, 26));
        buttonBox = new QDialogButtonBox(authen);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(130, 330, 193, 29));
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(authen);

        QMetaObject::connectSlotsByName(authen);
    } // setupUi

    void retranslateUi(QDialog *authen)
    {
        authen->setWindowTitle(QCoreApplication::translate("authen", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("authen", "Email:", nullptr));
        label_2->setText(QCoreApplication::translate("authen", "mot de passe:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class authen: public Ui_authen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHEN_H
