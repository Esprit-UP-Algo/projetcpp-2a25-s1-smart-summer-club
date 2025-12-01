#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"

#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#include <QPageLayout>
#include <QPageSize>
#include <QMarginsF>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QInputDialog>
#include <QTimer>
#include <QApplication>
#include <QPushButton>

#include "login.h"

// ================= CONSTRUCTEUR / DESTRUCTEUR =================

MainWindow::MainWindow(QWidget *parent,
                       const QString &posteUser,
                       int idUser)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_posteUser(posteUser.toLower())
    , m_idUser(idUser)
{
    ui->setupUi(this);

    // cacher tous les boutons du menu
    ui->pushButton->hide();   // employés
    ui->pushButton_2->hide(); // activité
    ui->pushButton_3->hide(); // abonnés
    ui->pushButton_4->hide(); // inscription
    ui->pushButton_5->hide(); // matériel

    // Afficher uniquement le bouton correspondant au rôle
    QString r = m_posteUser;

    if (r.contains("responsable rh"))
        ui->pushButton->show();       // employés

    if (r.contains("responsable club"))
        ui->pushButton_2->show();     // activité

    if (r.contains("administrateur"))
        ui->pushButton_3->show();     // abonnés

    if (r.contains("comptable"))
        ui->pushButton_4->show();     // inscription

    if (r.contains("responsable ro"))
        ui->pushButton_5->show();     // matériel

    // Connexions des boutons du menu
    connect(ui->pushButton,   &QPushButton::clicked, this, &MainWindow::onMenuButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onMenuButtonClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::onMenuButtonClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::onMenuButtonClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::onMenuButtonClicked);

    afficherEmployes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ===============================================================
// GESTION MENU – ACCÈS SELON RÔLE
// ===============================================================

void MainWindow::onMenuButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString r = m_posteUser;

    // protection en plus (normalement les autres boutons sont cachés)
    if (r.contains("responsable rh")   && btn != ui->pushButton)   return;
    if (r.contains("responsable club") && btn != ui->pushButton_2) return;
    if (r.contains("administrateur")   && btn != ui->pushButton_3) return;
    if (r.contains("comptable")        && btn != ui->pushButton_4) return;
    if (r.contains("responsable ro")   && btn != ui->pushButton_5) return;

    QMessageBox::information(this,
                             "Accès autorisé",
                             "Vous avez accès à ce module.");
}

// ===============================================================
// GESTION DES DROITS : ici on retourne toujours true
// (tu peux plus tard réactiver des restrictions si tu veux)
// ===============================================================

bool MainWindow::aLeDroit(const QString &action)
{
    Q_UNUSED(action);
    return true;
}

// ===============================================================
// AFFICHE EMPLOYES
// ===============================================================

void MainWindow::afficherEmployes()
{
    QSqlQuery query;

    // tout le monde voit tous les employés
    query.prepare("SELECT * FROM SUMMER.EMPLOYE ORDER BY ID_EMPLOYE ASC");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL",
                              "Erreur : " + query.lastError().text());
        return;
    }

    ui->tableWidget->setColumnCount(11);
    QStringList headers {"ID","Nom","Prénom","Poste","Fonction",
                        "Genre","Email","Téléphone","Date Naissance",
                        "Adresse","Salaire"};

    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < 11; col++) {
            ui->tableWidget->setItem(
                row, col,
                new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// ===============================================================
// VALIDATIONS
// ===============================================================

bool MainWindow::validerGenre(const QString &genre)
{
    QString g = genre.trimmed().toUpper();
    if (g != "H" && g != "F") {
        QMessageBox::warning(this, "Genre invalide",
                             "Le genre doit être H ou F.");
        return false;
    }
    return true;
}

bool MainWindow::validerEmail(const QString &email)
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@(gmail|yahoo|outlook)\\.(fr|com)$");
    if (!regex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Email invalide",
                             "Format email incorrect !");
        return false;
    }
    return true;
}

