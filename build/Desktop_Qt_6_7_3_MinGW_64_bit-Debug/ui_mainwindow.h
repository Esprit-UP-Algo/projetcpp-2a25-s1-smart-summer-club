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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *widget;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit;
    QGroupBox *groupBox_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton_7;
    QPushButton *pushButton_11;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QPushButton *pushButton_12;
    QComboBox *comboBox_2;
    QLineEdit *lineEdit_9;
    QLabel *label_2;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_6;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_13;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1333, 675);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 10, 231, 561));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"\n"
"background-color: rgb(255, 255, 255);\n"
"\n"
"background-color: rgb(0, 0, 128); /* blue background */\n"
"\n"
"border: 2px solid black; /* black border, 2px wide */\n"
"\n"
"border-radius: 8px; /* rounded corners */\n"
"\n"
"margin-top: 20px; /* space for the title */\n"
"\n"
"color: white; /* title text color */\n"
"\n"
"font-weight: bold;\n"
"\n"
"font-size: 14px;\n"
"\n"
"}"));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(60, 190, 130, 225));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));

        verticalLayout_2->addWidget(pushButton_3);

        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 60, 161, 111));
        widget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(\"C:/Users/Lenvovo LOQ/Downloads/logo.jpg\");\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"    background-color: transparent;\n"
"}\n"
""));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(60, 430, 128, 39));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(60, 490, 128, 39));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(510, 20, 481, 51));
        lineEdit->setStyleSheet(QString::fromUtf8("font: 900 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 170, 0);"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(240, 80, 1061, 371));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 11)
            tableWidget->setColumnCount(11);
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
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(250, 40, 751, 192));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"\n"
"background-color: rgb(110, 200, 248); /* blue background */\n"
"\n"
"border: 2px solid black;\n"
"\n"
"border-radius: 8px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"font-size: 14px;\n"
"\n"
"gridline-color: black; /* cell grid lines */\n"
"\n"
"color: white;\n"
"\n"
"selection-background-color: #10b981;\n"
"\n"
"selection-color: white;\n"
"\n"
"outline: 0;\n"
"\n"
"}\n"
"\n"
"\n"
"QTableWidget::item {\n"
"\n"
"border: 1px solid black; /* give each cell a border */\n"
"\n"
"padding: 4px;\n"
"\n"
"}\n"
"\n"
"\n"
"QHeaderView::section {\n"
"\n"
"background-color: rgb(110, 200, 248);\n"
"\n"
"color: white;\n"
"\n"
"border: 1px solid black; /* column header border */\n"
"\n"
"padding: 4px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));
        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(250, 330, 121, 31));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));
        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(250, 250, 121, 31));
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));
        layoutWidget_2 = new QWidget(groupBox_2);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(40, 40, 194, 259));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(layoutWidget_2);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(layoutWidget_2);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout->addWidget(lineEdit_3);

        lineEdit_4 = new QLineEdit(layoutWidget_2);
        lineEdit_4->setObjectName("lineEdit_4");

        verticalLayout->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(layoutWidget_2);
        lineEdit_5->setObjectName("lineEdit_5");

        verticalLayout->addWidget(lineEdit_5);

        lineEdit_6 = new QLineEdit(layoutWidget_2);
        lineEdit_6->setObjectName("lineEdit_6");

        verticalLayout->addWidget(lineEdit_6);

        lineEdit_7 = new QLineEdit(layoutWidget_2);
        lineEdit_7->setObjectName("lineEdit_7");

        verticalLayout->addWidget(lineEdit_7);

        lineEdit_8 = new QLineEdit(layoutWidget_2);
        lineEdit_8->setObjectName("lineEdit_8");

        verticalLayout->addWidget(lineEdit_8);

        pushButton_12 = new QPushButton(groupBox_2);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(250, 290, 121, 29));
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));
        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(390, 290, 76, 26));
        lineEdit_9 = new QLineEdit(groupBox_2);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(410, 250, 113, 26));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(380, 250, 63, 20));
        layoutWidget_3 = new QWidget(groupBox_2);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(630, 240, 108, 133));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_ajouter = new QPushButton(layoutWidget_3);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));

        verticalLayout_3->addWidget(pushButton_ajouter);

        pushButton_6 = new QPushButton(layoutWidget_3);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));

        verticalLayout_3->addWidget(pushButton_6);

        pushButton_10 = new QPushButton(layoutWidget_3);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));

        verticalLayout_3->addWidget(pushButton_10);

        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(890, 320, 121, 41));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"background-color: black; /* fond noir */\n"
"\n"
"color: white; /* texte blanc */\n"
"\n"
"border: 2px solid white; /* contour blanc */\n"
"\n"
"border-radius: 8px;\n"
"\n"
"padding: 8px 20px;\n"
"\n"
"font-size: 14px;\n"
"\n"
"font-weight: bold;\n"
"\n"
"}"));
        lineEdit_10 = new QLineEdit(groupBox_2);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(40, 310, 192, 26));
        lineEdit_11 = new QLineEdit(groupBox_2);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(40, 350, 192, 26));
        lineEdit_12 = new QLineEdit(centralWidget);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(280, 530, 192, 26));
        lineEdit_13 = new QLineEdit(centralWidget);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(280, 480, 192, 26));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1333, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "MENU", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "employ\303\251s", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Activit\303\251", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Abonn\303\251es", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "materiel", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "inscription", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "           Gestion Des Employ\303\251e - Summer Club", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Group Box", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "genre", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Date de naissance", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Supprimer ", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Recherche ", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "ID_employe", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("MainWindow", "poste", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "fonction", nullptr));
        lineEdit_7->setText(QCoreApplication::translate("MainWindow", "genre", nullptr));
        lineEdit_8->setText(QCoreApplication::translate("MainWindow", "email", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "TRI", nullptr));
        comboBox_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "A--Z", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter ", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Modifier ", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        lineEdit_10->setText(QCoreApplication::translate("MainWindow", "telephone", nullptr));
        lineEdit_11->setText(QCoreApplication::translate("MainWindow", "date_de_naissance", nullptr));
        lineEdit_12->setText(QCoreApplication::translate("MainWindow", "adresse", nullptr));
        lineEdit_13->setText(QCoreApplication::translate("MainWindow", "salaire", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
