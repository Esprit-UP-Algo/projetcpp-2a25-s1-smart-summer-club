#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "abonne.h"
#include"dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    abonne a;
    a.setID(ui->lineEdit_ID->text());
    a.setNom(ui->lineEdit_Nom->text());
    a.setPrenom(ui->lineEdit_Prenom->text());
    a.setdatedenaissance(ui->lineEdit_datedenaissance->text());
    a.setAdresse(ui->lineEdit_Adresse->text());
    a.setNumerodetelephone(ui->lineEdit_Numerodetelephone->text());
    a.setEmail(ui->lineEdit_Email->text());

    Dialog d;
    d.setabonne(a);
    d.exec();

}

