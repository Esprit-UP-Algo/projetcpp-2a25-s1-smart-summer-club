#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->image->setPixmap(QPixmap("C:/Users/hp/Documents/abonne/images/logo.png"));
    ui->image->setScaledContents(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}



