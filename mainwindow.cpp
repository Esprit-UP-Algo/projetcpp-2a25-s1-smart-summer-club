#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Placeholder pour aider l'utilisateur
    ui->lineEdit_7->setPlaceholderText("H ou F");
    ui->lineEdit_8->setPlaceholderText("exemple@gmail.com");
    ui->lineEdit_10->setPlaceholderText("12345678");
    ui->lineEdit_11->setPlaceholderText("JJ/MM/AAAA");

    // Afficher les employés au démarrage
    afficherEmployes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== MÉTHODE D'AFFICHAGE ====================
void MainWindow::afficherEmployes()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SUMMER.EMPLOYE ORDER BY ID_EMPLOYE");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération des données:\n" + query.lastError().text());
        return;
    }

    ui->tableWidget->setColumnCount(11);
    QStringList headers;
    headers << "ID" << "Nom" << "Prénom" << "Poste" << "Fonction" << "Genre"
            << "Email" << "Téléphone" << "Date Naissance" << "Adresse" << "Salaire";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int rowCount = 0;
    while (query.next()) rowCount++;
    ui->tableWidget->setRowCount(rowCount);

    query.seek(-1);
    int row = 0;
    while (query.next()) {
        for (int col = 0; col < 11; ++col)
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        row++;
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    qDebug() << "✅ Affichage de" << rowCount << "employés";
}

// ==================== MÉTHODES DE VALIDATION ====================
bool MainWindow::validerGenre(const QString &genre)
{
    QString genreUpper = genre.trimmed().toUpper();
    if (genreUpper != "H" && genreUpper != "F") {
        QMessageBox::warning(this, "Genre invalide", "Le genre doit être 'H' (Homme) ou 'F' (Femme).");
        return false;
    }
    return true;
}

bool MainWindow::validerEmail(const QString &email)
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@(gmail|yahoo|outlook)\\.(fr|com)$", QRegularExpression::CaseInsensitiveOption);
    if (!regex.match(email.trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Email invalide", "L'email doit respecter le format nom@domaine.com ou .fr");
        return false;
    }
    return true;
}

bool MainWindow::validerTelephone(const QString &telephone)
{
    QRegularExpression regex("^[0-9]{8}$");
    if (!regex.match(telephone.trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Téléphone invalide", "Le numéro doit contenir exactement 8 chiffres.");
        return false;
    }
    return true;
}

bool MainWindow::validerDate(const QString &date)
{
    QRegularExpression regex("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/([0-9]{4})$");
    QRegularExpressionMatch match = regex.match(date.trimmed());
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Date invalide", "Format attendu : JJ/MM/AAAA");
        return false;
    }

    QStringList parts = date.split("/");
    int jour = parts[0].toInt();
    int mois = parts[1].toInt();
    int annee = parts[2].toInt();
    QDate qdate(annee, mois, jour);
    if (!qdate.isValid() || qdate > QDate::currentDate()) {
        QMessageBox::warning(this, "Date invalide", "Vérifiez la date de naissance.");
        return false;
    }

    return true;
}

// ==================== AJOUT D'UN EMPLOYE ====================
void MainWindow::on_pushButton_ajouter_clicked()
{
    QString id_str = ui->lineEdit_2->text().trimmed();
    QString nom = ui->lineEdit_3->text().trimmed();
    QString prenom = ui->lineEdit_4->text().trimmed();
    QString poste = ui->lineEdit_5->text().trimmed();
    QString fonction = ui->lineEdit_6->text().trimmed();
    QString genre = ui->lineEdit_7->text().trimmed();
    QString email = ui->lineEdit_8->text().trimmed();
    QString telephone = ui->lineEdit_10->text().trimmed();
    QString date_naissance = ui->lineEdit_11->text().trimmed();
    QString adresse = ui->lineEdit_12->text().trimmed();
    QString salaire_str = ui->lineEdit_13->text().trimmed();

    if (id_str.isEmpty() || nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "ID, nom et prénom sont obligatoires !");
        return;
    }

    bool ok;
    int id = id_str.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être un entier positif !");
        return;
    }

    if (!genre.isEmpty() && !validerGenre(genre)) return;
    if (!email.isEmpty() && !validerEmail(email)) return;
    if (!telephone.isEmpty() && !validerTelephone(telephone)) return;
    if (!date_naissance.isEmpty() && !validerDate(date_naissance)) return;

    float salaire = salaire_str.toFloat(&ok);
    if (!ok) salaire = 0.0;

    Employe e(id, nom, prenom, poste, fonction, genre.toUpper(), email, telephone, date_naissance, adresse, salaire);
    if (e.ajouter()) {
        QMessageBox::information(this, "Succès", "✅ Employé ajouté avec succès !");
        afficherEmployes();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec de l'ajout. L'ID existe peut-être déjà.");
    }
}

