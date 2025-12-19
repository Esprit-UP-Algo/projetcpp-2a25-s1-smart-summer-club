/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox_menu;
    QPushButton *pushButton_abonne;
    QPushButton *pushButton_employe;
    QPushButton *pushButton_inscription_menu;
    QPushButton *pushButton_activite;
    QGroupBox *groupBox_form;
    QLabel *label_idActivite;
    QLineEdit *lineEdit_idActivite;
    QLabel *label_nom;
    QLineEdit *txtname;
    QLabel *label_description;
    QLabel *label_duree;
    QLineEdit *lineEdit_duree;
    QLabel *label_lieu;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_modifier;
    QPushButton *pushButton_supprimer;
    QPushButton *pushButton_actualiser;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1582, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox_menu = new QGroupBox(centralwidget);
        groupBox_menu->setObjectName("groupBox_menu");
        groupBox_menu->setGeometry(QRect(0, 10, 160, 571));
        groupBox_menu->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"background-color: rgb(0, 0, 128);\n"
"border: 2px solid black;\n"
"border-radius: 8px;\n"
"margin-top: 20px;\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 14px;\n"
"}\n"
"QPushButton {\n"
"    background-color: orange;\n"
"    color: white;\n"
"    border: 2px solid white;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        pushButton_abonne = new QPushButton(groupBox_menu);
        pushButton_abonne->setObjectName("pushButton_abonne");
        pushButton_abonne->setGeometry(QRect(10, 40, 140, 40));
        pushButton_employe = new QPushButton(groupBox_menu);
        pushButton_employe->setObjectName("pushButton_employe");
        pushButton_employe->setGeometry(QRect(10, 100, 140, 40));
        pushButton_inscription_menu = new QPushButton(groupBox_menu);
        pushButton_inscription_menu->setObjectName("pushButton_inscription_menu");
        pushButton_inscription_menu->setGeometry(QRect(10, 160, 140, 40));
        pushButton_activite = new QPushButton(groupBox_menu);
        pushButton_activite->setObjectName("pushButton_activite");
        pushButton_activite->setGeometry(QRect(10, 220, 140, 40));
        groupBox_form = new QGroupBox(centralwidget);
        groupBox_form->setObjectName("groupBox_form");
        groupBox_form->setGeometry(QRect(170, 10, 421, 481));
        groupBox_form->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"background-color: rgb(110, 200, 248);\n"
"border: 2px solid black;\n"
"border-radius: 8px;\n"
"margin-top: 20px;\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 14px;\n"
"}\n"
"QGroupBox::title {\n"
"border: 2px solid black;\n"
"border-radius: 8px;\n"
"background-color: rgb(110, 200, 248);\n"
"subcontrol-origin: margin;\n"
"subcontrol-position: top center;\n"
"padding: 2px 10px;\n"
"}"));
        label_idActivite = new QLabel(groupBox_form);
        label_idActivite->setObjectName("label_idActivite");
        label_idActivite->setGeometry(QRect(20, 50, 150, 30));
        lineEdit_idActivite = new QLineEdit(groupBox_form);
        lineEdit_idActivite->setObjectName("lineEdit_idActivite");
        lineEdit_idActivite->setGeometry(QRect(220, 50, 180, 30));
        label_nom = new QLabel(groupBox_form);
        label_nom->setObjectName("label_nom");
        label_nom->setGeometry(QRect(20, 110, 150, 30));
        txtname = new QLineEdit(groupBox_form);
        txtname->setObjectName("txtname");
        txtname->setGeometry(QRect(220, 110, 180, 30));
        label_description = new QLabel(groupBox_form);
        label_description->setObjectName("label_description");
        label_description->setGeometry(QRect(20, 180, 150, 30));
        label_duree = new QLabel(groupBox_form);
        label_duree->setObjectName("label_duree");
        label_duree->setGeometry(QRect(20, 250, 150, 30));
        lineEdit_duree = new QLineEdit(groupBox_form);
        lineEdit_duree->setObjectName("lineEdit_duree");
        lineEdit_duree->setGeometry(QRect(220, 240, 181, 41));
        label_lieu = new QLabel(groupBox_form);
        label_lieu->setObjectName("label_lieu");
        label_lieu->setGeometry(QRect(20, 320, 150, 30));
        pushButton_ajouter = new QPushButton(groupBox_form);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(20, 380, 140, 40));
        pushButton_modifier = new QPushButton(groupBox_form);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(250, 380, 140, 40));
        pushButton_supprimer = new QPushButton(groupBox_form);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(20, 430, 140, 40));
        pushButton_actualiser = new QPushButton(groupBox_form);
        pushButton_actualiser->setObjectName("pushButton_actualiser");
        pushButton_actualiser->setGeometry(QRect(250, 430, 140, 40));
        comboBox = new QComboBox(groupBox_form);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(220, 170, 181, 41));
        comboBox_2 = new QComboBox(groupBox_form);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(220, 320, 181, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1582, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion - Application", nullptr));
        groupBox_menu->setTitle(QCoreApplication::translate("MainWindow", "MENU", nullptr));
        pushButton_abonne->setText(QCoreApplication::translate("MainWindow", "Abonn\303\251", nullptr));
        pushButton_employe->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
        pushButton_inscription_menu->setText(QCoreApplication::translate("MainWindow", "Inscription", nullptr));
        pushButton_activite->setText(QCoreApplication::translate("MainWindow", "Activit\303\251", nullptr));
        groupBox_form->setTitle(QCoreApplication::translate("MainWindow", "Gestion des mat\303\251riels", nullptr));
        label_idActivite->setText(QCoreApplication::translate("MainWindow", "ID mat\303\251riel", nullptr));
        label_nom->setText(QCoreApplication::translate("MainWindow", "Nom du mat\303\251riel", nullptr));
        label_description->setText(QCoreApplication::translate("MainWindow", "cat\303\251gorie", nullptr));
        label_duree->setText(QCoreApplication::translate("MainWindow", "quantit\303\251 totale", nullptr));
        label_lieu->setText(QCoreApplication::translate("MainWindow", "\303\251tat du mat\303\251riel", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_actualiser->setText(QCoreApplication::translate("MainWindow", "Actualiser", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "veuillez choisir la cat\303\251gorie du mat\303\251riels ", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "restauration ", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "sport", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "piscine", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "travaux", nullptr));
        comboBox->setItemText(5, QString());
        comboBox->setItemText(6, QString());
        comboBox->setItemText(7, QString());

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "neuf", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "bon", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "moyen", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "endomag\303\251", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
