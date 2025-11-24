/********************************************************************************
** Form generated from reading UI file 'abonnewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABONNEWINDOW_H
#define UI_ABONNEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AbonneWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QLabel *labelTitle;
    QHBoxLayout *hboxLayout;
    QLineEdit *lineEdit_search;
    QPushButton *pushButton_search;
    QTableView *tableWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_nom;
    QLineEdit *lineEdit_nom;
    QLabel *label_prenom;
    QLineEdit *lineEdit_prenom;
    QLabel *label_adresse;
    QLineEdit *lineEdit_adresse;
    QLabel *label_tel;
    QLineEdit *lineEdit_tel;
    QLabel *label_mail;
    QLineEdit *lineEdit_mail;
    QLabel *label_naissance;
    QDateEdit *dateEdit_naissance;
    QHBoxLayout *hboxLayout1;
    QLabel *label_trier;
    QLineEdit *lineEdit_trier;
    QPushButton *pushButton_trier;
    QHBoxLayout *hboxLayout2;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_modifier;
    QPushButton *pushButton_supprimer;
    QPushButton *pushButton_export_pdf;
    QPushButton *pushButton_statistique;
    QPushButton *pushButton_historique;

    void setupUi(QMainWindow *AbonneWindow)
    {
        if (AbonneWindow->objectName().isEmpty())
            AbonneWindow->setObjectName("AbonneWindow");
        AbonneWindow->resize(900, 600);
        AbonneWindow->setStyleSheet(QString::fromUtf8("\n"
"    QMainWindow {\n"
"        background-color: #E3F2FD;      /* bleu ciel tr\303\250s clair */\n"
"    }\n"
"\n"
"    QLabel#labelTitle {\n"
"        color: #0D47A1;                 /* bleu plus fonc\303\251 pour le titre */\n"
"        font-size: 26px;\n"
"        font-weight: bold;\n"
"    }\n"
"\n"
"    QLabel {\n"
"        color: #0D47A1;\n"
"        font-weight: 500;\n"
"    }\n"
"\n"
"    /* Champs de saisie */\n"
"    QLineEdit {\n"
"        background-color: #FFFFFF;\n"
"        color: #000000;\n"
"        border: 1px solid #90CAF9;      /* bleu ciel */\n"
"        border-radius: 6px;\n"
"        padding: 4px 8px;\n"
"    }\n"
"    QLineEdit:focus {\n"
"        border: 1px solid #FF8C32;      /* orange */\n"
"    }\n"
"\n"
"    QDateEdit {\n"
"        background-color: #FFFFFF;\n"
"        color: #000000;\n"
"        border: 1px solid #90CAF9;\n"
"        border-radius: 6px;\n"
"        padding: 2px 6px;\n"
"    }\n"
"    QDateEdit::down-arrow {\n"
"        image: none;\n"
"    }\n"
"\n"
"    /* "
                        "Table d'affichage */\n"
"    QTableView#tableWidget {\n"
"        background-color: #FFFFFF;\n"
"        color: #000000;\n"
"        gridline-color: #90CAF9;\n"
"        selection-background-color: #FFB74D;   /* orange clair s\303\251lection */\n"
"        selection-color: #000000;\n"
"        border: 1px solid #90CAF9;\n"
"        alternate-background-color: #E3F2FD;\n"
"    }\n"
"\n"
"    /* En-t\303\252tes de la table */\n"
"    QHeaderView::section {\n"
"        background-color: #BBDEFB;\n"
"        color: #0D47A1;\n"
"        padding: 4px;\n"
"        border: none;\n"
"        border-right: 1px solid #90CAF9;\n"
"    }\n"
"\n"
"    /* Boutons \342\200\223 tous orange, m\303\252me supprimer + trier + exportation */\n"
"    QPushButton {\n"
"        background-color: #FF8C32;      /* orange */\n"
"        color: #000000;\n"
"        border: none;\n"
"        border-radius: 8px;\n"
"        padding: 8px 16px;\n"
"        font-weight: bold;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: "
                        "#FFA857;\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #CC6F25;\n"
