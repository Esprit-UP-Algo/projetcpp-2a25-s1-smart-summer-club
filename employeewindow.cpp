#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "employee.h"

#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QPainter>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

EmployeeWindow::EmployeeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmployeeWindow),
    selectedId(0)
{
    ui->setupUi(this);

    // Remplir le comboBox de tri
    ui->comboBox_tri->clear();
    ui->comboBox_tri->addItem("ID");
    ui->comboBox_tri->addItem("Nom");
    ui->comboBox_tri->addItem("Prénom");

    connect(ui->comboBox_tri, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &EmployeeWindow::trierEmployees);

    afficherEmployees();

    // Connecter les boutons
    connect(ui->pushButton_statistique, &QPushButton::clicked,
            this, &EmployeeWindow::afficherStatistique);

    connect(ui->pushButton_attestation, &QPushButton::clicked,
            this, &EmployeeWindow::on_pushButton_attestation_clicked);
}

EmployeeWindow::~EmployeeWindow()
{
    delete ui;
}

// 🔹 Affichage
void EmployeeWindow::afficherEmployees()
{
    Employee e;
    QSqlQueryModel *model = e.afficher();

    if(ui->tableView->model())
        delete ui->tableView->model();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    if(ui->tableView->model()) {
        connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &EmployeeWindow::selectionChanged);
    }

    selectedId = (model->rowCount() > 0) ? model->index(0,0).data().toInt() : 0;
}

// 🔹 Sélection d’une ligne
void EmployeeWindow::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    if(selected.indexes().isEmpty()) return;

    int row = selected.indexes().first().row();
    auto model = ui->tableView->model();

    ui->lineEdit_nom->setText(model->index(row,1).data().toString());
    ui->lineEdit_prenom->setText(model->index(row,2).data().toString());
    ui->lineEdit_poste->setText(model->index(row,3).data().toString());
    ui->lineEdit_fonction->setText(model->index(row,4).data().toString());
    ui->lineEdit_genre->setText(model->index(row,5).data().toString());
    ui->lineEdit_mail->setText(model->index(row,6).data().toString());
    ui->lineEdit_tel->setText(model->index(row,7).data().toString());
    ui->dateEdit_naissance->setDate(QDate::fromString(model->index(row,8).data().toString(),"yyyy-MM-dd"));
    ui->lineEdit_adresse->setText(model->index(row,9).data().toString());
    ui->lineEdit_salaire->setText(model->index(row,10).data().toString());

    selectedId = model->index(row,0).data().toInt();
}

// 🔹 Ajouter
void EmployeeWindow::on_pushButton_ajouter_clicked()
{
    Employee e(ui->lineEdit_nom->text(),
               ui->lineEdit_prenom->text(),
               ui->lineEdit_poste->text(),
               ui->lineEdit_fonction->text(),
               ui->lineEdit_genre->text(),
               ui->lineEdit_mail->text(),
               ui->lineEdit_tel->text(),
               ui->dateEdit_naissance->date(),
               ui->lineEdit_adresse->text(),
               ui->lineEdit_salaire->text().toDouble());

    if(e.ajouter()) {
        QMessageBox::information(this,"Ajouter","Employé ajouté avec succès !");
        afficherEmployees();
    } else {
        QMessageBox::warning(this,"Erreur","Échec de l'ajout !");
    }
}

// 🔹 Modifier
void EmployeeWindow::on_pushButton_modifier_clicked()
{
    if(selectedId == 0) {
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner un employé !");
        return;
    }

    Employee e(selectedId,
               ui->lineEdit_nom->text(),
               ui->lineEdit_prenom->text(),
               ui->lineEdit_poste->text(),
               ui->lineEdit_fonction->text(),
               ui->lineEdit_genre->text(),
               ui->lineEdit_mail->text(),
               ui->lineEdit_tel->text(),
               ui->dateEdit_naissance->date(),
               ui->lineEdit_adresse->text(),
               ui->lineEdit_salaire->text().toDouble());

    if(e.modifier()) {
        QMessageBox::information(this,"Modifier","Employé modifié avec succès !");
        afficherEmployees();
    } else {
        QMessageBox::warning(this,"Erreur","Échec de la modification !");
    }
}

// 🔹 Supprimer
void EmployeeWindow::on_pushButton_supprimer_clicked()
{
    if(selectedId == 0) {
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner un employé !");
        return;
    }

    Employee e;
    if(e.supprimer(selectedId)) {
        QMessageBox::information(this,"Supprimer","Employé supprimé avec succès !");
        selectedId = 0;
        afficherEmployees();
    } else {
        QMessageBox::warning(this,"Erreur","Échec de la suppression !");
    }
}

// 🔹 Recherche
void EmployeeWindow::on_pushButton_recherche_clicked()
{
    QString recherche = ui->lineEdit_recherche->text().trimmed();
    if(recherche.isEmpty()) {
        QMessageBox::warning(this,"Recherche","Veuillez entrer un ID, Nom ou Prénom !");
        return;
    }

    Employee e;
    QSqlQueryModel *model = nullptr;
    bool ok;
    int idRecherche = recherche.toInt(&ok);

    if(ok)
        model = e.rechercherParId(idRecherche);
    else {
        QSqlQuery query;
        query.prepare("SELECT ID_EMPLOYEE, NOM, PRENOM, POSTE, FONCTION, GENRE, EMAIL, TELEPHONE, "
                      "TO_CHAR(DATE_NAISSANCE,'YYYY-MM-DD') AS DATE_NAISSANCE, ADRESSE, SALAIRE "
                      "FROM EMPLOYEE WHERE LOWER(NOM) LIKE :text OR LOWER(PRENOM) LIKE :text "
                      "ORDER BY NOM ASC, PRENOM ASC");
        query.bindValue(":text", "%" + recherche.toLower() + "%");
        query.exec();

        model = new QSqlQueryModel();
        model->setQuery(std::move(query));
    }

    if(model && model->rowCount() > 0) {
        if(ui->tableView->model()) delete ui->tableView->model();
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        selectedId = model->index(0,0).data().toInt();
    } else {
        QMessageBox::information(this,"Recherche","Aucun résultat trouvé !");
        if(ui->tableView->model()) delete ui->tableView->model();
        ui->tableView->setModel(nullptr);
        selectedId = 0;
    }
}

