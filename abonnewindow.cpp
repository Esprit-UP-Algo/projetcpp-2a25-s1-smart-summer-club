#include "abonnewindow.h"
#include "ui_abonnewindow.h"
#include "abonne.h"

#include <QMessageBox>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QDialog>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QTableView>
#include <QDebug>

AbonneWindow::AbonneWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AbonneWindow)
{
    ui->setupUi(this);

    // Afficher tous les abonnés au démarrage
    Abonne a;
    ui->tableWidget->setModel(a.afficher());

    // Connecter les boutons
    connect(ui->pushButton_search, &QPushButton::clicked, this, &AbonneWindow::rechercherAbonne);
    connect(ui->pushButton_ajouter, &QPushButton::clicked, this, &AbonneWindow::ajouterAbonne);
    connect(ui->pushButton_modifier, &QPushButton::clicked, this, &AbonneWindow::modifierAbonne);
    connect(ui->pushButton_supprimer, &QPushButton::clicked, this, &AbonneWindow::supprimerAbonne);
    connect(ui->pushButton_export_pdf, &QPushButton::clicked, this, &AbonneWindow::exporterPDF);
    connect(ui->pushButton_trier, &QPushButton::clicked, this, &AbonneWindow::trierAbonne);

    // Statistiques
    connect(ui->pushButton_statistique, &QPushButton::clicked, this, [=](){
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle("Statistiques des abonnés");
        dialog->resize(600, 400);

        int tranche1 = 0, tranche2 = 0, tranche3 = 0, tranche4 = 0;

        QSqlQuery query("SELECT date_naissance FROM abonne");
        while(query.next()) {
            QDate dateNaissance = query.value(0).toDate();
            int age = dateNaissance.daysTo(QDate::currentDate()) / 365;
            if(age <= 20) tranche1++;
            else if(age <= 40) tranche2++;
            else if(age <= 60) tranche3++;
            else tranche4++;
        }

        QBarSet *set = new QBarSet("Nombre d'abonnés");
        *set << tranche1 << tranche2 << tranche3 << tranche4;

        QBarSeries *series = new QBarSeries();
        series->append(set);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Répartition des abonnés par tranche d'âge");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories = {"0-20", "21-40", "41-60", "61+"};
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        chart->createDefaultAxes();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QVBoxLayout *layout = new QVBoxLayout(dialog);
        layout->addWidget(chartView);
        dialog->exec();
    });

    // Historique
    connect(ui->pushButton_historique, &QPushButton::clicked, this, &AbonneWindow::historiqueAbonne);

    // 🔹 Remplir les champs automatiquement quand on clique sur une ligne
    connect(ui->tableWidget, &QTableView::clicked, this, &AbonneWindow::remplirChampsDepuisTable);
}

AbonneWindow::~AbonneWindow()
{
    delete ui;
}

// -------------------------
// Rechercher un abonné
void AbonneWindow::rechercherAbonne()
{
    QString texte = ui->lineEdit_search->text().trimmed();
    if (texte.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez entrer un ID.");
        return;
    }

    bool ok;
    int id = texte.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre.");
        return;
    }

    Abonne a;
    ui->tableWidget->setModel(a.rechercherParId(id));
}

