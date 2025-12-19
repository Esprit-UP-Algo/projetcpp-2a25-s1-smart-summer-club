#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ====== MODEL SQLITE ======
    model = new QSqlTableModel(this);
    model->setTable("materiel");
    model->select();
    ui->tableView->setModel(model);

    // ====== CONNEXIONS ======
    connect(ui->pushButton_ajouter,
            &QPushButton::clicked,
            this,
            &MainWindow::ajouterMateriel);

    connect(ui->pushButton_modifier,
            &QPushButton::clicked,
            this,
            &MainWindow::modifierMateriel);

    connect(ui->pushButton_supprimer,
            &QPushButton::clicked,
            this,
            &MainWindow::supprimerMateriel);

    connect(ui->pushButton_actualiser,
            &QPushButton::clicked,
            this,
            &MainWindow::actualiserMateriel);

    // Quand on clique sur une ligne → remplir les champs
    connect(ui->tableView,
            &QTableView::clicked,
            this,
            &MainWindow::remplirChamps);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//// ================= CRUD ===================

void MainWindow::ajouterMateriel()
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO materiel (nom, categorie, quantite, etat) "
        "VALUES (?, ?, ?, ?)");

    query.addBindValue(ui->lineEdit_nom->text());
    query.addBindValue(ui->comboBox_categorie->currentText());
    query.addBindValue(ui->lineEdit_quantite->text().toInt());
    query.addBindValue(ui->comboBox_etat->currentText());

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Ajout échoué");
        return;
    }

    model->select();
    clearFields();
}

void MainWindow::modifierMateriel()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) return;

    int id = model->data(model->index(index.row(), 0)).toInt();

    QSqlQuery query;
    query.prepare(
        "UPDATE materiel "
        "SET nom=?, categorie=?, quantite=?, etat=? "
        "WHERE id=?");

    query.addBindValue(ui->lineEdit_nom->text());
    query.addBindValue(ui->comboBox_categorie->currentText());
    query.addBindValue(ui->lineEdit_quantite->text().toInt());
    query.addBindValue(ui->comboBox_etat->currentText());
    query.addBindValue(id);

    query.exec();
    model->select();
}

void MainWindow::supprimerMateriel()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) return;

    model->removeRow(index.row());
    model->submitAll();
    model->select();
}

void MainWindow::actualiserMateriel()
{
    model->select();
}

//// ============ UTILITAIRES ============

void MainWindow::remplirChamps(const QModelIndex &index)
{
    int row = index.row();

    ui->lineEdit_nom->setText(model->data(model->index(row, 1)).toString());
    ui->comboBox_categorie->setCurrentText(
        model->data(model->index(row, 2)).toString());
    ui->lineEdit_quantite->setText(
        model->data(model->index(row, 3)).toString());
    ui->comboBox_etat->setCurrentText(
        model->data(model->index(row, 4)).toString());
}

void MainWindow::clearFields()
{
    ui->lineEdit_nom->clear();
    ui->lineEdit_quantite->clear();
}
