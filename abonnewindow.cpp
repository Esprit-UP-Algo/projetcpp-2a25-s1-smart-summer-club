#include "abonnewindow.h"
#include "ui_abonnewindow.h"
#include <QMessageBox>
#include <QDate>

AbonneWindow::AbonneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AbonneWindow)
{
    ui->setupUi(this);
    afficherAbonnes();
}

AbonneWindow::~AbonneWindow()
{
    delete ui;
}

void AbonneWindow::afficherAbonnes()
{
    Abonne a;
    ui->tableWidget->setModel(a.afficher());

    // Connect selection signal after setting model
    if (ui->tableWidget->model()) {
        connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &AbonneWindow::selectionChanged);
    }
}

void AbonneWindow::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    if(selected.indexes().isEmpty())
        return;

    int row = selected.indexes().first().row();

    ui->lineEdit_nom->setText(ui->tableWidget->model()->index(row, 1).data().toString());
    ui->lineEdit_prenom->setText(ui->tableWidget->model()->index(row, 2).data().toString());
    ui->dateEdit_naissance->setDate(QDate::fromString(ui->tableWidget->model()->index(row, 3).data().toString(), "yyyy-MM-dd"));
    ui->lineEdit_adresse->setText(ui->tableWidget->model()->index(row, 4).data().toString());
    ui->lineEdit_tel->setText(ui->tableWidget->model()->index(row, 5).data().toString());
    ui->lineEdit_mail->setText(ui->tableWidget->model()->index(row, 6).data().toString());

    // Store the selected ID for modify/delete
    selectedId = ui->tableWidget->model()->index(row, 0).data().toInt();
}

void AbonneWindow::on_pushButton_ajouter_clicked()
{
    Abonne a(0,  // id will be auto-incremented in the database
             ui->lineEdit_nom->text(),
             ui->lineEdit_prenom->text(),
             ui->dateEdit_naissance->date(),
             ui->lineEdit_adresse->text(),
             ui->lineEdit_tel->text(),
             ui->lineEdit_mail->text());

    if(a.ajouter()) {
        QMessageBox::information(this, "Ajouter", "Abonné ajouté avec succès!");
        afficherAbonnes();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l'ajout!");
    }
}

void AbonneWindow::on_pushButton_modifier_clicked()
{
    if(selectedId == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un abonné dans la table!");
        return;
    }

    Abonne a(selectedId,
             ui->lineEdit_nom->text(),
             ui->lineEdit_prenom->text(),
             ui->dateEdit_naissance->date(),
             ui->lineEdit_adresse->text(),
             ui->lineEdit_tel->text(),
             ui->lineEdit_mail->text());

    if(a.modifier()) {
        QMessageBox::information(this, "Modifier", "Abonné modifié avec succès!");
        afficherAbonnes();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification!");
    }
}

void AbonneWindow::on_pushButton_supprimer_clicked()
{
    if(selectedId == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un abonné dans la table!");
        return;
    }

    Abonne a;
    if(a.supprimer(selectedId)) {
        QMessageBox::information(this, "Supprimer", "Abonné supprimé avec succès!");
        selectedId = 0; // reset selected ID
        afficherAbonnes();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression!");
    }
}
