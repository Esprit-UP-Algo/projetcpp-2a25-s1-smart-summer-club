#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inscription.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QInputDialog>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , modelInscriptions(new QStandardItemModel(this))
    , modelAbonnes(new QStandardItemModel(this))
    , modelActivites(new QStandardItemModel(this))
    , currentInscriptionId(-1)
{
    ui->setupUi(this);

    // Initialiser la base de données
    if (!DatabaseManager::instance().initializeDatabase()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'initialiser la base de données");
        return;
    }

    initialiserUI();
    chargerDonnees();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialiserUI()
{
    // Configuration du modèle des inscriptions
    modelInscriptions->setHorizontalHeaderLabels({"ID", "Abonné", "Activité", "Date", "Statut", "Paiement", "Prix"});
    ui->tableInscriptions->setModel(modelInscriptions);
    ui->tableInscriptions->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Redimensionner les colonnes pour un meilleur affichage
    ui->tableInscriptions->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableInscriptions->setColumnWidth(0, 50);   // ID
    ui->tableInscriptions->setColumnWidth(1, 150);  // Abonné
    ui->tableInscriptions->setColumnWidth(2, 150);  // Activité
    ui->tableInscriptions->setColumnWidth(3, 100);  // Date
    ui->tableInscriptions->setColumnWidth(4, 100);  // Statut
    ui->tableInscriptions->setColumnWidth(5, 80);   // Paiement
    ui->tableInscriptions->setColumnWidth(6, 80);   // Prix

    // SUPPRIMER la partie chargement CSS puisque c'est intégré dans le .ui
    // Le CSS est maintenant directement dans le fichier .ui
}

void MainWindow::chargerDonnees()
{
    chargerInscriptions();
    chargerAbonnes();
    chargerActivites();
    mettreAJourStatistiques();
}

void MainWindow::chargerInscriptions()
{
    modelInscriptions->removeRows(0, modelInscriptions->rowCount());

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.exec("SELECT i.*, a.nom as nom_abonne, a.prenom as prenom_abonne, act.nom as nom_activite, act.prix as prix_activite "
               "FROM inscriptions i "
               "JOIN abonnes a ON i.id_abonne = a.id_abonne "
               "JOIN activites act ON i.id_activite = act.id_activite "
               "ORDER BY i.date_inscription DESC");

    while (query.next()) {
        QList<QStandardItem*> row;
        row << new QStandardItem(query.value("id_inscription").toString());

        // Nom complet de l'abonné
        QString nomComplet = query.value("prenom_abonne").toString() + " " + query.value("nom_abonne").toString();
        row << new QStandardItem(nomComplet);

        row << new QStandardItem(query.value("nom_activite").toString());
        row << new QStandardItem(query.value("date_inscription").toDate().toString("dd/MM/yyyy"));
        row << new QStandardItem(query.value("statut").toString());
        row << new QStandardItem(query.value("paiement_effectue").toBool() ? "Oui" : "Non");
        row << new QStandardItem(QString::number(query.value("prix").toDouble(), 'f', 2) + " €");

        // Colorier selon le statut
        QColor backgroundColor;
        if (query.value("statut").toString() == "confirmé") {
            backgroundColor = QColor("#d4edda"); // Vert clair
        } else if (query.value("statut").toString() == "annulée") {
            backgroundColor = QColor("#f8d7da"); // Rouge clair
        } else {
            backgroundColor = QColor("#fff3cd"); // Jaune clair pour en attente
        }

        for (auto item : row) {
            item->setBackground(backgroundColor);
            item->setTextAlignment(Qt::AlignCenter);
        }

        modelInscriptions->appendRow(row);
    }
}

void MainWindow::chargerAbonnes()
{
    modelAbonnes->clear();
    QSqlQuery query("SELECT id_abonne, nom, prenom FROM abonnes ORDER BY nom, prenom",
                    DatabaseManager::instance().getDatabase());

    while (query.next()) {
        QString nomComplet = query.value("prenom").toString() + " " + query.value("nom").toString();
        QStandardItem *item = new QStandardItem(nomComplet);
        item->setData(query.value("id_abonne").toInt(), Qt::UserRole); // Stocker l'ID
        modelAbonnes->appendRow(item);
    }
}

void MainWindow::chargerActivites()
{
    modelActivites->clear();
    QSqlQuery query("SELECT id_activite, nom, prix FROM activites ORDER BY nom",
                    DatabaseManager::instance().getDatabase());

    while (query.next()) {
        QString activiteInfo = query.value("nom").toString() + " (" + QString::number(query.value("prix").toDouble(), 'f', 2) + " €)";
        QStandardItem *item = new QStandardItem(activiteInfo);
        item->setData(query.value("id_activite").toInt(), Qt::UserRole); // Stocker l'ID
        modelActivites->appendRow(item);
    }
}

void MainWindow::mettreAJourStatistiques()
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());

    // Total inscriptions
    query.exec("SELECT COUNT(*) FROM inscriptions");
    if (query.next()) {
        ui->labelTotalInscriptions->setText(query.value(0).toString());
    }

    // Inscriptions confirmées
    query.exec("SELECT COUNT(*) FROM inscriptions WHERE statut = 'confirmé'");
    if (query.next()) {
        ui->labelConfirmes->setText(query.value(0).toString());
    }

    // En attente
    query.exec("SELECT COUNT(*) FROM inscriptions WHERE statut = 'en attente'");
    if (query.next()) {
        ui->labelEnAttente->setText(query.value(0).toString());
    }

    // Revenus totaux
    query.exec("SELECT SUM(prix) FROM inscriptions WHERE paiement_effectue = 1");
    if (query.next()) {
        double revenus = query.value(0).toDouble();
        ui->labelRevenus->setText(QString::number(revenus, 'f', 2) + " €");
    }
}

