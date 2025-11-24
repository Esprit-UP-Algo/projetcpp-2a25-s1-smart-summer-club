/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QLabel *labelTitle;
    QHBoxLayout *hboxLayout;
    QPushButton *pushButtonAbonne;
    QPushButton *pushButtonEmployee;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 200);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName("vboxLayout");
        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTitle->setFont(font);

        vboxLayout->addWidget(labelTitle);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        pushButtonAbonne = new QPushButton(centralwidget);
        pushButtonAbonne->setObjectName("pushButtonAbonne");

        hboxLayout->addWidget(pushButtonAbonne);

        pushButtonEmployee = new QPushButton(centralwidget);
        pushButtonEmployee->setObjectName("pushButtonEmployee");

        hboxLayout->addWidget(pushButtonEmployee);


        vboxLayout->addLayout(hboxLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "Bienvenue", nullptr));
        pushButtonAbonne->setText(QCoreApplication::translate("MainWindow", "Gestion Abonn\303\251", nullptr));
        pushButtonEmployee->setText(QCoreApplication::translate("MainWindow", "Gestion Employee", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