// ==================== SELECTION D'UNE LIGNE DU TABLEAU ====================
void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    QString id = ui->tableWidget->item(row, 0)->text();
    QString nom = ui->tableWidget->item(row, 1)->text();
    QString prenom = ui->tableWidget->item(row, 2)->text();
    QString poste = ui->tableWidget->item(row, 3)->text();
    QString fonction = ui->tableWidget->item(row, 4)->text();
    QString genre = ui->tableWidget->item(row, 5)->text();
    QString email = ui->tableWidget->item(row, 6)->text();
    QString telephone = ui->tableWidget->item(row, 7)->text();
    QString date_naissance = ui->tableWidget->item(row, 8)->text();
    QString adresse = ui->tableWidget->item(row, 9)->text();
    QString salaire = ui->tableWidget->item(row, 10)->text();

    ui->lineEdit_2->setText(id);
    ui->lineEdit_3->setText(nom);
    ui->lineEdit_4->setText(prenom);
    ui->lineEdit_5->setText(poste);
    ui->lineEdit_6->setText(fonction);
    ui->lineEdit_7->setText(genre);
    ui->lineEdit_8->setText(email);
    ui->lineEdit_10->setText(telephone);
    ui->lineEdit_11->setText(date_naissance);
    ui->lineEdit_12->setText(adresse);
    ui->lineEdit_13->setText(salaire);

    ui->lineEdit_2->setReadOnly(true); // éviter modification de l'ID

    qDebug() << "🟢 Employé sélectionné pour modification : ID =" << id;
}

// ==================== MODIFICATION D'UN EMPLOYE ====================
void MainWindow::on_pushButton_6_clicked()
{
    QString id_str = ui->lineEdit_2->text().trimmed();
    QString nom = ui->lineEdit_3->text().trimmed();
    QString prenom = ui->lineEdit_4->text().trimmed();
    QString poste = ui->lineEdit_5->text().trimmed();
    QString fonction = ui->lineEdit_6->text().trimmed();
    QString genre = ui->lineEdit_7->text().trimmed();
    QString email = ui->lineEdit_8->text().trimmed();
    QString telephone = ui->lineEdit_10->text().trimmed();
    QString date_naissance = ui->lineEdit_11->text().trimmed();
    QString adresse = ui->lineEdit_12->text().trimmed();
    QString salaire_str = ui->lineEdit_13->text().trimmed();

    if (id_str.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé à modifier !");
        return;
    }

    bool ok;
    int id = id_str.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    float salaire = salaire_str.toFloat(&ok);
    if (!ok) salaire = 0.0;

    if (!genre.isEmpty() && !validerGenre(genre)) return;
    if (!email.isEmpty() && !validerEmail(email)) return;
    if (!telephone.isEmpty() && !validerTelephone(telephone)) return;
    if (!date_naissance.isEmpty() && !validerDate(date_naissance)) return;

    Employe e;
    e.setIdEmploye(id);
    e.setNom(nom);
    e.setPrenom(prenom);
    e.setPoste(poste);
    e.setFonction(fonction);
    e.setGenre(genre.toUpper());
    e.setEmail(email);
    e.setTelephone(telephone);
    e.setDateNaissance(date_naissance);
    e.setAdresse(adresse);
    e.setSalaire(salaire);

    bool test = e.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "✅ Employé modifié avec succès !");
        afficherEmployes();
        ui->lineEdit_2->setReadOnly(false);
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec de la modification de l'employé.");
    }
}

// ==================== SUPPRESSION D'UN EMPLOYE ====================
void MainWindow::on_pushButton_7_clicked()
{
    QString id_str = ui->lineEdit_2->text().trimmed();

    if (id_str.isEmpty()) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez d'abord sélectionner un employé à supprimer !");
        return;
    }

    bool ok;
    int id = id_str.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation de suppression",
                                  "Voulez-vous vraiment supprimer cet employé (ID: " + id_str + ") ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    Employe e;
    bool test = e.supprimer(id);

    if (test) {
        QMessageBox::information(this, "Succès", "✅ Employé supprimé avec succès !");
        afficherEmployes();

        // Nettoyer les champs
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_2->setReadOnly(false);
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Échec de la suppression dans la base de données.");
    }
}
