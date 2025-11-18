#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inscription.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QColor>
#include <QHeaderView>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QPainter>
#include <QPixmap>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QDate>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QDateTime>
#include <QDebug>

// Pour QR Code - Utilisation simple avec QPainter
#include <QImage>
#include <QRect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , modelInscriptions(new QStandardItemModel(this))
    , modelAbonnes(new QStandardItemModel(this))
    , modelActivites(new QStandardItemModel(this))
    , currentInscriptionId(-1)
    , currentSortColumn("date_inscription")
    , currentSortOrder(Qt::DescendingOrder)
{
    ui->setupUi(this);

    // Initialiser la base de données
    if (!DatabaseManager::instance().initializeDatabase()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'initialiser la base de données");
        return;
    }

    initialiserUI();
    chargerDonnees();
    initialiserStatistiques();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialiserUI()
{
    // Configuration du modèle des inscriptions
    modelInscriptions->setHorizontalHeaderLabels({"ID", "Abonné", "Activité", "Date", "Statut", "Paiement", "Prix"});
    ui->tableView_inscriptions->setModel(modelInscriptions);
    ui->tableView_inscriptions->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Redimensionner les colonnes pour un meilleur affichage
    ui->tableView_inscriptions->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableView_inscriptions->setColumnWidth(0, 50);   // ID
    ui->tableView_inscriptions->setColumnWidth(1, 150);  // Abonné
    ui->tableView_inscriptions->setColumnWidth(2, 150);  // Activité
    ui->tableView_inscriptions->setColumnWidth(3, 100);  // Date
    ui->tableView_inscriptions->setColumnWidth(4, 100);  // Statut
    ui->tableView_inscriptions->setColumnWidth(5, 80);   // Paiement
    ui->tableView_inscriptions->setColumnWidth(6, 80);   // Prix

    // Connecter la recherche en temps réel
    connect(ui->lineEdit_search, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_search_textChanged);
}

void MainWindow::chargerDonnees()
{
    chargerInscriptions();
    chargerAbonnes();
    chargerActivites();
    mettreAJourStatistiques();
}

void MainWindow::chargerInscriptions(const QString &filter, const QString &sortColumn, Qt::SortOrder sortOrder)
{
    modelInscriptions->removeRows(0, modelInscriptions->rowCount());

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    
    QString sql = "SELECT i.*, a.nom as nom_abonne, a.prenom as prenom_abonne, act.nom as nom_activite, act.prix as prix_activite "
                   "FROM inscriptions i "
                   "JOIN abonnes a ON i.id_abonne = a.id_abonne "
                   "JOIN activites act ON i.id_activite = act.id_activite ";
    
    // Ajouter le filtre de recherche
    if (!filter.isEmpty()) {
        sql += "WHERE (i.id_inscription LIKE :filter OR "
               "a.nom LIKE :filter OR a.prenom LIKE :filter OR "
               "act.nom LIKE :filter OR i.statut LIKE :filter) ";
    }
    
    // Ajouter le tri
    QString orderBy = sortColumn.isEmpty() ? "i.date_inscription" : sortColumn;
    QString orderDir = (sortOrder == Qt::AscendingOrder) ? "ASC" : "DESC";
    sql += "ORDER BY " + orderBy + " " + orderDir;
    
    query.prepare(sql);
    if (!filter.isEmpty()) {
        query.bindValue(":filter", "%" + filter + "%");
    }
    
    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Erreur lors du chargement des inscriptions: " + query.lastError().text());
        return;
    }

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
        QString statut = query.value("statut").toString().toLower();
        if (statut == "confirmé") {
            backgroundColor = QColor("#d4edda"); // Vert clair
        } else if (statut == "annulée") {
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
        item->setData(query.value("id_abonne").toInt(), Qt::UserRole);
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
        item->setData(query.value("id_activite").toInt(), Qt::UserRole);
        modelActivites->appendRow(item);
    }
}