// -------------------------
// Ajouter un abonné
void AbonneWindow::ajouterAbonne()
{
    Abonne a;
    a.setNom(ui->lineEdit_nom->text());
    a.setPrenom(ui->lineEdit_prenom->text());
    a.setAdresse(ui->lineEdit_adresse->text());
    a.setTelephone(ui->lineEdit_tel->text());
    a.setEmail(ui->lineEdit_mail->text());
    a.setDateNaissance(ui->dateEdit_naissance->date());

    if (a.ajouter()) {
        QMessageBox::information(this, "Succès", "Abonné ajouté !");
        ui->tableWidget->setModel(a.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter l'abonné.");
    }
}

// -------------------------
// 🔹 Remplir champs depuis le tableau
void AbonneWindow::remplirChampsDepuisTable(const QModelIndex &index)
{
    if (!index.isValid()) return;
    int row = index.row();
    QAbstractItemModel *model = ui->tableWidget->model();
    if (!model) return;

    ui->lineEdit_nom->setText(model->data(model->index(row,1)).toString());
    ui->lineEdit_prenom->setText(model->data(model->index(row,2)).toString());
    ui->dateEdit_naissance->setDate(model->data(model->index(row,3)).toDate());
    ui->lineEdit_adresse->setText(model->data(model->index(row,4)).toString());
    ui->lineEdit_tel->setText(model->data(model->index(row,5)).toString());
    ui->lineEdit_mail->setText(model->data(model->index(row,6)).toString());
    ui->lineEdit_search->setText(model->data(model->index(row,0)).toString());
}

// -------------------------
// Modifier un abonné (avec historique)
void AbonneWindow::modifierAbonne()
{
    QModelIndex index = ui->tableWidget->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un abonné dans le tableau pour modifier.");
        return;
    }

    int row = index.row();
    QAbstractItemModel *model = ui->tableWidget->model();
    if (!model) return;

    int id = model->data(model->index(row,0)).toInt();

    // Anciennes valeurs
    QString oldNom    = model->data(model->index(row,1)).toString();
    QString oldPrenom = model->data(model->index(row,2)).toString();
    QDate oldDateN    = model->data(model->index(row,3)).toDate();
    QString oldAdresse= model->data(model->index(row,4)).toString();
    QString oldTel    = model->data(model->index(row,5)).toString();
    QString oldEmail  = model->data(model->index(row,6)).toString();

    // Nouvelles valeurs (si vide, garder anciennes)
    QString newNom    = ui->lineEdit_nom->text().trimmed().isEmpty() ? oldNom : ui->lineEdit_nom->text().trimmed();
    QString newPrenom = ui->lineEdit_prenom->text().trimmed().isEmpty() ? oldPrenom : ui->lineEdit_prenom->text().trimmed();
    QString newAdresse= ui->lineEdit_adresse->text().trimmed().isEmpty() ? oldAdresse : ui->lineEdit_adresse->text().trimmed();
    QString newTel    = ui->lineEdit_tel->text().trimmed().isEmpty() ? oldTel : ui->lineEdit_tel->text().trimmed();
    QString newEmail  = ui->lineEdit_mail->text().trimmed().isEmpty() ? oldEmail : ui->lineEdit_mail->text().trimmed();
    QDate newDateN    = ui->dateEdit_naissance->date();

    // Historique
    QSqlQuery query;
    query.prepare(
        "INSERT INTO HISTORIQUE_ABONNE "
        "(ID_HISTORIQUE, ID_ABONNE, NOM, PRENOM, ADRESSE, TELEPHONE, EMAIL, DATE_NAISSANCE, DATE_MODIFICATION) "
        "VALUES (SEQ_ID_HISTORIQUE.NEXTVAL, :id_abonne, :nom, :prenom, :adresse, :tel, :email, :dateN, SYSDATE)"
    );
    query.bindValue(":id_abonne", id);
    query.bindValue(":nom", oldNom);
    query.bindValue(":prenom", oldPrenom);
    query.bindValue(":adresse", oldAdresse);
    query.bindValue(":tel", oldTel);
    query.bindValue(":email", oldEmail);
    query.bindValue(":dateN", oldDateN);

    if(!query.exec()) {
        QMessageBox::critical(this, "Erreur historique", "Erreur insertion historique : "+query.lastError().text());
        return;
    }

    // Modifier abonné
    Abonne a;
    a.setId(id);
    a.setNom(newNom);
    a.setPrenom(newPrenom);
    a.setAdresse(newAdresse);
    a.setTelephone(newTel);
    a.setEmail(newEmail);
    a.setDateNaissance(newDateN);

    if(a.modifier()) {
        QMessageBox::information(this,"Succès","Abonné modifié (ancienne version enregistrée) !");
        ui->tableWidget->setModel(a.afficher());
    } else {
        QMessageBox::critical(this,"Erreur","Impossible de modifier l'abonné.");
    }
}