bool MainWindow::validerTelephone(const QString &telephone)
{
    QRegularExpression regex("^[0-9]{8}$");
    if (!regex.match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Téléphone invalide",
                             "Doit contenir 8 chiffres.");
        return false;
    }
    return true;
}

bool MainWindow::validerDate(const QString &date)
{
    QRegularExpression regex("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/([0-9]{4})$");
    if (!regex.match(date).hasMatch()) {
        QMessageBox::warning(this, "Date invalide",
                             "Format : JJ/MM/AAAA");
        return false;
    }

    QStringList p = date.split("/");
    QDate d(p[2].toInt(), p[1].toInt(), p[0].toInt());

    if (!d.isValid() || d > QDate::currentDate()) {
        QMessageBox::warning(this, "Date invalide",
                             "Date incorrecte !");
        return false;
    }
    return true;
}

// ===============================================================
// AJOUT EMPLOYE
// ===============================================================

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
        QMessageBox::warning(this,"Erreur","Champs obligatoires manquants !");
        return;
    }

    bool ok;
    int id = id_str.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this,"Erreur","ID invalide !");
        return;
    }

    if (!genre.isEmpty() && !validerGenre(genre)) return;
    if (!email.isEmpty() && !validerEmail(email)) return;
    if (!telephone.isEmpty() && !validerTelephone(telephone)) return;
    if (!date_naissance.isEmpty() && !validerDate(date_naissance)) return;

    float salaire = salaire_str.toFloat(&ok);
    if (!ok) salaire = 0;

    Employe e(id, nom, prenom, poste, fonction, genre.toUpper(),
              email, telephone, date_naissance, adresse, salaire);

    if (!e.ajouter()) {
        QMessageBox::critical(this, "Erreur",
                              "Échec de l'ajout :\n" + e.lastError());
        return;
    }

    QMessageBox::information(this, "Succès", "Employé ajouté !");
    afficherEmployes();
}

// ===============================================================
// SÉLECTION TABLE
// ===============================================================

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    for (int i = 0; i < 11; i++) {
        QLineEdit *edit =
            this->findChild<QLineEdit*>(QString("lineEdit_%1").arg(i+2));

        if (edit && ui->tableWidget->item(row, i))
            edit->setText(ui->tableWidget->item(row, i)->text());
    }
}

// ===============================================================
// MODIFICATION
// ===============================================================

void MainWindow::on_pushButton_6_clicked()
{
    QString id_str = ui->lineEdit_2->text();
    if (id_str.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé !");
        return;
    }

    int id = id_str.toInt();

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

    bool ok;
    float salaire = salaire_str.toFloat(&ok);
    if (!ok) salaire = 0.0;

    if (!genre.isEmpty() && !validerGenre(genre)) return;
    if (!email.isEmpty() && !validerEmail(email)) return;
    if (!telephone.isEmpty() && !validerTelephone(telephone)) return;
    if (!date_naissance.isEmpty() && !validerDate(date_naissance)) return;

    Employe e(id, nom, prenom, poste, fonction, genre, email,
              telephone, date_naissance, adresse, salaire);

    if (e.modifier()) {
        QMessageBox::information(this, "Succès", "✔ Employé modifié !");
        afficherEmployes();
    } else {
        QMessageBox::critical(this, "Erreur",
                              "❌ Modification impossible !\n" + e.lastError());
    }
}

// ===============================================================
// SUPPRESSION
// ===============================================================

void MainWindow::on_pushButton_7_clicked()
{
    QString id_str = ui->lineEdit_2->text();

    if (id_str.isEmpty()) {
        QMessageBox::warning(this,"Erreur",
                             "Aucun employé sélectionné !");
        return;
    }

    Employe e;
    if (!e.supprimer(id_str.toInt())) {
        QMessageBox::critical(this,"Erreur",
                              "Suppression impossible !");
        return;
    }

    QMessageBox::information(this,"Succès","Employé supprimé !");
    afficherEmployes();
}

