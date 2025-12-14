#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inscriptiondao.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QTimer>  // For QTimer::singleShot

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Use DatabaseManager singleton for database connection
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    if (!dbManager.connect()) {
        QMessageBox::critical(this, "Error", "Failed to connect to database. The application will now exit.");
        QTimer::singleShot(0, this, &QApplication::quit);
        return;
    }
    
    setupConnections();
    loadInscriptions();
    updateButtonsState(false);
    updateLcdDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
   // In MainWindow::setupConnections()
   connect(ui->pushButton_abonne, &QPushButton::clicked, this, &MainWindow::onAbonneClicked);
   connect(ui->pushButton_employe, &QPushButton::clicked, this, &MainWindow::onEmployeClicked);
   connect(ui->pushButton_inscription_menu, &QPushButton::clicked, this, &MainWindow::onInscriptionClicked);
   connect(ui->pushButton_activite, &QPushButton::clicked, this, &MainWindow::onActiviteClicked);
   connect(ui->pushButton_activite_2, &QPushButton::clicked, this, &MainWindow::onMateriauxClicked);
   connect(ui->pushButton_actualiser, &QPushButton::clicked, this, &MainWindow::refreshInscriptions);
}

void MainWindow::loadInscriptions()
{
    // Your existing code for loading inscriptions
}

void MainWindow::updateLcdDisplay()
{
    // Remove Arduino check and update display
    int currentIndex = ui->tabWidget_main->currentIndex();
    QString title;
    
    switch (currentIndex) {
        case 0: title = "Tableau de bord"; break;
        case 1: title = "Gestion des abonnés"; break;
        case 2: title = "Gestion des employés"; break;
        // Add more cases as needed
        default: title = "Application"; break;
    }
    
    setWindowTitle(title);
}

void MainWindow::onAbonneClicked()
{
    ui->tabWidget_main->setCurrentIndex(1); // Update index as needed
}

void MainWindow::onEmployeClicked()
{
    ui->tabWidget_main->setCurrentIndex(2); // Update index as needed
}

void MainWindow::onInscriptionClicked()
{
    ui->tabWidget_main->setCurrentIndex(3); // Update index as needed
}

void MainWindow::onActiviteClicked()
{
    ui->tabWidget_main->setCurrentIndex(4); // Update index as needed
}

void MainWindow::onMateriauxClicked()
{
    ui->tabWidget_main->setCurrentIndex(5); // Update index as needed
}

void MainWindow::refreshInscriptions()
{
    loadInscriptions();
}

void MainWindow::clearForm()
{
    // Your existing code for clearing form
}

bool MainWindow::validateForm()
{
    // Your existing code for form validation
    return true;
}

// In mainwindow.cpp
void MainWindow::updateButtonsState(bool isEditing)
{
    ui->pushButton_modifier->setEnabled(isEditing);
    ui->pushButton_supprimer->setEnabled(isEditing);
    ui->pushButton_valider->setEnabled(isEditing);
}