// -------------------------
// Supprimer
void AbonneWindow::supprimerAbonne()
{
    QString texte = ui->lineEdit_search->text().trimmed();
    if(texte.isEmpty()) {
        QMessageBox::warning(this,"Attention","Veuillez entrer un ID.");
        return;
    }

    bool ok;
    int id = texte.toInt(&ok);
    if(!ok) {
        QMessageBox::warning(this,"Erreur","L'ID doit être un nombre.");
        return;
    }

    Abonne a;
    if(a.supprimer(id)) {
        QMessageBox::information(this,"Succès","Abonné supprimé !");
        ui->tableWidget->setModel(a.afficher());
    } else {
        QMessageBox::critical(this,"Erreur","Impossible de supprimer l'abonné.");
    }
}

// -------------------------
// Export PDF
void AbonneWindow::exporterPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Exporter PDF","","*.pdf");
    if(fileName.isEmpty()) return;
    if(!fileName.endsWith(".pdf")) fileName += ".pdf";

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QString html = "<h2>Liste des abonnés</h2><table border='1' cellspacing='0' cellpadding='2'>";
    html += "<tr><th>ID</th><th>Nom</th><th>Prénom</th><th>Date Naissance</th><th>Adresse</th><th>Téléphone</th><th>Email</th></tr>";

    QAbstractItemModel *model = ui->tableWidget->model();
    for(int i=0;i<model->rowCount();i++){
        html += "<tr>";
        for(int j=0;j<model->columnCount();j++){
            html += "<td>"+model->data(model->index(i,j)).toString()+"</td>";
        }
        html += "</tr>";
    }
    html += "</table>";

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(this,"Succès","Exportation PDF terminée !");
}

// -------------------------
// Trier
void AbonneWindow::trierAbonne()
{
    QString critere = ui->lineEdit_trier->text().trimmed();
    if(critere.isEmpty()){
        QMessageBox::warning(this,"Attention","Veuillez entrer un critère pour trier.");
        return;
    }

    Abonne a;
    ui->tableWidget->setModel(a.trier(critere));
}

// -------------------------
// Historique
void AbonneWindow::historiqueAbonne()
{
    int id_abonne = -1;
    QModelIndex index = ui->tableWidget->currentIndex();
    if(index.isValid()){
        id_abonne = index.sibling(index.row(),0).data().toInt();
    } else {
        bool ok;
        int id = ui->lineEdit_search->text().toInt(&ok);
        if(!ok){
            QMessageBox::warning(this,"Historique","Sélectionnez un abonné ou entrez un ID valide.");
            return;
        }
        id_abonne = id;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString(
        "SELECT ID_HISTORIQUE, ID_ABONNE, NOM, PRENOM, ADRESSE, TELEPHONE, EMAIL, DATE_NAISSANCE, DATE_MODIFICATION "
        "FROM HISTORIQUE_ABONNE "
        "WHERE ID_ABONNE=%1 ORDER BY DATE_MODIFICATION DESC"
    ).arg(id_abonne));

    if(model->lastError().isValid()){
        QMessageBox::critical(this,"Erreur historique","Erreur chargement historique : "+model->lastError().text());
        delete model;
        return;
    }

    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle(QString("Historique de l'abonné %1").arg(id_abonne));
    dlg->resize(800,400);

    QVBoxLayout *layout = new QVBoxLayout(dlg);
    QTableView *view = new QTableView(dlg);
    view->setModel(model);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setAlternatingRowColors(true);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout->addWidget(view);
    dlg->setLayout(layout);
    dlg->exec();
}