// ===============================================================
// TRI
// ===============================================================

void MainWindow::on_pushButton_12_clicked()
{
    QString critere = ui->comboBox_2->currentText();
    QString colonne;

    if (critere == "ID")
        colonne = "CAST(ID_EMPLOYE AS NUMBER)";
    else if (critere == "Nom")
        colonne = "NOM";
    else if (critere == "Prénom")
        colonne = "PRENOM";
    else if (critere == "Poste")
        colonne = "POSTE";
    else {
        QMessageBox::warning(this,"Erreur","Critère invalide !");
        return;
    }

    QString req =
        QString("SELECT * FROM SUMMER.EMPLOYE ORDER BY %1 ASC")
            .arg(colonne);

    QSqlQuery query(req);

    ui->tableWidget->setRowCount(0);

    if (!query.next()) {
        QMessageBox::warning(this,"Erreur SQL",
                             "Aucune donnée retournée !\nRequête :\n" + req);
        return;
    }

    query.previous();

    int totalCols = query.record().count();
    int row = 0;

    while (query.next()) {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < totalCols; col++) {
            ui->tableWidget->setItem(row, col,
                                     new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }

    QMessageBox::information(this,"Tri","Tri par " + critere + " effectué !");
}

// ===============================================================
// ATTESTATIONS - HTML
// ===============================================================

QString MainWindow::construireAttestationHtml(const QString &mode,
                                              const QString &id,
                                              const QString &nom,
                                              const QString &prenom,
                                              const QString &poste,
                                              const QString &fonction,
                                              const QString &naissance,
                                              const QString &adresse,
                                              const QString &salaire)
{
    QString html;

    html += "<style>"
            "body { font-family:'Georgia','Times New Roman',serif; font-size:14pt; }"
            ".page { "
            "width:85%; "
            "margin:auto; "
            "margin-top:30px; "
            "padding:30px; "
            "border:2px solid #004080; "
            "border-radius:12px; "
            "background-color:#f9fbff; "
            "position:relative;"
            "}"
            ".title { "
            "text-align:center; "
            "font-size:26pt; "
            "font-weight:bold; "
            "color:#003366; "
            "text-decoration:underline; "
            "margin-bottom:20px; "
            "}"
            ".separator { "
            "border-top:1px solid #004080; "
            "margin-top:5px; "
            "margin-bottom:25px; "
            "}"
            ".label { "
            "color:#003e7e; "
            "font-weight:bold; "
            "}"
            ".info { "
            "margin-left:40px; "
            "line-height:1.7; "
            "}"
            ".paragraph { "
            "margin-top:22px; "
            "text-align:justify; "
            "line-height:1.6; "
            "color:#111; "
            "}"
            ".signature { "
            "margin-top:60px; "
            "text-align:right; "
            "font-size:14pt; "
            "color:#003366; "
            "}"
            "</style>";

    html += "<div class='page'>";

    if (mode == "travail")
        html += "<p class='title'>Attestation de Travail</p>";
    else if (mode == "salaire")
        html += "<p class='title'>Attestation de Salaire</p>";
    else
        html += "<p class='title'>Attestation de Présence</p>";

    html += "<div class='separator'></div>";

    html += "<p class='paragraph'>Nous certifions que :</p>";

    html += "<div class='info'>";
    html += "<p><span class='label'>Nom & Prénom :</span> " + nom + " " + prenom + "</p>";
    html += "<p><span class='label'>ID Employé :</span> " + id + "</p>";
    html += "<p><span class='label'>Poste :</span> " + poste + "</p>";
    html += "<p><span class='label'>Fonction :</span> " + fonction + "</p>";
    html += "<p><span class='label'>Date de naissance :</span> " + naissance + "</p>";
    html += "<p><span class='label'>Adresse :</span> " + adresse + "</p>";

    if (mode == "salaire")
        html += "<p><span class='label'>Salaire mensuel brut :</span> " + salaire + " DT</p>";

    html += "</div>";

    if (mode == "travail") {
        html += "<p class='paragraph'>"
                "L'intéressé(e) exerce au sein de notre établissement et occupe son poste "
                "avec professionnalisme, sérieux et engagement."
                "</p>";
        html += "<p class='paragraph'>"
                "La présente attestation est délivrée à la demande de l'intéressé(e) "
                "pour servir et valoir ce que de droit."
                "</p>";
    }
    else if (mode == "salaire") {
        html += "<p class='paragraph'>"
                "L'intéressé(e) perçoit un salaire mensuel brut de <b>" + salaire +
                " dinars tunisiens</b>, conformément aux dispositions légales."
                "</p>";
        html += "<p class='paragraph'>"
                "La présente attestation est délivrée à la demande de l'intéressé(e) "
                "pour servir et valoir ce que de droit."
                "</p>";
    }
    else {
        html += "<p class='paragraph'>"
                "L'intéressé(e) est régulièrement présent(e) au sein de notre établissement "
                "et accomplit ses tâches conformément aux dispositions internes."
                "</p>";
        html += "<p class='paragraph'>"
                "La présente attestation est délivrée à la demande de l'intéressé(e) "
                "pour servir et valoir ce que de droit."
                "</p>";
    }

    html += "<div class='signature'>"
            "Tunis, le " + QDate::currentDate().toString("dd/MM/yyyy") +
            "<br><br><b>Le Directeur Général</b><br>Summer Club"
            "</div>";

    html += "</div>";

    return html;
}

// ===============================================================
// EXPORT PDF
// ===============================================================

void MainWindow::on_pushButton_10_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur",
                             "Veuillez sélectionner un employé dans la table.");
        return;
    }

    QStringList types;
    types << "Attestation de travail"
          << "Attestation de salaire"
          << "Attestation de présence";

    bool ok = false;
    QString choix = QInputDialog::getItem(this,
                                          "Type d'attestation",
                                          "Veuillez choisir le type :",
                                          types,
                                          0,
                                          false,
                                          &ok);
    if (!ok || choix.isEmpty())
        return;

    QString mode;
    if (choix.contains("travail", Qt::CaseInsensitive))
        mode = "travail";
    else if (choix.contains("salaire", Qt::CaseInsensitive))
        mode = "salaire";
    else
        mode = "presence";

    QString id        = ui->tableWidget->item(row, 0)->text();
    QString nom       = ui->tableWidget->item(row, 1)->text();
    QString prenom    = ui->tableWidget->item(row, 2)->text();
    QString poste     = ui->tableWidget->item(row, 3)->text();
    QString fonction  = ui->tableWidget->item(row, 4)->text();
    QString naissance = ui->tableWidget->item(row, 8)->text();
    QString adresse   = ui->tableWidget->item(row, 9)->text();
    QString salaire   = ui->tableWidget->item(row, 10)->text();

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter attestation",
        "attestation_" + nom + "_" + prenom + ".pdf",
        "PDF (*.pdf)");

    if (fileName.isEmpty())
        return;
    if (!fileName.endsWith(".pdf"))
        fileName += ".pdf";

    QString html = construireAttestationHtml(mode,
                                             id, nom, prenom,
                                             poste, fonction,
                                             naissance, adresse,
                                             salaire);

    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageOrientation(QPageLayout::Portrait);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    doc.print(&printer);

    QMessageBox::information(this, "Succès",
                             "Attestation exportée en PDF avec succès !");
}

