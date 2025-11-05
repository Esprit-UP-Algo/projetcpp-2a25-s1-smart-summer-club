#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connexion à la base
    if (Connection::createInstance()->createConnection()) {
        QMessageBox::information(this, "Connexion", "Connexion à la base réussie !");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la connexion à la base.");
    }

    // Charger les données initiales
    refreshTable();
}

MainWindow::~MainWindow() {
    delete ui;
}

// Rafraîchir l'affichage de la table
void MainWindow::refreshTable() {
    QSqlQueryModel *model = A.afficher();

    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount());
    ui->tableWidget->setHorizontalHeaderLabels(
        {"ID", "Nom", "Prénom", "Adresse", "Téléphone", "Email", "Date de naissance"}
        );

    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(model->data(model->index(i, j)).toString()));
        }
    }
}

// Ajouter un abonné
void MainWindow::on_pushButton_ajouter_clicked() {
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString adresse = ui->lineEdit_adresse->text();
    QString telephone = ui->lineEdit_tel->text();
    QString email = ui->lineEdit_mail->text();
    QString dateNaissance = ui->dateEdit_naissance->date().toString("yyyy-MM-dd");

    Abonne a(nom, prenom, adresse, telephone, email, dateNaissance);

    if (a.ajouter()) {
        QMessageBox::information(this, "Succès", "Abonné ajouté avec succès !");
        refreshTable();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ajouter l'abonné !");
    }
}

// Modifier un abonné (par sélection dans la table)
void MainWindow::on_pushButton_modifier_clicked() {
    int currentRow = ui->tableWidget->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un abonné à modifier.");
        return;
    }

    int id = ui->tableWidget->item(currentRow, 0)->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString adresse = ui->lineEdit_adresse->text();
    QString telephone = ui->lineEdit_tel->text();
    QString email = ui->lineEdit_mail->text();
    QString dateNaissance = ui->dateEdit_naissance->date().toString("yyyy-MM-dd");

    Abonne a(nom, prenom, adresse, telephone, email, dateNaissance);

    if (a.modifier(id)) {
        QMessageBox::information(this, "Succès", "Abonné modifié avec succès !");
        refreshTable();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier l'abonné !");
    }
}

// Supprimer un abonné (par sélection dans la table)
void MainWindow::on_pushButton_supprimer_clicked() {
    int id = -1;

    // ✅ Option 1: Try to read from text field
    QString idText = ui->lineEdit_idSuppr->text().trimmed();
    if (!idText.isEmpty()) {
        id = idText.toInt();
    } else {
        // ✅ Option 2: Get from selected row if no text entered
        int currentRow = ui->tableWidget->currentRow();
        if (currentRow >= 0) {
            id = ui->tableWidget->item(currentRow, 0)->text().toInt();
        }
    }

    if (id == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir ou sélectionner un ID à supprimer.");
        return;
    }

    if (A.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Abonné supprimé !");
        refreshTable();
        ui->lineEdit_idSuppr->clear(); // 🔄 reset field
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de suppression !");
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    Q_UNUSED(column); // we don’t need this parameter

    ui->lineEdit_nom->setText(ui->tableWidget->item(row, 1)->text());
    ui->lineEdit_prenom->setText(ui->tableWidget->item(row, 2)->text());
    ui->lineEdit_adresse->setText(ui->tableWidget->item(row, 3)->text());
    ui->lineEdit_tel->setText(ui->tableWidget->item(row, 4)->text());
    ui->lineEdit_mail->setText(ui->tableWidget->item(row, 5)->text());
    ui->dateEdit_naissance->setDate(QDate::fromString(ui->tableWidget->item(row, 6)->text(), "yyyy-MM-dd"));
}