// 🔹 Trier
void EmployeeWindow::trierEmployees(int index)
{
    Employee e;
    QSqlQueryModel *model = nullptr;

    if(index == 0)
        model = e.trierParId();
    else if(index == 1)
        model = e.trierParNom();
    else if(index == 2)
        model = e.trierParPrenom();

    if(model) {
        if(ui->tableView->model())
            delete ui->tableView->model();

        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();

        selectedId = (model->rowCount() > 0) ? model->index(0,0).data().toInt() : 0;
    }
}

// 🔹 Statistique
void EmployeeWindow::afficherStatistique()
{
    QSqlQuery query;
    query.exec("SELECT GENRE, COUNT(*) FROM EMPLOYEE GROUP BY GENRE");

    int hommes = 0, femmes = 0;
    while(query.next()) {
        QString genre = query.value(0).toString().toLower();
        int count = query.value(1).toInt();
        if(genre.contains("homme")) hommes = count;
        else if(genre.contains("femme")) femmes = count;
    }

    int total = hommes + femmes;
    if(total == 0) {
        QMessageBox::information(this,"Statistique","Aucun employé trouvé !");
        return;
    }

    QPieSeries *series = new QPieSeries();
    if(hommes > 0) {
        QPieSlice *sliceH = series->append("Hommes", hommes);
        sliceH->setLabel(QString("Hommes : %1 (%2%)").arg(hommes).arg(hommes*100/total));
        sliceH->setLabelVisible(true);
        sliceH->setBrush(Qt::blue);
    }
    if(femmes > 0) {
        QPieSlice *sliceF = series->append("Femmes", femmes);
        sliceF->setLabel(QString("Femmes : %1 (%2%)").arg(femmes).arg(femmes*100/total));
        sliceF->setLabelVisible(true);
        sliceF->setBrush(Qt::magenta);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par genre");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *statWindow = new QWidget();
    statWindow->setWindowTitle("Statistique par genre");
    QVBoxLayout *layout = new QVBoxLayout(statWindow);
    layout->addWidget(chartView);
    statWindow->setLayout(layout);
    statWindow->resize(600,400);
    statWindow->show();
}

// 🔹 Attestation PDF
void EmployeeWindow::on_pushButton_attestation_clicked()
{
    if(selectedId == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé !");
        return;
    }

    Employee emp(selectedId,
                 ui->lineEdit_nom->text(),
                 ui->lineEdit_prenom->text(),
                 ui->lineEdit_poste->text(),
                 ui->lineEdit_fonction->text(),
                 ui->lineEdit_genre->text(),
                 ui->lineEdit_mail->text(),
                 ui->lineEdit_tel->text(),
                 ui->dateEdit_naissance->date(),
                 ui->lineEdit_adresse->text(),
                 ui->lineEdit_salaire->text().toDouble());

    QString fileName = QFileDialog::getSaveFileName(this,
        "Enregistrer Attestation", emp.getNom() + "_" + emp.getPrenom() + ".pdf", "*.pdf");
    if(fileName.isEmpty()) return;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;

    QString html;
    html += "<html><head><style>"
            "body {font-family: Arial, sans-serif; line-height: 1.6; margin: 30px;}"
            "h1 {text-align: center; color: #FF6600; font-size: 28pt; margin-bottom: 40px;}"
            "p {font-size: 14pt; margin: 10px 0;}"
            "span.label {font-weight: bold; color: #003366;}"
            ".signature {margin-top: 60px; text-align: right; font-size: 14pt;}"
            "</style></head><body>";

    html += "<h1>Attestation d'emploi</h1>";
    html += "<p>Je soussigné(e), certifie que l'employé(e) suivant(e) :</p>";
    html += "<p><span class='label'>ID :</span> " + QString::number(emp.getId()) + "</p>";
    html += "<p><span class='label'>Nom :</span> " + emp.getNom() + "</p>";
    html += "<p><span class='label'>Prénom :</span> " + emp.getPrenom() + "</p>";
    html += "<p><span class='label'>Poste :</span> " + emp.getPoste() + "</p>";
    html += "<p><span class='label'>Fonction :</span> " + emp.getFonction() + "</p>";
    html += "<p><span class='label'>Genre :</span> " + emp.getGenre() + "</p>";
    html += "<p><span class='label'>Email :</span> " + emp.getEmail() + "</p>";
    html += "<p><span class='label'>Téléphone :</span> " + emp.getTelephone() + "</p>";
    html += "<p><span class='label'>Adresse :</span> " + emp.getAdresse() + "</p>";
    html += "<p><span class='label'>Date de naissance :</span> " + emp.getDateNaissance().toString("yyyy-MM-dd") + "</p>";
    html += "<p><span class='label'>Salaire :</span> " + QString::number(emp.getSalaire()) + "</p>";
    html += "<p style='margin-top:30px;'>Cette attestation est délivrée pour servir et valoir ce que de droit.</p>";
    html += "<p class='signature'>Signature:<br>____________________</p>";
    html += "</body></html>";

    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(this, "Succès", "Attestation PDF générée avec succès !");
}
