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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_8;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_11;
    QLabel *label_10;
    QTabWidget *statistiquz;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLineEdit *lineEdit_nom;
    QLabel *label_3;
    QLineEdit *lineEdit_prenom;
    QLabel *label_4;
    QDateEdit *dateEdit_naissance;
    QLabel *label_5;
    QLineEdit *lineEdit_adresse;
    QLabel *label_6;
    QLineEdit *lineEdit_tel;
    QLabel *label_7;
    QLineEdit *lineEdit_mail;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_ajouter;
    QTableWidget *tableWidget;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QPushButton *pushButton_supprimer;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_idSuppr;
    QComboBox *comboBox;
    QLineEdit *lineEdit_7;
    QLabel *image;
    QPushButton *pushButton_modifier;
    QWidget *tab_2;
    QLabel *label_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 640);
        QFont font;
        font.setPointSize(8);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(510, 60, 37, 12));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(30, 20, 141, 541));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"        background-color: rgb(255, 255, 255);\n"
"    background-color: rgb(0, 0, 128);   /* blue background */\n"
"    border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;                    /* rounded corners */\n"
"    margin-top: 20px;                      /* space for the title */\n"
"    color: white;                          /* title text color */\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}"));
        pushButton_12 = new QPushButton(groupBox_2);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(0, 70, 141, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Source Code Pro Medium")});
        font1.setBold(true);
        pushButton_12->setFont(font1);
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: orange;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        pushButton_13 = new QPushButton(groupBox_2);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(0, 260, 141, 41));
        pushButton_13->setFont(font1);
        pushButton_13->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: orange;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        pushButton_14 = new QPushButton(groupBox_2);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(0, 360, 141, 41));
        pushButton_14->setFont(font1);
        pushButton_14->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: orange;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        pushButton_15 = new QPushButton(groupBox_2);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(0, 450, 141, 41));
        pushButton_15->setFont(font1);
        pushButton_15->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: orange;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(0, 160, 141, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("System")});
        font2.setBold(true);
        pushButton_11->setFont(font2);
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: orange;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(180, 30, 37, 12));
        statistiquz = new QTabWidget(centralwidget);
        statistiquz->setObjectName("statistiquz");
        statistiquz->setGeometry(QRect(180, 10, 1071, 591));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 421, 521));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgb(110, 200, 248);   /* blue background */\n"
"    border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;                    /* rounded corners */\n"
"    margin-top: 20px;                      /* space for the title */\n"
"    color: white;                          /* title text color */\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
" border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;\n"
"background-color: rgb(110, 200, 248);\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;       /* title centered */\n"
"    padding: 2px 10px;\n"
"}"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 160, 71, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Source Code Pro Medium")});
        font3.setPointSize(16);
        label_2->setFont(font3);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_nom = new QLineEdit(groupBox);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(230, 150, 181, 41));
        lineEdit_nom->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}\n"
""));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 210, 81, 21));
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_prenom = new QLineEdit(groupBox);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(230, 200, 181, 41));
        lineEdit_prenom->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}\n"
""));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 250, 191, 41));
        label_4->setFont(font3);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        dateEdit_naissance = new QDateEdit(groupBox);
        dateEdit_naissance->setObjectName("dateEdit_naissance");
        dateEdit_naissance->setGeometry(QRect(230, 250, 181, 41));
        dateEdit_naissance->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}\n"
"\n"
""));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 310, 91, 51));
        label_5->setFont(font3);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_adresse = new QLineEdit(groupBox);
        lineEdit_adresse->setObjectName("lineEdit_adresse");
        lineEdit_adresse->setGeometry(QRect(230, 310, 181, 41));
        lineEdit_adresse->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}\n"
""));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 380, 211, 41));
        label_6->setFont(font3);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_tel = new QLineEdit(groupBox);
        lineEdit_tel->setObjectName("lineEdit_tel");
        lineEdit_tel->setGeometry(QRect(230, 380, 181, 41));
        lineEdit_tel->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}\n"
""));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 430, 81, 31));
        label_7->setFont(font3);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_mail = new QLineEdit(groupBox);
        lineEdit_mail->setObjectName("lineEdit_mail");
        lineEdit_mail->setGeometry(QRect(230, 430, 181, 41));
        lineEdit_mail->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}\n"
