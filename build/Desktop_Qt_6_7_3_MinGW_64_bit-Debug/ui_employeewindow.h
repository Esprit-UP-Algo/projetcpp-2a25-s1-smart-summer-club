/********************************************************************************
** Form generated from reading UI file 'employeewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEWINDOW_H
#define UI_EMPLOYEEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
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

    void setupUi(QMainWindow *EmployeeWindow)
    {
        if (EmployeeWindow->objectName().isEmpty())
            EmployeeWindow->setObjectName("EmployeeWindow");
        EmployeeWindow->resize(900, 600);
        centralwidget = new QWidget(EmployeeWindow);
        centralwidget->setObjectName("centralwidget");
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(20, 20, 860, 250));
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
    } // retranslateUi

};

namespace Ui {
    class EmployeeWindow: public Ui_EmployeeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEWINDOW_H