// ===============================================================
// IMPRESSION DIRECTE
// ===============================================================

void MainWindow::on_pushButton_imprimer_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur",
                             "Veuillez sélectionner un employé dans la table.");
        return;
    }

    QString mode = "travail";

    QString id        = ui->tableWidget->item(row, 0)->text();
    QString nom       = ui->tableWidget->item(row, 1)->text();
    QString prenom    = ui->tableWidget->item(row, 2)->text();
    QString poste     = ui->tableWidget->item(row, 3)->text();
    QString fonction  = ui->tableWidget->item(row, 4)->text();
    QString naissance = ui->tableWidget->item(row, 8)->text();
    QString adresse   = ui->tableWidget->item(row, 9)->text();
    QString salaire   = ui->tableWidget->item(row, 10)->text();

    QString html = construireAttestationHtml(mode,
                                             id, nom, prenom,
                                             poste, fonction,
                                             naissance, adresse,
                                             salaire);

    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Imprimer l'attestation");

    if (dialog.exec() != QDialog::Accepted)
        return;

    printer.setPageOrientation(QPageLayout::Portrait);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    doc.print(&printer);
}

// ===============================================================
// RECHERCHE
// ===============================================================

void MainWindow::on_pushButton_11_clicked()
{
    QString id_str = ui->lineEdit_9->text().trimmed();

    if (id_str.isEmpty()) {
        QMessageBox::warning(this,"Erreur","Entrez un ID !");
        return;
    }

    bool ok;
    int id = id_str.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this,"Erreur","ID invalide !");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM SUMMER.EMPLOYE WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);
    query.exec();

    ui->tableWidget->setRowCount(0);

    if (query.next()) {
        ui->tableWidget->insertRow(0);
        for (int col = 0; col < 11; col++)
            ui->tableWidget->setItem(0,col,
                                     new QTableWidgetItem(query.value(col).toString()));
        QMessageBox::information(this,"Résultat","Employé trouvé !");
    } else {
        QMessageBox::information(this,"Résultat",
                                 "Aucun employé trouvé.");
    }
}

