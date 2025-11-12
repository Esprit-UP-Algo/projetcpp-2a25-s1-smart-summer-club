#include "gestion-inscription.h"
#include "ui_gestion_inscription.h"

#include <QSqlQueryModel>
#include <QModelIndex>
#include <QVariant>
#include <QDate>

GestionInscriptions::GestionInscriptions(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GestionInscriptions)
{
    ui->setupUi(this);
    chargerTable();

    // Optionnel: config table
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

GestionInscriptions::~GestionInscriptions()
{
    delete ui;
}

void GestionInscriptions::chargerTable()
{
    QSqlQueryModel* model = inscription.afficher();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void GestionInscriptions::viderChamps()
{
    ui->lineEditIdInscription->clear();
    ui->lineEditIdAbonne->clear();
    ui->lineEditIdActivite->clear();
    ui->dateEditInscription->setDate(QDate::currentDate());
    ui->comboBoxStatut->setCurrentIndex(0);
    ui->checkBoxPaiement->setChecked(false);
    ui->lineEditPrix->clear();
}

void GestionInscriptions::on_btnAjouter_clicked()
{
    inscription.setIdInscription(ui->lineEditIdInscription->text().toInt());
    inscription.setIdAbonne(ui->lineEditIdAbonne->text().toInt());
    inscription.setIdActivite(ui->lineEditIdActivite->text().toInt());
    inscription.setDateInscription(ui->dateEditInscription->date().toString("yyyy-MM-dd"));
    inscription.setStatut(ui->comboBoxStatut->currentText());
    inscription.setPaiement(ui->checkBoxPaiement->isChecked());
    inscription.setPrix(ui->lineEditPrix->text().toDouble());

    if (!inscription.validerChamps()) {
        QMessageBox::warning(this, tr("Validation"), tr("Veuillez vérifier les champs saisis."));
        return;
    }

    if (inscription.ajouter()) {
        QMessageBox::information(this, tr("Succès"), tr("Inscription ajoutée avec succès."));
        chargerTable();
        viderChamps();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l'ajout de l'inscription."));
    }
}

void GestionInscriptions::on_btnModifier_clicked()
{
    inscription.setIdInscription(ui->lineEditIdInscription->text().toInt());
    inscription.setIdAbonne(ui->lineEditIdAbonne->text().toInt());
    inscription.setIdActivite(ui->lineEditIdActivite->text().toInt());
    inscription.setDateInscription(ui->dateEditInscription->date().toString("yyyy-MM-dd"));
    inscription.setStatut(ui->comboBoxStatut->currentText());
    inscription.setPaiement(ui->checkBoxPaiement->isChecked());
    inscription.setPrix(ui->lineEditPrix->text().toDouble());

    if (!inscription.validerChamps()) {
        QMessageBox::warning(this, tr("Validation"), tr("Veuillez vérifier les champs saisis."));
        return;
    }

    if (inscription.modifier()) {
        QMessageBox::information(this, tr("Succès"), tr("Inscription modifiée avec succès."));
        chargerTable();
        viderChamps();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }
}

void GestionInscriptions::on_btnSupprimer_clicked()
{
    int id = ui->lineEditIdInscription->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner une inscription valide."));
        return;
    }

    if (QMessageBox::question(this, tr("Confirmation"),
                              tr("Supprimer l'inscription %1 ?").arg(id)) != QMessageBox::Yes) {
        return;
    }

    if (inscription.supprimer(id)) {
        QMessageBox::information(this, tr("Succès"), tr("Inscription supprimée."));
        chargerTable();
        viderChamps();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
    }
}

void GestionInscriptions::on_btnRafraichir_clicked()
{
    chargerTable();
}

void GestionInscriptions::on_tableView_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    const QAbstractItemModel* model = ui->tableView->model();
    const int row = index.row();

    ui->lineEditIdInscription->setText(model->index(row, 0).data().toString());
    ui->lineEditIdAbonne->setText(model->index(row, 1).data().toString());
    ui->lineEditIdActivite->setText(model->index(row, 2).data().toString());

    const QString dateStr = model->index(row, 3).data().toString();
    ui->dateEditInscription->setDate(QDate::fromString(dateStr, "yyyy-MM-dd"));

    ui->comboBoxStatut->setCurrentText(model->index(row, 4).data().toString());
    ui->checkBoxPaiement->setChecked(model->index(row, 5).data().toBool());
    ui->lineEditPrix->setText(model->index(row, 6).data().toString());
}
