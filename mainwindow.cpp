#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , abonneWindow(nullptr)
    , employeeWindow(nullptr)
{
    ui->setupUi(this);

    // Connect the buttons to slots
    connect(ui->pushButtonAbonne, &QPushButton::clicked, this, &MainWindow::openAbonneWindow);
    connect(ui->pushButtonEmployee, &QPushButton::clicked, this, &MainWindow::openEmployeeWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slots to open windows
void MainWindow::openAbonneWindow()
{
    if (!abonneWindow)
        abonneWindow = new AbonneWindow(this);
    abonneWindow->show();
}



void MainWindow::openEmployeeWindow()
{
    // 1. Show login dialog first
    Login loginDialog(this);
    if (loginDialog.exec() == QDialog::Accepted) {
        // Login successful, open EmployeeWindow
        if (!employeeWindow)
            employeeWindow = new EmployeeWindow(this);
        employeeWindow->show();
    } else {
        // Login failed or cancelled
        QMessageBox::warning(this, "Accès refusé", "Authentification requise !");
    }
}