// ===============================================================
// STATISTIQUES GENRE (CAMEMBERT)
// ===============================================================

void MainWindow::on_pushButton_8_clicked()
{
    int H = 0, F = 0;

    QSqlQuery query("SELECT GENRE FROM SUMMER.EMPLOYE");
    while (query.next()) {
        QString g = query.value(0).toString().toUpper();
        if (g == "H") H++;
        else if (g == "F") F++;
    }

    int total = H + F;
    if (total == 0) return;

    double pH = (double)H / total * 100.0;
    double pF = (double)F / total * 100.0;

    QPieSeries *series = new QPieSeries();

    QPieSlice *sliceH = series->append(QString("Hommes (%1%)").arg(QString::number(pH,'f',1)), H);
    QPieSlice *sliceF = series->append(QString("Femmes (%1%)").arg(QString::number(pF,'f',1)), F);

    series->setLabelsVisible(true);

    sliceH->setLabelFont(QFont("Arial", 10));
    sliceF->setLabelFont(QFont("Arial", 10));

    sliceH->setLabelColor(Qt::black);
    sliceF->setLabelColor(Qt::black);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés (%)");
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->resize(700, 500);
    view->show();
}

// ===============================================================
// DECONNEXION
// ===============================================================

void MainWindow::on_pushButton_9_clicked()
{
    // CONFIRMATION
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Déconnexion",
        "Voulez-vous vraiment vous déconnecter ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::No)
        return;

    // FERMER LA FENÊTRE PRINCIPALE
    this->close();

    // OUVRIR LA FENÊTRE LOGIN
    Login login;
    if (login.exec() == QDialog::Accepted)
    {
        // Récupérer les infos du nouvel utilisateur
        int idUser = login.getIdEmploye();
        QString posteUser = login.getPosteBD();

        // Ouvrir une nouvelle MainWindow
        MainWindow *w = new MainWindow(nullptr, posteUser, idUser);
        w->show();
    }
    else
    {
        // Si l'utilisateur annule → on quitte l'application
        QApplication::quit();
    }
}