"    }\n"
"\n"
"    /* Ligne de recherche */\n"
"    QLineEdit#lineEdit_search {\n"
"        background-color: #FFFFFF;\n"
"        border-radius: 12px;\n"
"        padding-left: 10px;\n"
"    }\n"
"\n"
"    /* GroupBox infos abonn\303\251 */\n"
"    QGroupBox {\n"
"        color: #0D47A1;\n"
"        border: 1px solid #90CAF9;\n"
"        border-radius: 8px;\n"
"        margin-top: 8px;\n"
"        background-color: #EAF4FF;\n"
"    }\n"
"    QGroupBox::title {\n"
"        subcontrol-origin: margin;\n"
"        left: 10px;\n"
"        padding: 0 4px;\n"
"    }\n"
"   "));
        centralwidget = new QWidget(AbonneWindow);
        centralwidget->setObjectName("centralwidget");
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName("vboxLayout");
        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        vboxLayout->addWidget(labelTitle);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(10);
        hboxLayout->setObjectName("hboxLayout");
        lineEdit_search = new QLineEdit(centralwidget);
        lineEdit_search->setObjectName("lineEdit_search");
        lineEdit_search->setMinimumHeight(32);

        hboxLayout->addWidget(lineEdit_search);

        pushButton_search = new QPushButton(centralwidget);
        pushButton_search->setObjectName("pushButton_search");
        pushButton_search->setMinimumHeight(32);

        hboxLayout->addWidget(pushButton_search);


        vboxLayout->addLayout(hboxLayout);

        tableWidget = new QTableView(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        vboxLayout->addWidget(tableWidget);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label_nom = new QLabel(groupBox);
        label_nom->setObjectName("label_nom");

        gridLayout->addWidget(label_nom, 0, 0, 1, 1);

        lineEdit_nom = new QLineEdit(groupBox);
        lineEdit_nom->setObjectName("lineEdit_nom");

        gridLayout->addWidget(lineEdit_nom, 0, 1, 1, 1);

        label_prenom = new QLabel(groupBox);
        label_prenom->setObjectName("label_prenom");

        gridLayout->addWidget(label_prenom, 1, 0, 1, 1);

        lineEdit_prenom = new QLineEdit(groupBox);
        lineEdit_prenom->setObjectName("lineEdit_prenom");

        gridLayout->addWidget(lineEdit_prenom, 1, 1, 1, 1);

        label_adresse = new QLabel(groupBox);
        label_adresse->setObjectName("label_adresse");

        gridLayout->addWidget(label_adresse, 2, 0, 1, 1);

        lineEdit_adresse = new QLineEdit(groupBox);
        lineEdit_adresse->setObjectName("lineEdit_adresse");

        gridLayout->addWidget(lineEdit_adresse, 2, 1, 1, 1);

        label_tel = new QLabel(groupBox);
        label_tel->setObjectName("label_tel");

        gridLayout->addWidget(label_tel, 3, 0, 1, 1);

        lineEdit_tel = new QLineEdit(groupBox);
        lineEdit_tel->setObjectName("lineEdit_tel");

        gridLayout->addWidget(lineEdit_tel, 3, 1, 1, 1);

        label_mail = new QLabel(groupBox);
        label_mail->setObjectName("label_mail");

        gridLayout->addWidget(label_mail, 4, 0, 1, 1);

        lineEdit_mail = new QLineEdit(groupBox);
        lineEdit_mail->setObjectName("lineEdit_mail");

        gridLayout->addWidget(lineEdit_mail, 4, 1, 1, 1);

        label_naissance = new QLabel(groupBox);
        label_naissance->setObjectName("label_naissance");

        gridLayout->addWidget(label_naissance, 5, 0, 1, 1);

        dateEdit_naissance = new QDateEdit(groupBox);
        dateEdit_naissance->setObjectName("dateEdit_naissance");

        gridLayout->addWidget(dateEdit_naissance, 5, 1, 1, 1);


        vboxLayout->addWidget(groupBox);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(10);
        hboxLayout1->setObjectName("hboxLayout1");
        label_trier = new QLabel(centralwidget);
        label_trier->setObjectName("label_trier");

        hboxLayout1->addWidget(label_trier);

        lineEdit_trier = new QLineEdit(centralwidget);
        lineEdit_trier->setObjectName("lineEdit_trier");

        hboxLayout1->addWidget(lineEdit_trier);

        pushButton_trier = new QPushButton(centralwidget);
        pushButton_trier->setObjectName("pushButton_trier");

        hboxLayout1->addWidget(pushButton_trier);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(20);
        hboxLayout2->setObjectName("hboxLayout2");
        hboxLayout2->setAlignment(Qt::AlignHCenter);
        pushButton_ajouter = new QPushButton(centralwidget);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setMinimumWidth(120);

        hboxLayout2->addWidget(pushButton_ajouter);

        pushButton_modifier = new QPushButton(centralwidget);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setMinimumWidth(120);

        hboxLayout2->addWidget(pushButton_modifier);

        pushButton_supprimer = new QPushButton(centralwidget);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setMinimumWidth(120);

        hboxLayout2->addWidget(pushButton_supprimer);

        pushButton_export_pdf = new QPushButton(centralwidget);
        pushButton_export_pdf->setObjectName("pushButton_export_pdf");
        pushButton_export_pdf->setMinimumWidth(150);

        hboxLayout2->addWidget(pushButton_export_pdf);

        pushButton_statistique = new QPushButton(centralwidget);
        pushButton_statistique->setObjectName("pushButton_statistique");
        pushButton_statistique->setMinimumWidth(150);

        hboxLayout2->addWidget(pushButton_statistique);

        pushButton_historique = new QPushButton(centralwidget);
        pushButton_historique->setObjectName("pushButton_historique");
        pushButton_historique->setMinimumWidth(150);

        hboxLayout2->addWidget(pushButton_historique);


        vboxLayout->addLayout(hboxLayout2);

        AbonneWindow->setCentralWidget(centralwidget);

        retranslateUi(AbonneWindow);

        QMetaObject::connectSlotsByName(AbonneWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AbonneWindow)
    {
        AbonneWindow->setWindowTitle(QCoreApplication::translate("AbonneWindow", "Gestion des Abonn\303\251s", nullptr));
        labelTitle->setText(QCoreApplication::translate("AbonneWindow", "Gestion des Abonn\303\251s", nullptr));
        lineEdit_search->setPlaceholderText(QCoreApplication::translate("AbonneWindow", "Entrez l'ID pour rechercher ou supprimer", nullptr));
        pushButton_search->setText(QCoreApplication::translate("AbonneWindow", "Rechercher", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AbonneWindow", "Informations Abonn\303\251", nullptr));
        label_nom->setText(QCoreApplication::translate("AbonneWindow", "Nom :", nullptr));
        lineEdit_nom->setPlaceholderText(QCoreApplication::translate("AbonneWindow", "Nom", nullptr));
        label_prenom->setText(QCoreApplication::translate("AbonneWindow", "Pr\303\251nom :", nullptr));
        lineEdit_prenom->setPlaceholderText(QCoreApplication::translate("AbonneWindow", "Pr\303\251nom", nullptr));
        label_adresse->setText(QCoreApplication::translate("AbonneWindow", "Adresse :", nullptr));
        lineEdit_adresse->setPlaceholderText(QCoreApplication::translate("AbonneWindow", "Adresse", nullptr));
        label_tel->setText(QCoreApplication::translate("AbonneWindow", "T\303\251l\303\251phone :", nullptr));
        lineEdit_tel->setPlaceholderText(QCoreApplication::translate("AbonneWindow", "T\303\251l\303\251phone", nullptr));
        label_mail->setText(QCoreApplication::translate("AbonneWindow", "Email :", nullptr));
        lineEdit_mail->setPlaceholderText(QCoreApplication::translate("AbonneWindow", "Email", nullptr));
        label_naissance->setText(QCoreApplication::translate("AbonneWindow", "Date de naissance :", nullptr));
        dateEdit_naissance->setDisplayFormat(QCoreApplication::translate("AbonneWindow", "dd/MM/yyyy", nullptr));
        label_trier->setText(QCoreApplication::translate("AbonneWindow", "Trier par :", nullptr));
        lineEdit_trier->setPlaceholderText(QCoreApplication::translate("AbonneWindow", "Ex : nom, prenom, adresse...", nullptr));
        pushButton_trier->setText(QCoreApplication::translate("AbonneWindow", "Trier", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("AbonneWindow", "Ajouter", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("AbonneWindow", "Modifier", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("AbonneWindow", "Supprimer", nullptr));
        pushButton_export_pdf->setText(QCoreApplication::translate("AbonneWindow", "Exportation PDF", nullptr));
        pushButton_statistique->setText(QCoreApplication::translate("AbonneWindow", "Statistique", nullptr));
        pushButton_historique->setText(QCoreApplication::translate("AbonneWindow", "Historique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AbonneWindow: public Ui_AbonneWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABONNEWINDOW_H