""));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 530, 101, 31));
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;      /* fond noir */\n"
"    color: white;                 /* texte blanc */\n"
"    border: 2px solid white;      /* contour blanc */\n"
"    border-radius: 8px;           /* coins arrondis */\n"
"    padding: 8px 20px;            /* espace int\303\251rieur */\n"
"    font-size: 14px;              /* taille du texte */\n"
"    font-weight: bold;            /* texte en gras */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #333333;    /* gris fonc\303\251 au survol */\n"
"}\n"
""));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(320, 530, 101, 31));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;      /* fond noir */\n"
"    color: white;                 /* texte blanc */\n"
"    border: 2px solid white;      /* contour blanc */\n"
"    border-radius: 8px;           /* coins arrondis */\n"
"    padding: 8px 20px;            /* espace int\303\251rieur */\n"
"    font-size: 14px;              /* taille du texte */\n"
"    font-weight: bold;            /* texte en gras */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #333333;    /* gris fonc\303\251 au survol */\n"
"}\n"
""));
        pushButton_ajouter = new QPushButton(groupBox);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(30, 480, 111, 31));
        pushButton_ajouter->setFont(font1);
        pushButton_ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: orange;   /* noir normal */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}"));
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(430, 20, 601, 192));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: rgb(110, 200, 248);   /* blue background */\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    gridline-color: black;                 /* cell grid lines */\n"
"    color: white;\n"
"    selection-background-color: #10b981;\n"
"    selection-color: white;\n"
"    outline: 0;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    border: 1px solid black;               /* give each cell a border */\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: rgb(110, 200, 248);\n"
"    color: white;\n"
"    border: 1px solid black;              /* column header border */\n"
"    padding: 4px;\n"
"    font-weight: bold;\n"
"}"));
        pushButton_7 = new QPushButton(tab);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(430, 240, 171, 41));
        pushButton_7->setFont(font1);
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        pushButton_6 = new QPushButton(tab);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(430, 400, 171, 41));
        pushButton_6->setFont(font1);
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        pushButton_supprimer = new QPushButton(tab);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(430, 320, 171, 41));
        pushButton_supprimer->setFont(font1);
        pushButton_supprimer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(430, 280, 171, 41));
        pushButton_5->setFont(font1);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        lineEdit_idSuppr = new QLineEdit(tab);
        lineEdit_idSuppr->setObjectName("lineEdit_idSuppr");
        lineEdit_idSuppr->setGeometry(QRect(610, 320, 111, 31));
        lineEdit_idSuppr->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"        color: rgb(0, 0, 0);\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}\n"
"ui->lineEdit_8->setPlaceholderText(\"Identifiant\");"));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(610, 240, 111, 31));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}\n"
"\n"
"/* Style du menu d\303\251roulant */\n"
"QComboBox QAbstractItemView {\n"
"    background-color: white;     /* fond du menu */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour du menu */\n"
"    selection-background-color: black;  /* fond quand un item est s\303\251lectionn\303\251 */\n"
"    selection-color: white;      /* texte blanc sur s\303\251lection */\n"
"}"));
        lineEdit_7 = new QLineEdit(tab);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(610, 280, 111, 31));
        lineEdit_7->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: white;     /* fond blanc */\n"
"    color: black;                /* texte en noir */\n"
"    border: 2px solid black;     /* contour noir */\n"
"    border-radius: 8px;          /* coins arrondis */\n"
"    padding: 8px 20px;           /* espace int\303\251rieur */\n"
"    font-size: 14px;             /* taille du texte */\n"
"    font-weight: bold;           /* texte en gras */\n"
"}"));
        image = new QLabel(tab);
        image->setObjectName("image");
        image->setGeometry(QRect(610, 380, 151, 181));
        image->setPixmap(QPixmap(QString::fromUtf8("images/logo application.png")));
        pushButton_modifier = new QPushButton(tab);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(430, 360, 171, 41));
        pushButton_modifier->setFont(font1);
        pushButton_modifier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: black;   /* fond noir */\n"
"    color: white;              /* texte blanc */\n"
"    border: 2px solid white;   /* contour blanc */\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        statistiquz->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_9 = new QLabel(tab_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(280, 70, 37, 12));
        statistiquz->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        statistiquz->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_8->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "MENU", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Inscription", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "Activit\303\251", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Mat\303\251riel ", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Abonn\303\251", nullptr));
        label_10->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "ajouter un abonn\303\251", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        lineEdit_nom->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        lineEdit_prenom->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Date de naissance", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        lineEdit_adresse->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Num\303\251ro de t\303\251lephone", nullptr));
        lineEdit_tel->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        lineEdit_mail->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Date de naissance", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Trier par", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Exportation PDF", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        lineEdit_idSuppr->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        comboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "A--Z", nullptr));
        lineEdit_7->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        image->setText(QString());
        pushButton_modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        statistiquz->setTabText(statistiquz->indexOf(tab), QCoreApplication::translate("MainWindow", "abonn\303\251s", nullptr));
        label_9->setText(QString());
        statistiquz->setTabText(statistiquz->indexOf(tab_2), QCoreApplication::translate("MainWindow", "statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