void MainWindow::on_tableInscriptions_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        currentInscriptionId = modelInscriptions->item(index.row(), 0)->text().toInt();

        // Surligner la ligne sélectionnée
        for (int col = 0; col < modelInscriptions->columnCount(); ++col) {
            QStandardItem *item = modelInscriptions->item(index.row(), col);
            if (item) {
                item->setBackground(QColor("#d6eaf8")); // Bleu clair pour la sélection
            }
        }
    }
}

void MainWindow::on_ajouterInscription_clicked()
{
    // Dialogue pour ajouter une inscription
    bool ok;

    // Sélection de l'abonné
    QStringList abonnesList;
    QMap<QString, int> abonnesMap; // Pour mapper le nom à l'ID

    for (int i = 0; i < modelAbonnes->rowCount(); ++i) {
        QString nomComplet = modelAbonnes->item(i)->text();
        int idAbonne = modelAbonnes->item(i)->data(Qt::UserRole).toInt();
        abonnesList << nomComplet;
        abonnesMap[nomComplet] = idAbonne;
    }

    QString abonneSelectionne = QInputDialog::getItem(this, "Nouvelle inscription",
                                                      "Sélectionnez l'abonné:", abonnesList, 0, false, &ok);
    if (!ok || abonneSelectionne.isEmpty()) return;

    // Sélection de l'activité
    QStringList activitesList;
    QMap<QString, QPair<int, double>> activitesMap; // Pour mapper à l'ID et prix

    for (int i = 0; i < modelActivites->rowCount(); ++i) {
        QString activiteInfo = modelActivites->item(i)->text();
        int idActivite = modelActivites->item(i)->data(Qt::UserRole).toInt();

        // Extraire le prix de la chaîne
        double prix = 0.0;
        int prixStart = activiteInfo.lastIndexOf("(");
        if (prixStart != -1) {
            QString prixStr = activiteInfo.mid(prixStart + 1).remove(" €)");
            prix = prixStr.toDouble();
        }

        activitesList << activiteInfo;
        activitesMap[activiteInfo] = qMakePair(idActivite, prix);
    }

    QString activiteSelectionnee = QInputDialog::getItem(this, "Nouvelle inscription",
                                                         "Sélectionnez l'activité:", activitesList, 0, false, &ok);
    if (!ok || activiteSelectionnee.isEmpty()) return;

    // Créer la nouvelle inscription
    Inscription nouvelleInscription;
    nouvelleInscription.setIdAbonne(abonnesMap[abonneSelectionne]);
    nouvelleInscription.setIdActivite(activitesMap[activiteSelectionnee].first);
    nouvelleInscription.setStatut("en attente");
    nouvelleInscription.setPaiementEffectue(false);
    nouvelleInscription.setPrix(activitesMap[activiteSelectionnee].second);

    if (nouvelleInscription.sauvegarder()) {
        QMessageBox::information(this, "Succès", "Inscription ajoutée avec succès");
        chargerInscriptions();
        mettreAJourStatistiques();
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'ajout de l'inscription");
    }
}

void MainWindow::on_modifierInscription_clicked()
{
    if (currentInscriptionId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner une inscription");
        return;
    }

    Inscription* inscription = Inscription::charger(currentInscriptionId);
    if (!inscription) {
        QMessageBox::warning(this, "Erreur", "Impossible de charger l'inscription");
        return;
    }

    // Dialogue de modification
    QStringList statuts = {"confirmé", "en attente", "annulée"};
    bool ok;
    QString nouveauStatut = QInputDialog::getItem(this, "Modifier inscription",
                                                  "Nouveau statut:", statuts,
                                                  statuts.indexOf(inscription->getStatut()),
                                                  false, &ok);

    if (ok) {
        inscription->setStatut(nouveauStatut);
        if (inscription->sauvegarder()) {
            QMessageBox::information(this, "Succès", "Inscription modifiée avec succès");
            chargerInscriptions();
            mettreAJourStatistiques();
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de la modification");
        }
    }

    delete inscription;
}

void MainWindow::on_supprimerInscription_clicked()
{
    if (currentInscriptionId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner une inscription");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cette inscription?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Inscription* inscription = Inscription::charger(currentInscriptionId);
        if (inscription && inscription->supprimer()) {
            QMessageBox::information(this, "Succès", "Inscription supprimée avec succès");
            currentInscriptionId = -1;
            chargerInscriptions();
            mettreAJourStatistiques();
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de la suppression");
        }
        delete inscription;
    }
}

void MainWindow::on_validerInscription_clicked()
{
    if (currentInscriptionId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner une inscription");
        return;
    }

    Inscription* inscription = Inscription::charger(currentInscriptionId);
    if (inscription) {
        inscription->setStatut("confirmé");
        if (inscription->sauvegarder()) {
            QMessageBox::information(this, "Succès", "Inscription confirmée");
            chargerInscriptions();
            mettreAJourStatistiques();
        }
        delete inscription;
    }
}

void MainWindow::on_marquerPaiement_clicked()
{
    if (currentInscriptionId == -1) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner une inscription");
        return;
    }

    Inscription* inscription = Inscription::charger(currentInscriptionId);
    if (inscription) {
        inscription->setPaiementEffectue(true);
        if (inscription->sauvegarder()) {
            QMessageBox::information(this, "Succès", "Paiement marqué comme effectué");
            chargerInscriptions();
            mettreAJourStatistiques();
        }
        delete inscription;
    }
}

void MainWindow::on_actualiserStatistiques_clicked()
{
    chargerDonnees();
    QMessageBox::information(this, "Actualisation", "Données mises à jour");
}