void MainWindow::mettreAJourStatistiques()
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());

    // Total inscriptions
    query.exec("SELECT COUNT(*) FROM inscriptions");
    if (query.next()) {
        // Les labels seront affichés dans l'onglet statistiques
    }

    // Inscriptions confirmées
    query.exec("SELECT COUNT(*) FROM inscriptions WHERE statut = 'confirmé'");
    if (query.next()) {
        // Les labels seront affichés dans l'onglet statistiques
    }

    // En attente
    query.exec("SELECT COUNT(*) FROM inscriptions WHERE statut = 'en attente'");
    if (query.next()) {
        // Les labels seront affichés dans l'onglet statistiques
    }

    // Revenus totaux
    query.exec("SELECT SUM(prix) FROM inscriptions WHERE paiement_effectue = 1");
    if (query.next()) {
        // Les labels seront affichés dans l'onglet statistiques
    }
}

void MainWindow::initialiserStatistiques()
{
    // Créer les graphiques pour l'onglet statistiques
    QWidget *statsWidget = ui->tab_statistique;
    
    // Supprimer le layout existant s'il y en a un
    if (statsWidget->layout()) {
        QLayoutItem *item;
        while ((item = statsWidget->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete statsWidget->layout();
    }
    
    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(statsWidget);
    
    // Graphique en barres - Inscriptions par statut
    QChart *chartStatut = new QChart();
    chartStatut->setTitle("Répartition des inscriptions par statut");
    
    QBarSet *set = new QBarSet("Inscriptions");
    
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    int confirme = 0, enAttente = 0, annulee = 0;
    
    query.exec("SELECT statut, COUNT(*) as count FROM inscriptions GROUP BY statut");
    while (query.next()) {
        QString statut = query.value("statut").toString().toLower();
        int count = query.value("count").toInt();
        if (statut == "confirmé") confirme = count;
        else if (statut == "en attente") enAttente = count;
        else if (statut == "annulée") annulee = count;
    }
    
    *set << confirme << enAttente << annulee;
    
    QBarSeries *series = new QBarSeries();
    series->append(set);
    chartStatut->addSeries(series);
    
    QStringList categories;
    categories << "Confirmé" << "En attente" << "Annulée";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chartStatut->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    chartStatut->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    QChartView *chartView = new QChartView(chartStatut);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(300);
    
    // Graphique en camembert - Répartition par activité
    QChart *chartActivite = new QChart();
    chartActivite->setTitle("Répartition des inscriptions par activité");
    
    QPieSeries *pieSeries = new QPieSeries();
    
    query.exec("SELECT act.nom, COUNT(i.id_inscription) as count "
               "FROM activites act "
               "LEFT JOIN inscriptions i ON act.id_activite = i.id_activite "
               "GROUP BY act.id_activite, act.nom");
    
    while (query.next()) {
        QString nom = query.value("nom").toString();
        int count = query.value("count").toInt();
        if (count > 0) {
            QPieSlice *slice = pieSeries->append(nom, count);
            slice->setLabelVisible(true);
        }
    }
    
    chartActivite->addSeries(pieSeries);
    chartActivite->legend()->setAlignment(Qt::AlignRight);
    
    QChartView *pieChartView = new QChartView(chartActivite);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setMinimumHeight(300);
    
    // Ajouter les graphiques au layout
    mainLayout->addWidget(chartView);
    mainLayout->addWidget(pieChartView);
    
    statsWidget->setLayout(mainLayout);
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
        
        // Charger les données dans le formulaire si disponible
        // (Les champs peuvent ne pas être présents dans l'UI)
    }
}

void MainWindow::on_ajouterInscription_clicked()
{
    bool ok;

    // Sélection de l'abonné
    QStringList abonnesList;
    QMap<QString, int> abonnesMap;

    for (int i = 0; i < modelAbonnes->rowCount(); ++i) {
        QString nomComplet = modelAbonnes->item(i)->text();
        int idAbonne = modelAbonnes->item(i)->data(Qt::UserRole).toInt();
        abonnesList << nomComplet;
        abonnesMap[nomComplet] = idAbonne;
    }

    if (abonnesList.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Aucun abonné disponible");
        return;
    }

    QString abonneSelectionne = QInputDialog::getItem(this, "Nouvelle inscription",
                                                      "Sélectionnez l'abonné:", abonnesList, 0, false, &ok);
    if (!ok || abonneSelectionne.isEmpty()) return;

    // Sélection de l'activité
    QStringList activitesList;
    QMap<QString, QPair<int, double>> activitesMap;

    for (int i = 0; i < modelActivites->rowCount(); ++i) {
        QString activiteInfo = modelActivites->item(i)->text();
        int idActivite = modelActivites->item(i)->data(Qt::UserRole).toInt();

        double prix = 0.0;
        int prixStart = activiteInfo.lastIndexOf("(");
        if (prixStart != -1) {
            QString prixStr = activiteInfo.mid(prixStart + 1).remove(" €)");
            prix = prixStr.toDouble();
        }

        activitesList << activiteInfo;
        activitesMap[activiteInfo] = qMakePair(idActivite, prix);
    }

    if (activitesList.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Aucune activité disponible");
        return;
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
    nouvelleInscription.setDateInscription(QDate::currentDate().toString("yyyy-MM-dd"));

    if (nouvelleInscription.sauvegarder()) {
        QMessageBox::information(this, "Succès", "Inscription ajoutée avec succès");
        chargerInscriptions();
        mettreAJourStatistiques();
        initialiserStatistiques(); // Rafraîchir les graphiques
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
    int currentIndex = statuts.indexOf(inscription->getStatut().toLower());
    if (currentIndex < 0) currentIndex = 0;
    
    QString nouveauStatut = QInputDialog::getItem(this, "Modifier inscription",
                                                  "Nouveau statut:", statuts,
                                                  currentIndex, false, &ok);

    if (ok) {
        inscription->setStatut(nouveauStatut);
        if (inscription->sauvegarder()) {
            QMessageBox::information(this, "Succès", "Inscription modifiée avec succès");
            chargerInscriptions();
            mettreAJourStatistiques();
            initialiserStatistiques();
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
            initialiserStatistiques();
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
            initialiserStatistiques();
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
    initialiserStatistiques();
    QMessageBox::information(this, "Actualisation", "Données mises à jour");
}

void MainWindow::on_pushButton_search_clicked()
{
    QString filter = ui->lineEdit_search->text();
    chargerInscriptions(filter, currentSortColumn, currentSortOrder);
}

void MainWindow::on_lineEdit_search_textChanged(const QString &text)
{
    chargerInscriptions(text, currentSortColumn, currentSortOrder);
}

void MainWindow::on_pushButton_trier_clicked()
{
    QStringList options = {"Date (plus récent)", "Date (plus ancien)", "Nom abonné (A-Z)", 
                           "Nom abonné (Z-A)", "Activité (A-Z)", "Prix (croissant)", 
                           "Prix (décroissant)", "Statut"};
    
    bool ok;
    QString choix = QInputDialog::getItem(this, "Trier par", "Sélectionnez le critère de tri:",
                                          options, 0, false, &ok);
    
    if (!ok) return;
    
    if (choix.contains("Date (plus récent)")) {
        currentSortColumn = "i.date_inscription";
        currentSortOrder = Qt::DescendingOrder;
    } else if (choix.contains("Date (plus ancien)")) {
        currentSortColumn = "i.date_inscription";
        currentSortOrder = Qt::AscendingOrder;
    } else if (choix.contains("Nom abonné (A-Z)")) {
        currentSortColumn = "a.nom";
        currentSortOrder = Qt::AscendingOrder;
    } else if (choix.contains("Nom abonné (Z-A)")) {
        currentSortColumn = "a.nom";
        currentSortOrder = Qt::DescendingOrder;
    } else if (choix.contains("Activité (A-Z)")) {
        currentSortColumn = "act.nom";
        currentSortOrder = Qt::AscendingOrder;
    } else if (choix.contains("Prix (croissant)")) {
        currentSortColumn = "i.prix";
        currentSortOrder = Qt::AscendingOrder;
    } else if (choix.contains("Prix (décroissant)")) {
        currentSortColumn = "i.prix";
        currentSortOrder = Qt::DescendingOrder;
    } else if (choix.contains("Statut")) {
        currentSortColumn = "i.statut";
        currentSortOrder = Qt::AscendingOrder;
    }
    
    QString filter = ui->lineEdit_search->text();
    chargerInscriptions(filter, currentSortColumn, currentSortOrder);
}

void MainWindow::on_pushButton_export_clicked()
{
    exporterPDF();
}

void MainWindow::exporterPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/inscriptions.pdf",
                                                    "PDF Files (*.pdf)");
    
    if (fileName.isEmpty()) return;
    
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);
    
    QTextDocument document;
    QTextCursor cursor(&document);
    
    // En-tête
    QTextCharFormat titleFormat;
    titleFormat.setFontPointSize(16);
    titleFormat.setFontWeight(QFont::Bold);
    cursor.insertText("Liste des Inscriptions", titleFormat);
    cursor.insertBlock();
    cursor.insertText("Date d'export: " + QDate::currentDate().toString("dd/MM/yyyy"));
    cursor.insertBlock();
    cursor.insertBlock();
    
    // Tableau
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setCellPadding(5);
    tableFormat.setCellSpacing(0);
    tableFormat.setBorder(1);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    
    QTextTable *table = cursor.insertTable(modelInscriptions->rowCount() + 1, 7, tableFormat);
    
    // En-têtes du tableau
    QStringList headers = {"ID", "Abonné", "Activité", "Date", "Statut", "Paiement", "Prix"};
    for (int col = 0; col < headers.size(); ++col) {
        QTextTableCell cell = table->cellAt(0, col);
        QTextCharFormat format = cell.format();
        format.setFontWeight(QFont::Bold);
        format.setBackground(QColor("#e0e0e0"));
        cell.setFormat(format);
        cell.firstCursorPosition().insertText(headers[col]);
    }
    
    // Données
    for (int row = 0; row < modelInscriptions->rowCount(); ++row) {
        for (int col = 0; col < modelInscriptions->columnCount(); ++col) {
            QStandardItem *item = modelInscriptions->item(row, col);
            if (item) {
                table->cellAt(row + 1, col).firstCursorPosition().insertText(item->text());
            }
        }
    }
    
    // Générer le QR code pour la première inscription si disponible
    if (currentInscriptionId > 0) {
        cursor.movePosition(QTextCursor::End);
        cursor.insertBlock();
        cursor.insertBlock();
        QTextCharFormat subtitleFormat;
        subtitleFormat.setFontPointSize(12);
        subtitleFormat.setFontWeight(QFont::Bold);
        cursor.insertText("QR Code de l'inscription sélectionnée:", subtitleFormat);
        cursor.insertBlock();
        
        // Générer et insérer le QR code
        genererQRCode(currentInscriptionId);
        QString qrPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/qr_" + QString::number(currentInscriptionId) + ".png";
        QFileInfo fileInfo(qrPath);
        if (fileInfo.exists()) {
            QTextImageFormat imageFormat;
            imageFormat.setName(qrPath);
            imageFormat.setWidth(100);
            imageFormat.setHeight(100);
            cursor.insertImage(imageFormat);
        }
    }
    
    document.print(&printer);
    QMessageBox::information(this, "Succès", "PDF exporté avec succès: " + fileName);
}

void MainWindow::genererQRCode(int idInscription)
{
    // Génération simple d'un QR code (version simplifiée)
    // Pour une vraie génération QR, il faudrait utiliser une bibliothèque comme qzxing
    
    QString data = QString("INSCRIPTION_ID:%1").arg(idInscription);
    
    // Créer une image simple représentant un QR code (version simplifiée)
    QImage qrImage(200, 200, QImage::Format_RGB32);
    qrImage.fill(Qt::white);
    
    QPainter painter(&qrImage);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    
    // Dessiner un motif simple (simulation de QR code)
    int cellSize = 10;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            // Générer un motif basé sur l'ID
            if ((i * 20 + j + idInscription) % 3 == 0) {
                painter.drawRect(i * cellSize, j * cellSize, cellSize, cellSize);
            }
        }
    }
    
    // Ajouter le texte
    painter.setPen(Qt::black);
    QFont font;
    font.setPointSize(8);
    painter.setFont(font);
    painter.drawText(QRect(0, 180, 200, 20), Qt::AlignCenter, QString("ID: %1").arg(idInscription));
    
    painter.end();
    
    // Sauvegarder l'image
    QString qrPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/qr_" + QString::number(idInscription) + ".png";
    qrImage.save(qrPath, "PNG");
    
    QMessageBox::information(this, "QR Code", "QR Code généré pour l'inscription #" + QString::number(idInscription));
}

void MainWindow::on_pushButton_refresh_table_clicked()
{
    ui->lineEdit_search->clear();
    currentSortColumn = "date_inscription";
    currentSortOrder = Qt::DescendingOrder;
    chargerInscriptions();
}
