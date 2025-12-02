/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmployeeWindow
{
public:
    QWidget *centralwidget;
    QTableView *tableView;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_prenom;
    QLineEdit *lineEdit_poste;
    QLineEdit *lineEdit_fonction;
    QLineEdit *lineEdit_genre;
    QLineEdit *lineEdit_mail;
    QLineEdit *lineEdit_tel;
    QDateEdit *dateEdit_naissance;
    QLineEdit *lineEdit_adresse;
    QLineEdit *lineEdit_salaire;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_modifier;
    QPushButton *pushButton_supprimer;
    QPushButton *pushButton_recherche;
    QLabel *label_recherche;
    QLineEdit *lineEdit_recherche;
    QPushButton *pushButton_tri;
    QComboBox *comboBox_tri;
    QPushButton *pushButton_statistique;
    QPushButton *pushButton_attestation;

    void setupUi(QMainWindow *EmployeeWindow)
    {
        if (EmployeeWindow->objectName().isEmpty())
            EmployeeWindow->setObjectName("EmployeeWindow");
        EmployeeWindow->resize(960, 600);
        EmployeeWindow->setStyleSheet(QString::fromUtf8("\n"
"    QWidget {\n"
"        background-color: #e8f1ff;\n"
"        font: 10pt \"Segoe UI\";\n"
"    }\n"
"    QLineEdit, QDateEdit {\n"
"        border: 2px solid #1f4e79;\n"
"        border-radius: 6px;\n"
"        padding: 4px;\n"
"        background: #ffffff;\n"
"    }\n"
"    QTableView {\n"
"        border: 2px solid #1f4e79;\n"
"        background: #ffffff;\n"
"        alternate-background-color: #f2f6ff;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #ff8c42;\n"
"        color: white;\n"
"        border-radius: 10px;\n"
"        padding: 6px;\n"
"        font-weight: bold;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #e6762e;\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #cc5f20;\n"
"    }\n"
"   "));
        centralwidget = new QWidget(EmployeeWindow);
        centralwidget->setObjectName("centralwidget");
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(20, 20, 920, 250));
        lineEdit_nom = new QLineEdit(centralwidget);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(100, 290, 200, 25));
        lineEdit_prenom = new QLineEdit(centralwidget);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(100, 330, 200, 25));
        lineEdit_poste = new QLineEdit(centralwidget);
        lineEdit_poste->setObjectName("lineEdit_poste");
        lineEdit_poste->setGeometry(QRect(400, 290, 200, 25));
        lineEdit_fonction = new QLineEdit(centralwidget);
        lineEdit_fonction->setObjectName("lineEdit_fonction");
        lineEdit_fonction->setGeometry(QRect(400, 330, 200, 25));
        lineEdit_genre = new QLineEdit(centralwidget);
        lineEdit_genre->setObjectName("lineEdit_genre");
        lineEdit_genre->setGeometry(QRect(100, 370, 200, 25));
        lineEdit_mail = new QLineEdit(centralwidget);
        lineEdit_mail->setObjectName("lineEdit_mail");
        lineEdit_mail->setGeometry(QRect(400, 370, 200, 25));
        lineEdit_tel = new QLineEdit(centralwidget);
        lineEdit_tel->setObjectName("lineEdit_tel");
        lineEdit_tel->setGeometry(QRect(100, 410, 200, 25));
        dateEdit_naissance = new QDateEdit(centralwidget);
        dateEdit_naissance->setObjectName("dateEdit_naissance");
        dateEdit_naissance->setGeometry(QRect(400, 410, 200, 25));
        lineEdit_adresse = new QLineEdit(centralwidget);
        lineEdit_adresse->setObjectName("lineEdit_adresse");
        lineEdit_adresse->setGeometry(QRect(100, 450, 200, 25));
        lineEdit_salaire = new QLineEdit(centralwidget);
        lineEdit_salaire->setObjectName("lineEdit_salaire");
        lineEdit_salaire->setGeometry(QRect(400, 450, 200, 25));
        pushButton_ajouter = new QPushButton(centralwidget);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(650, 290, 100, 30));
        pushButton_modifier = new QPushButton(centralwidget);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(650, 340, 100, 30));
        pushButton_supprimer = new QPushButton(centralwidget);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(650, 390, 100, 30));
        pushButton_recherche = new QPushButton(centralwidget);
        pushButton_recherche->setObjectName("pushButton_recherche");
        pushButton_recherche->setGeometry(QRect(100, 500, 100, 30));
        label_recherche = new QLabel(centralwidget);
        label_recherche->setObjectName("label_recherche");
        label_recherche->setGeometry(QRect(210, 500, 50, 25));
        lineEdit_recherche = new QLineEdit(centralwidget);
        lineEdit_recherche->setObjectName("lineEdit_recherche");
        lineEdit_recherche->setGeometry(QRect(270, 500, 200, 25));
        pushButton_tri = new QPushButton(centralwidget);
        pushButton_tri->setObjectName("pushButton_tri");
        pushButton_tri->setGeometry(QRect(480, 500, 100, 30));
        comboBox_tri = new QComboBox(centralwidget);
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->setObjectName("comboBox_tri");
        comboBox_tri->setGeometry(QRect(590, 500, 120, 25));
        pushButton_statistique = new QPushButton(centralwidget);
        pushButton_statistique->setObjectName("pushButton_statistique");
        pushButton_statistique->setGeometry(QRect(720, 500, 100, 30));
        pushButton_attestation = new QPushButton(centralwidget);
        pushButton_attestation->setObjectName("pushButton_attestation");
        pushButton_attestation->setGeometry(QRect(840, 500, 100, 30));
        EmployeeWindow->setCentralWidget(centralwidget);

        retranslateUi(EmployeeWindow);

        QMetaObject::connectSlotsByName(EmployeeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EmployeeWindow)
    {
        EmployeeWindow->setWindowTitle(QCoreApplication::translate("EmployeeWindow", "Gestion Employee", nullptr));
        lineEdit_nom->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Nom", nullptr));
        lineEdit_prenom->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Pr\303\251nom", nullptr));
        lineEdit_poste->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Poste", nullptr));
        lineEdit_fonction->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Fonction", nullptr));
        lineEdit_genre->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Genre", nullptr));
        lineEdit_mail->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Email", nullptr));
        lineEdit_tel->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "T\303\251l\303\251phone", nullptr));
        dateEdit_naissance->setDisplayFormat(QCoreApplication::translate("EmployeeWindow", "yyyy-MM-dd", nullptr));
        lineEdit_adresse->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Adresse", nullptr));
        lineEdit_salaire->setPlaceholderText(QCoreApplication::translate("EmployeeWindow", "Salaire", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("EmployeeWindow", "Ajouter", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("EmployeeWindow", "Modifier", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("EmployeeWindow", "Supprimer", nullptr));
        pushButton_recherche->setText(QCoreApplication::translate("EmployeeWindow", "Recherche", nullptr));
        label_recherche->setText(QCoreApplication::translate("EmployeeWindow", "ID", nullptr));
        pushButton_tri->setText(QCoreApplication::translate("EmployeeWindow", "Tri", nullptr));
        comboBox_tri->setItemText(0, QCoreApplication::translate("EmployeeWindow", "ID", nullptr));
        comboBox_tri->setItemText(1, QCoreApplication::translate("EmployeeWindow", "Nom", nullptr));
        comboBox_tri->setItemText(2, QCoreApplication::translate("EmployeeWindow", "Pr\303\251nom", nullptr));

        pushButton_statistique->setText(QCoreApplication::translate("EmployeeWindow", "Statistique", nullptr));
        pushButton_attestation->setText(QCoreApplication::translate("EmployeeWindow", "Attestation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmployeeWindow: public Ui_EmployeeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
